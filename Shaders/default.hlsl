struct vertexin
{

    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 noraml : NORMAL;
    float3 tangentU : TANGENT;
    float AOk : AOk;
    float3 color : COLOR;
#ifdef SKINNED
 float4 boneweights : WEIGHTS;
    uint4 boneindex : BONEINDICES;

#endif

};
struct vertexout
{
    float4 positionH : SV_POSITION;
    float3 positionW : POSITIONT;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tanegntU : TANGENT;
    float4 positionL : POSITIONT1;
    float AOk : AOk;
    float3 color : COLOR;
};
Texture2D g_tex : register(t0);
Texture2D g_nmap : register(t1);
TextureCube g_skycube1 : register(t2);
Texture2D g_smap : register(t3);
Texture2D g_precomMap : register(t4);
Texture2D g_precomavgMap : register(t5);
Texture2D g_LUT : register(t7);
Texture2D g_ssaomap : register(t8);
Texture2D g_fluxmap : register(t9);
Texture2D g_normalmap : register(t10);
Texture2D g_worldposmap : register(t11);
Texture2D g_SSDODLmap : register(t12);
Texture2D g_SSDOnmap : register(t13);
Texture2D g_lastFrame : register(t14);
Texture3D LPV3Dtex1 : register(t16);
Texture3D LPV3Dtex2 : register(t17);
Texture3D LPV3Dtex3 : register(t18);
SamplerState g_sampler : register(s0);
int Xplus(float alpha)
{
    if (alpha > 0)
        return 1;
    else
        return 0;
}
float Blinn_PhongNDF(float r, float3 n, float3 h)
{
    float alpha = 2 * pow(r, -2) - 2;
    return ((alpha + 2) * (pow(max(dot(h, n), 0), alpha)) / (2 * 3.1415926));

}
float GGX(float3 alpha, float3 n, float3 h)
{
    alpha = alpha * alpha;
    float ret = (pow(alpha, 2) * Xplus(dot(h, n))) / (3.1415926585f * pow((1 + pow(dot(n, h), 2) * (alpha * alpha - 1)), 2));
    if (ret > 10)
        return 10;
    
    return ret;
}
float3 SchlickFresnel(float3 F0, float3 n, float3 h)
{
    return F0 + (1 - F0) * pow((1 - max(0, dot(n, h))), 5);
    

}
float3 smooth_SurfaceDiff(float3 F0, float3 albedo, float3 n, float3 l, float Dotnv)
{
    float k = (21 / (20 * 3.1415926));
    float3 base1 = (1 - pow(1 - max(0, dot(n, l)), 5));
    float3 base2 = (1 - pow(1 - max(0, Dotnv), 5));
    return k * (1 - F0) * base1 * base2 * albedo;

}
float lambda(float alpha)
{
    return (-1 + pow((1 + (1 / dot(alpha, alpha))), 0.5)) / 2;

}
float smithG2(float3 h, float3 l, float3 n, float roughness, float Dotnv, float Dothv)
{
    float a1 = dot(n, l) / (roughness * (pow((1 - pow(dot(n, l), 2)), 0.5)));
    float a2 = Dotnv / (roughness * (pow((1 - pow(Dotnv, 2)), 0.5)));
    float3 base1 = 1 + lambda(a1) + lambda(a2);
    float3 base2 = Xplus(Dothv) * Xplus(dot(h, l));
    return base2 / base1;

}

cbuffer passcb : register(b0)
{
    float4x4 MWVP;
    float3 eyepos;
    float pad1;
    float3 AL;
    float pad2;
    float3 BL;
    float roughness;
    float3 lightdir;
    float pad3;
    float4 md;
    float3 r0;
    float pad4;
    float4x4 V;
    float4x4 W;
    float4x4 VP;
    float4x4 WinvT;
    float4x4 P;
    float4x4 S;
    float3 lightPos;
    float pad5;
    float4x4 smuvmat;
    float4x4 invP;
    float4x4 invuvmat;
    float randnum[4096];
    
}

cbuffer objcb : register(b1)
{
    float4x4 world;
    float4x4 worldinvT;
}
cbuffer modelmats : register(b2)
{
    float4x4 finalmats[58];
}
static const float sm_dx = 1.0f / 2048.0f;
static const float sm_dy = 1.0f / 2048.0f;
static const float Rsmdx = 1.0f / 1000.0f;
static const float Rsmdy = 1.0f / 1000.0f;
static const float SSRdx = 1.0f / 1024.0f;
static const float SSRdy = 1.0f / 768.0f;
vertexout VS(vertexin pin)
{
    vertexout pout;
   
  
    float4 Position = pin.position;
//#ifdef SKINNED
    
//    Position = (pin.boneweights.x * mul(Position, finalmats[pin.boneindex.x]))
//    + (pin.boneweights.y * mul(Position, finalmats[pin.boneindex.y])) +
//    pin.boneweights.z * mul(Position, finalmats[pin.boneindex.z]) + pin.boneweights.w * mul(Position, finalmats[pin.boneindex.w]);

//#endif
    Position /= Position.w;
    pout.positionW = mul(Position, world).xyz;
    float4x4 MVP = mul(world, VP);
    float4 posmvp = mul(Position, MVP);
    pout.positionH = posmvp;
    pout.uv = pin.uv;
    pout.normal = pin.noraml;
    pout.tanegntU = pin.tangentU;
    pout.positionL = mul(float4(pout.positionW, 1.0f), S);
    pout.AOk = pin.AOk;
    pout.color = pin.color;
    return pout;
}
float calct(float3 postocenter, float3 specularDir, float r)
{
    float tx, ty, tz;
    float disx = r - abs(postocenter.x);
    if (postocenter.x > 0)
    {
        if (specularDir.x > 0)
            tx = abs(disx / specularDir.x);
        if (specularDir.x < 0)
            tx = abs((abs(postocenter.x) + r) / abs(specularDir.x));

    }
    if (postocenter.x < 0)
    {
        if (specularDir.x > 0)
            tx = abs(abs(postocenter.x) + r / specularDir.x);
        if (specularDir.x < 0)
            tx = abs((disx) / abs(specularDir.x));
    }
    float disy = r - abs(postocenter.y);
    if (postocenter.y > 0)
    {
        if (specularDir.y > 0)
            ty = abs(disy / specularDir.y);
        if (specularDir.y < 0)
            ty = abs((abs(postocenter.y) + r) / abs(specularDir.y));

    }
    if (postocenter.y < 0)
    {
        if (specularDir.y > 0)
            ty = abs(abs(postocenter.y) + r / specularDir.y);
        if (specularDir.y < 0)
            ty = abs((disy) / abs(specularDir.y));
    }
    float disz = r - abs(postocenter.z);
    if (postocenter.z > 0)
    {
        if (specularDir.z > 0)
            tz = abs(disz / specularDir.z);
        if (specularDir.z < 0)
            tz = abs((abs(postocenter.z) + r) / abs(specularDir.z));

    }
    if (postocenter.z < 0)
    {
        if (specularDir.z > 0)
            tz = abs(abs(postocenter.z) + r / specularDir.z);
        if (specularDir.z < 0)
            tz = abs((disz) / abs(specularDir.z));
    }
    return min(min(tx, tz), ty);

}
float calcShadowFactor(float lightWidth, float dis, float2 smuv)//pcss的硬算版，坐等vssm
{
    float occdepth = 0;
    int numocc = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            float depth = (g_smap.Sample(g_sampler, smuv + float2(sm_dx * i, sm_dy * j)).r);
            if (dis > depth)
            {
                occdepth += depth;
                numocc++;
            }
        }
    }
    float avoccdepth = occdepth / numocc;
    float coresize = 0;
 
    coresize = lightWidth * ((dis - avoccdepth) / avoccdepth) + 1;
    
    int convCore = coresize;
    if (convCore > 2)
        convCore = 2; //大于4就崩，最多3，还是得加速
    if (convCore <= 0)
        convCore = 0;
    float shadowfactor = 0;
    
    for (int k = -1 * convCore; k <= convCore; k++)
    {
        for (int l = -1 * convCore; l <= 1 * convCore; l++)
        {
            float depth = (g_smap.Sample(g_sampler, smuv + float2(sm_dx * k, sm_dy * l)).r);
            shadowfactor += (dis > depth + 0.005f);

        }

    }
    shadowfactor /= (convCore * 2 + 1) * (convCore * 2 + 1);
    return (1.0f - shadowfactor + 0.7f) / 2.0f;
}
float random(float2 st)
{
   
    return frac(sin(dot(st.xy, float2(12.9898, 78.233))) * 43758.5453);
    
}

float3 RandHemisphereUnitVec3new(float4 n, float num1, float num2)
{
    float3 H = -1 * n.xyz;
    int i = 0;
    while (dot(H, n.xyz) < 0)
    {
        i++;
        num1++;
        num2++;
        if (i > 10)
            return n.xyz;
        float phi = 2 * 3.14159f * random(float2(num1, num2));
        float theta = acos(2 * random(float2(num2, num1)) - 1);
        float SinTheta = sin(theta);
        H.x = SinTheta * cos(phi);
        H.z = SinTheta * sin(phi);
        H.y = cos(theta);
        
    }
    return normalize(H);
}
float calcShadowFactorVssm(int coresize, float dis, float2 smuv)//pcf的加速
{
    float sum = 0;
    float sum2 = 0;
    for (int i = 0; i <= 30; i++)
    {
        int dx = int(randnum[i * 4] * 6.0f);
        int dy = int(randnum[i * 4 + 1] * 6.0f);
        float sample = g_smap.Sample(g_sampler, smuv + float2(dx * sm_dx, dy * sm_dy));
        int dx2 = int(randnum[i * 4 + 2] * 6.0f);
        int dy2 = int(randnum[i * 4 + 3] * 6.0f);
        float sample2 = g_smap.Sample(g_sampler, smuv + float2(dx2 * sm_dx, dy2 * sm_dy));
        sum += sample;
        sum2 += (sample2 * sample2);
    }
    float Ex = (sum / 30.0f) * 100.0f;
    float Ex2 = (sum2 / 30.0f) * 100.0f;
    float Dx = abs(Ex2 - Ex * Ex); //理应是个负数
    return (Dx / (Dx + (pow(dis - Ex, 2)))); //这有问题
 
    //float sum = 0;
    //for (int i = 0; i < 99; i++)
    //{
    //    sum += abs(randnum[i]);

    //}
    //return sum;
}
float occlusionFunc(float distz)
{
    float occlusion = 0;
    if (distz > 0)
    {
        //float fadeLength = 5 - 0.25f;
        //occlusion = saturate((5 - distz) / fadeLength);
        occlusion = 1;
    }
    return occlusion;
}
float NDCdepthToViewdepth(float ndc)
{
    return P[3][2] / (ndc - P[2][2]);
}
float ViewdepthToNDC(float Viewdepth)
{
    return (P[3][2] / Viewdepth) + P[2][2];
}
float3 avgFmu(float3 F0, float3 l, float3 n)
{
    float3 outter = float3(0, 0, 0);
    for (int i = 0; i < 20; i++)
    {
     
        float mu = random(float2(i * i, i + 20));
        float3 v = float3(-1.0f * sqrt(1 - mu * mu), mu, 0);
        float3 h = normalize(l + v);

        float3 fmu = SchlickFresnel(F0, n, h);
        outter.x = outter.x + fmu.x * 2 * mu;
        outter.y = outter.y + fmu.y * 2 * mu;
        outter.z = outter.z + fmu.z * 2 * mu;
    }
    outter /= 20.0f;
    return outter;

}
float3 Fadd(float3 F0, float3 l, float3 n, float Eavg)
{
    float favg = avgFmu(F0, l, n);
    float3 base1 = favg * Eavg;
    float3 base2 = 1 - favg * (1 - Eavg);
    return base1 / base2;

}

float4 UniformSampleHemisphere(float2 E)
{
    float Phi = 2 * 3.1415926f * E.x;
    float CosTheta = E.y;
    float SinTheta = sqrt(1 - CosTheta * CosTheta);

    float3 H;
    H.x = SinTheta * cos(Phi);
    H.y = SinTheta * sin(Phi);
    H.z = CosTheta;

    float PDF = 1.0 / (2 * 3.1415926f);

    return float4(H, PDF);
}
float3 fms(float3 Emuo, float3 Emui, float3 Eavg)
{
  
    float3 base1 = (1 - Emuo) * (1 - Emui);
    float3 base2 = 3.14159f * (1 - Eavg);
    return base1 / base2;
}
bool SSRtest(float2 V0, float2 V1, float2 nextuv, float k0, float k1, float Vz1, float Vz2)
{
    float t = (nextuv.x - V0.x) / (V1.x - V0.x);
    float k = k0 + (k1 - k0) * t;
    float2 V = mul(float4(nextuv, 0, 0), invuvmat).xy * k;
    float Vz = Vz1 + t * (Vz2 - Vz1);
    float VzNDC = ViewdepthToNDC(Vz);
    float NDCzofMap = g_smap.Sample(g_sampler, nextuv);
    float VzofMap = NDCdepthToViewdepth(NDCzofMap);

    float4 Vproj = float4(V, VzNDC * k, k);
    float4 Q = mul(Vproj, invP);
    if (VzofMap + 0.5f < Q.z)
        return true;
    else
        return false;
}
#define PI 3.14159f
#define SH_C0 0.282094792f // 1 / 2sqrt(pi)
#define SH_C1 0.488602512f // sqrt(3/pi) / 2

float4 SHbase(float3 n)
{
    float Y[4];
    Y[0] = SH_C0;
    Y[1] = SH_C1 * n.y;
    Y[2] = SH_C1 * n.z;
    Y[3] = SH_C1 * n.x;
    return float4(Y[0], Y[1], Y[2], Y[3]);
}
float3 getCellCenter(int3 index)
{
    return float3(-60 + 6 + 12 * index.x, 5 + 10 * index.y, -60 + 6 + 12 * index.z);
}
float4 getirradiance(float3 radianceDir, int3 index)
{



    float3 E = float3(0, 0, 0);
    float3 uvw = float3(index.x / 10.0f, index.y / 10.0f, index.z / 10.0f);
    uvw = float3(uvw.x, uvw.y, uvw.z);
    float3 c0 = float3(LPV3Dtex1.Sample(g_sampler, uvw).r, LPV3Dtex2.Sample(g_sampler, uvw).r, LPV3Dtex3.Sample(g_sampler, uvw).r);
    float3 c1 = float3(LPV3Dtex1.Sample(g_sampler, uvw).g, LPV3Dtex2.Sample(g_sampler, uvw).g, LPV3Dtex3.Sample(g_sampler, uvw).g);
    float3 c2 = float3(LPV3Dtex1.Sample(g_sampler, uvw).b, LPV3Dtex2.Sample(g_sampler, uvw).b, LPV3Dtex3.Sample(g_sampler, uvw).b);
    float3 c3 = float3(LPV3Dtex1.Sample(g_sampler, uvw).a, LPV3Dtex2.Sample(g_sampler, uvw).a, LPV3Dtex3.Sample(g_sampler, uvw).a);
    float4 SH = SHbase(radianceDir);
    E += PI * SH.r * c0;
    E += 2 / 3 * PI * SH.g * c1;
    E += 2 / 3 * PI * SH.b * c2;
    E += 2 / 3 * PI * SH.a * c3;
    return float4(E, 1.0f) / 3.14f;
}
int3 getindex(float3 pos)
{
    int3 ret;
    ret.x = (pos.x + 60) / 12;
    ret.y = pos.y / 10;
    ret.z = (pos.z + 60) / 12;
    return ret;
}

float2 SSR(float4 Q0V, float4 Q1V)
{
    float4 Q0VP = mul(Q0V, P);
    float4 Q1VP = mul(Q1V, P);
    float3 V0NDC = (Q0VP / Q0VP.w).xyz;
    float3 V1NDC = (Q1VP / Q1VP.w).xyz;
    float2 V0 = mul(float4(V0NDC, 1.0f), smuvmat).xy; //2D纹理空间线性插值起终点
    float2 V1 = mul(float4(V1NDC, 1.0f), smuvmat).xy; //2D纹理空间线性插值起终点
    float k0 = Q0VP.w;
    float k1 = Q1VP.w;
    float slope;
    int n = 0;
    float2 finaluv = float2(0, 0);
    
    if (V1.x - V0.x > V1.y - V0.y)
    {
        slope = (V1.y - V0.y) / (V1.x - V0.x);
        if (V1.x - V0.x > 0)
        {
            for (int i = 0; i < (V1.x - V0.x) / SSRdx; i++)
            {
                n++;
                if (n > 50)
                    break;
                if (SSRtest(V0, V1, float2(V0.x + i * SSRdx, V0.y + i * slope * SSRdy), k0, k1, Q0V.z, Q1V.z))
                {
                    finaluv = float2(V0.x + i * SSRdx, V0.y + i * slope * SSRdy);
                    break;

                }
                  
                
            }

        }
        else
        {
            for (int i = 0; i > (V1.x - V0.x) / SSRdx; i--)
            {
                n++;
                if (n > 50)
                    break;
                if (SSRtest(V0, V1, float2(V0.x + i * SSRdx, V0.y + i * SSRdy * slope), k0, k1, Q0V.z, Q1V.z))
                {
                    finaluv = float2(V0.x + i * SSRdx, V0.y + i * SSRdy * slope);
                    break;

                }
                
            }
        }
    }
    else
    {
        slope = (V1.x - V0.x) / (V1.y - V0.y);
        if (V1.y - V0.y > 0)
        {
            for (int i = 0; i < (V1.y - V0.y) / SSRdy; i++)
            {
                n++;
                if (n > 50)
                    break;
                if (SSRtest(V0, V1, float2(V0.x + i * SSRdx * slope, V0.y + i * SSRdy), k0, k1, Q0V.z, Q1V.z))
                {
                    finaluv = float2(V0.x + i * SSRdx * slope, V0.y + i * SSRdy);
                    break;

                }
                  
                
            }

        }
        else
        {
            for (int i = 0; i > (V1.y - V0.y) / SSRdy; i--)
            {
                n++;
                if (n > 50)
                    break;
                if (SSRtest(V0, V1, float2(V0.x + i * SSRdx * slope, V0.y + i * SSRdy), k0, k1, Q0V.z, Q1V.z))
                {
                    finaluv = float2(V0.x + i * SSRdx * slope, V0.y + i * SSRdy);
                    break;

                }
                
            }
        }
    }
    return finaluv;
        
}
float4 PS(vertexout pin) : SV_Target
{
    float2 smuv = mul(pin.positionL, smuvmat).xy;
    float dis = pin.positionL.z; //在同一空间比较，都在NDC
 
   // float shadowfactor = calcShadowFactor(10.0f, dis, smuv);
   // float shadowfactor = calcShadowFactorVssm(10, dis, smuv);
  
    //float smx = frac(smuv.x * 1024.0f);
    //float smy = frac(smuv.y * 768.0f);
    //float results[4];
    //for (int i = 0; i < 2; i++)
    //{
    //    for (int j = 0; j < 2; j++)
    //        results[i * 2 + j] = (dis < g_smap.Sample(g_sampler, smuv + float2(sm_dx * i, sm_dy * j)).r + 0.05);

    //}
    //float shadowfactor;
    //for (int k = 0; k < 4; k++)
    //{
    //    shadowfactor += results[k];
    //}
    //shadowfactor /= 4;
   
    //shadowfactor = (shadowfactor + 1) / 2.0f;
    pin.normal = normalize(pin.normal);
    pin.tanegntU = normalize(pin.tanegntU);
    float3 normalW = normalize(mul(float4(pin.normal, 0.0f), worldinvT).xyz); //法线在坐标变化后得归一化
    float3 B = normalize(cross(normalW, pin.tanegntU));
    float3x3 TBN = float3x3(pin.tanegntU, B, normalW);
    float3 bumpednormal = normalize(((g_nmap.Sample(g_sampler, pin.uv).xyz)) * 2.0f - 1.0f); //-1到1的法线
    float3 bumpednormalW = normalize(mul(bumpednormal, TBN));
    float3 toeye = normalize(eyepos - pin.positionW); //必须得在世界坐标进行
    float4 texcolor;
    if (pin.color.x == 0 && pin.color.y == 0 && pin.color.z == 0)
    {
        texcolor = g_tex.Sample(g_sampler, pin.uv);
    }
    else
    {
        texcolor = float4(pin.color, 1.0f);

    }
    float3 r = -1.0f * toeye - (2 * dot(-1.0f * toeye, normalW)) * normalW;
    float3 lightdirnor = normalize(lightdir);
   
    float4 speculouscolor = g_skycube1.Sample(g_sampler, r);
    float3 h = normalize(toeye + lightdirnor); //半程向量
    float3 Emui = g_precomMap.Sample(g_sampler, float2(max(0.001, dot(bumpednormalW, toeye)), (1 - roughness)));
    float3 Emuo = g_precomMap.Sample(g_sampler, float2(max(0.001, dot(bumpednormalW, lightdirnor)), (1 - roughness)));
    float Eavg = g_precomavgMap.Sample(g_sampler, float2(0.5f, 1 - roughness)).x;
    //float3 fadd = Fadd((float3(1, 1, 1) - texcolor.xyz) / 100.0f, lightdirnor, bumpednormalW, Eavg);
    float3 Fms = fms(Emui, Emuo, Eavg);
    float3 diffuse = smooth_SurfaceDiff(r0, texcolor.xyz, bumpednormalW, lightdirnor, dot(bumpednormalW, toeye));
    float3 F = SchlickFresnel(r0, bumpednormalW, h);
    float G = smithG2(h, lightdirnor, bumpednormalW, roughness, dot(bumpednormalW, toeye), dot(h, toeye));
    float D = GGX(roughness, bumpednormalW, h);
    float3 BRDF = G * D * F / (4 * abs(dot(bumpednormalW, lightdirnor)) * abs(dot(bumpednormalW, toeye))) + Fms;
    float scale = g_LUT.Sample(g_sampler, float2(dot(bumpednormalW, toeye), 1 - roughness)).x;
    float bias = g_LUT.Sample(g_sampler, float2(dot(bumpednormalW, toeye), 1 - roughness)).y;
    float4 IBL = float4(speculouscolor.xyz * (F * scale + bias), 1.0f);
    //float4 AL =  texcolor / 3.1415926f;
    float4 SSAOVP = mul(float4(pin.positionW, 1.0f), VP);
    float4 SSAOVPNDC = SSAOVP / SSAOVP.w;
    float2 SSAOuv = mul(SSAOVPNDC, smuvmat).xy;
    float4 AL = g_ssaomap.Sample(g_sampler, SSAOuv).r * float4(0.6f, 0.6f, 0.6f, 1.0f) * texcolor / 3.1415926f;
    //float AL = g_ssaomap.Sample(g_sampler, SSAOuv).r;
    //return AL;
    //return texcolor * float4(0.6f, 0.6f, 0.6f, 1.0f) / 3.1415926f;
    //return IBL;
    float2 lightuv = mul(mul(float4(pin.positionW, 1.0f), S), smuvmat).xy;
    float3 Q0 = pin.positionW; //世界坐标
    float3 Q1 = Q0 + 100 * normalize(r);
    float4 Q0V = mul(float4(Q0, 1.0f), V); //齐次裁剪坐标
    float4 Q1V = mul(float4(Q1, 1.0f), V);
    float2 SSRintersect = SSR(Q0V, Q1V);
    float4 SSRsample;
    if (SSRintersect.x == 0 && SSRintersect.y == 0)
    {
        SSRsample = g_skycube1.Sample(g_sampler, normalize(r));
    }
    else
    {
        SSRsample = g_lastFrame.Sample(g_sampler, SSRintersect);
    }
    float3 indirectLight = float3(0, 0, 0);
    indirectLight = SSRsample.xyz;
    
    //RSM算法
    
    
    //for (int j = 0; j < 400; j++)
    //{
    //    float randnum1 = random(float2(j * 20, j * 40));
    //    float randnum2 = random(float2(j * 40, j * 20));
    //    float2 sampleuv = float2(lightuv.x + 1.0f * randnum1 * sin(2 * 3.14159f * randnum2), lightuv.y + 1.0f * randnum1 * cos(2 * 3.14159f * randnum2));
    //    float3 RSMflux = g_fluxmap.Sample(g_sampler, sampleuv).xyz;
    //    float3 RSMnormal = (g_normalmap.Sample(g_sampler, sampleuv).xyz) * 2 - float3(1, 1, 1);
    //    float3 RSMworldpos = g_worldposmap.Sample(g_sampler, sampleuv).xyz;
    //    float3 pq = RSMworldpos * 200.0f - float3(100.0f, 100.0f, 100.0f) - pin.positionW;
    //    float3 normalpq = normalize(pq);
    //    float k;
    //    if (dot(-1 * normalpq, RSMnormal) <= 0)
    //    {
    //        k = 0;
    //    }
    //    else
    //    {
    //        k = 1;
    //    }
    //    float cos1 = dot(normalW, normalpq);
    //    float cos2 = dot(RSMnormal, -1 * normalpq);
    //    float dis = length(pq);
    //    float3 indirh = normalize(normalpq + toeye);
    //    float3 indirBRDF = SchlickFresnel(r0, bumpednormalW, indirh) * smithG2(indirh, normalpq, bumpednormalW, roughness, dot(bumpednormalW, toeye), dot(indirh, toeye)) * GGX(roughness, bumpednormalW, indirh) / (4 * max(0, dot(bumpednormalW, normalpq)) * max(0, dot(bumpednormalW, toeye)));
    //    indirectLight += RSMflux * max(0, cos1) * randnum1 * randnum1 * max(0, dot(-1 * normalpq, RSMnormal)) * 2 / (dis);

    //}
    
    
    //SSDO算法
    
    //float3 normalV = mul(float4(normalW, 0), V);
    //float4 posV = mul(float4(pin.positionW, 1.0f), V);
    //int rand = 1;
    //float As = 3.14159f * 10000 / 32;
    //for (int j = 0; i < 32; i++)
    //{
    //    rand++;
    //    float3 sampleVec = RandHemisphereUnitVec3new(float4(normalW, 0), j * j + 10, rand * 20);
    //    float randRadius = random(float2(rand * 10, i + 10));
    //    float3 samplePoint = pin.positionW + randRadius * sampleVec * 100;
    //    float4 sampleViewproject = mul(float4(samplePoint, 1.0f), VP); //采样点先变换到观察空间，再变化到裁剪空间。
    //    float4 sampleViewprojectNDC = sampleViewproject / sampleViewproject.w; //变化到NDC
    //    float2 sampleuv = mul(sampleViewprojectNDC, smuvmat).xy; //获得纹理空间的坐标
    //    float NDCdepthofMap = g_smap.Sample(g_sampler, sampleuv).r;
    //    float sampleViewdepth = NDCdepthToViewdepth(sampleViewprojectNDC.z);
    //    float viewDepthofMap = NDCdepthToViewdepth(NDCdepthofMap);
    //    float distz = sampleViewdepth - viewDepthofMap;
    //    float3 sampleView = mul(float4(samplePoint, 1.0f), V).xyz;
    //    float3 r = (viewDepthofMap / sampleViewdepth) * sampleView;
    //    float3 pq = normalize(r - posV.xyz);
    //    float3 mapnormal = g_SSDOnmap.Sample(g_sampler, sampleuv).xyz * 2 - float3(1, 1, 1);
    //    float3 mapnormalV = normalize(mul(float4(mapnormal, 0), V).xyz);
    //    float cos2 = max(0, dot(-1 * pq, mapnormalV));
    //    float k = 0;
    //    if (cos2 > 0)
    //        k = 1;
    //    float dp = max(0, dot(normalV, pq));
    //    float dis = max(0, length(samplePoint - pin.positionW));
    //    if (dis < 1)
    //        dis = 1;
    //    float4 DL = g_SSDODLmap.Sample(g_sampler, sampleuv);
    //    float3 indirectL = (occlusionFunc(distz) * DL * As * dp * cos2 / (dis * dis * 3.14)).xyz;
    //    //if (indirectL.x > 0.3 || indirectL.y > 0.3 || indirectL.z > 0.3)
    //    //    indirectL = float3(0, 0, 0);
    //    indirectLight = indirectLight + indirectL;
    //}
    

    return float4(indirectLight, 0.0f); //* + g_SSDODLmap.Sample(g_sampler,SSAOuv);  + texcolor / 3.14;
   
}