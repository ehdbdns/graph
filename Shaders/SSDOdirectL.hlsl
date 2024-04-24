struct vertexin
{

    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 noraml : NORMAL;
    float3 tangentU : TANGENT;
    float AOk : AOk;
    float3 color:COLOR;
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
    float4 positionVP : POSITIONT2;
    float AOk : AOk;
    float3 color : COLOR;
};
Texture2D g_tex : register(t0);
Texture2D g_nmap : register(t1);
TextureCube g_skycube1 : register(t2);
Texture2D g_depthmap : register(t3);
Texture2D g_precomMap : register(t4);
Texture2D g_precomavgMap : register(t5);
Texture2D g_LUT : register(t7);
Texture2D g_ssaomap : register(t8);
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
    float4x4 uvmat;
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

float random(float2 st)
{
   
    return frac(sin(dot(st.xy, float2(12.9898, 78.233))) * 43758.5453);
    
}

float4 UniformSampleHemisphere(float2 E)
{
    float Phi = 2 * 3.1415926f * E.x;
    float CosTheta = E.y;
    float SinTheta = sqrt(1 - CosTheta * CosTheta);

    float3 H;
    H.x = SinTheta * cos(Phi);
    H.z = SinTheta * sin(Phi);
    H.y = CosTheta;

    float PDF = 1.0 / (2 * 3.1415926f);

    return float4(H, PDF);
}

vertexout VS(vertexin pin)
{
    vertexout pout;
   
  
    float4 Position = pin.position;
//#ifdef SKINNED
    
//    Position = (pin.boneweights.x * mul(Position, finalmats[pin.boneindex.x]))
//    + (pin.boneweights.y * mul(Position, finalmats[pin.boneindex.y])) +
//    pin.boneweights.z * mul(Position, finalmats[pin.boneindex.z]) + pin.boneweights.w * mul(Position, finalmats[pin.boneindex.w]);

//#endif
    Position = float4(Position.xyz, 1.0f);
    pout.positionW = mul(Position, world).xyz;
    float4x4 MVP = mul(world, VP);
    float4 posmvp = mul(Position, MVP);
    pout.positionH = posmvp;
    pout.uv = pin.uv;
    pout.normal = pin.noraml;
    pout.tanegntU = pin.tangentU;
    pout.positionL = mul(float4(pout.positionW, 1.0f), S);
    pout.positionVP = mul(float4(pout.positionW, 1.0f), VP);
    pout.AOk = pin.AOk;
    pout.color = pin.color;
    return pout;
}
bool Vector3Greater(float3 v1, float3 v2)
{
    if (v1.x > v2.x && v1.y > v2.y && v1.z > v2.z)
        return true;
    return false;
}
bool Vector3Less(float3 v1, float3 v2)
{
    if (v1.x < v2.x && v1.y < v2.y && v1.z < v2.z)
        return true;
    return false;
}
float3 Vector3LengthSq(float4 v)
{
    float len2 = v.x * v.x + v.y * v.y + v.z * v.z;
    return float3(len2, len2, len2);
}

float3 RandHemisphereUnitVec3(float4 n, float num1, float num2)
{
    int i = 0;
    float3 One = float3(1.0f, 1.0f, 1.0f);
    float3 Zero = float3(0, 0, 0);
    float4 v = float4(1, 1, 1, 0);
    while (Vector3Greater(Vector3LengthSq(v), One) || Vector3Less(dot(n, v), Zero))
    {
        v = float4(2 * (random(float2(num1, num2)) - 0.5f), 2 * (random
        (float2(num2, num1)) - 0.5f), 2 * (random(float2(num1 * num1, num2 * num2)) - 0.5f), 0.0f);
    }
    return normalize(v).xyz;
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
float NDCdepthToViewdepth(float ndc)
{
    return P[3][2] / (ndc - P[2][2]);
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
float4 PS(vertexout pin) : SV_Target
{
    float3 normal = normalize(pin.normal);
    float3 normalV = mul(float4(normal, 0), V);
    float4 posV = mul(float4(pin.positionW, 1.0f), V);
    float4 posVP = mul(posV, P);
    float posViewDepth = NDCdepthToViewdepth((posVP / posVP.w).z);
    float4 DirectL = float4(0,0,0,0);
    int rand = 1;
    for (int i = 0; i < 16; i++)
    {
        rand++;
        float3 sampleVec = RandHemisphereUnitVec3new(float4(normal, 0), i * i + 10, rand * 20);
        float randRadius = random(float2(rand * 10, i + 10));
        float3 samplePoint = pin.positionW + randRadius * sampleVec * 5;
        float4 sampleViewproject = mul(float4(samplePoint, 1.0f), VP); //采样点先变换到观察空间，再变化到裁剪空间。
        float4 sampleViewprojectNDC = sampleViewproject / sampleViewproject.w; //变化到NDC
        float2 sampleuv = mul(sampleViewprojectNDC, uvmat).xy; //获得纹理空间的坐标
        float NDCdepthofMap = g_depthmap.Sample(g_sampler, sampleuv).r;
        float sampleViewdepth = NDCdepthToViewdepth(sampleViewprojectNDC.z);
        float viewDepthofMap = NDCdepthToViewdepth(NDCdepthofMap);
        float distz = sampleViewdepth - viewDepthofMap;
        float3 sampleView = mul(float4(samplePoint, 1.0f), V).xyz;
        float3 r = (viewDepthofMap / sampleViewdepth) * sampleView;
        float dp = max(0, dot(normalV, normalize(r - posV.xyz)));
        float4 texcolor;
        if (pin.color.x == 0 && pin.color.y == 0 && pin.color.z == 0)
        {
            texcolor = g_tex.Sample(g_sampler, pin.uv);
        }
        else
        {
            texcolor = float4(pin.color, 1.0f);

        }
        DirectL = DirectL + (1 - occlusionFunc(distz)) * dot(normal, sampleVec) * 2 * g_skycube1.Sample(g_sampler, sampleVec)*texcolor;
    }
    
    DirectL /= 16;
    return DirectL;
}