struct vertexin
{

    float3 position : POSITION;
 
};
struct vertexout
{
    float4 positionH : SV_POSITION;
    float3 positionW : POSITIONT;
    float4 positionV : POSITIONT1;

};
Texture2D g_tex : register(t0);
Texture2D g_nmap : register(t1);
TextureCube g_skycube1 : register(t2);
Texture2D g_smap : register(t3);
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
float GGX(float alpha, float3 n, float3 h)
{
   // alpha = alpha * alpha;

    float ret = (pow(alpha, 2) * Xplus(dot(h, n))) / (3.1415926585f * pow((1 + pow(dot(n, h), 2) * (alpha * alpha - 1)), 2));
    if (ret > 1)
        return 1;
    
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
    H.y = SinTheta * sin(Phi);
    H.z = CosTheta;

    float PDF = 1.0 / (2 * 3.1415926f);

    return float4(H, PDF);
}
float lambda(float alpha)
{
    return (-1 + pow((1 + (1 / dot(alpha, alpha))), 0.500000f)) / 2;

}
float smithG2(float3 h, float3 l, float3 n, float roughness, float Dotnv, float Dothv)
{
    float a1 = dot(n, l) / (roughness * (pow((1 - pow(dot(n, l), 2)), 0.5000000f)));

    float a2 = Dotnv / (roughness * (pow((1 - pow(Dotnv, 2)), 0.500000f)));

    float base1 = 1 + lambda(a1) + lambda(a2);

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
    float randnum[4096];
  
}

float3 prefilter(float3 R,float roughness)
{
    float3 n = R;
    float3 o = R;
    int num = 0;
    int rand = 1;
    float3 ret1 = float3(0, 0, 0);
    float ret2 = float3(0, 0, 0);
    float3 up = float3(0.0f, 1.0f, 0); // abs(R.z) < 0.999 ? float3(0.0f, 0.0f, 1.0f) : float3(1.0f, 0.0f, 0.0f);
    float3 tangent = normalize(cross(up, R));
    float3 bitangent = cross(R, tangent);
    while (num <= 100)
    {
        rand++;
        num++;
        float PI = 3.1415926f;
        float randnum1 = random(float2(num * num + 10, rand * 2));
        float randnum2 = random(float2(rand * 2, num * num + 10));
        float a = roughness * roughness;
        float phi = 2.0f * PI *randnum1;
        float cosTheta = sqrt((1.0f - randnum2) / (1.0f + (a * a - 1.0f) * randnum2));
        float sinTheta = sqrt(1.0f - cosTheta * cosTheta);
        float3 H;//关于GGX重要性采样
        H.x = cos(phi) * sinTheta;
        H.y = sin(phi) * sinTheta;
        H.z = cosTheta;


        float3 sampleVec = tangent * H.x + bitangent * H.y + R * H.z;

        float3 h = normalize(sampleVec + o);
        float3 Lc = g_skycube1.Sample(g_sampler, sampleVec);
        float dotnl = dot(n, sampleVec);
        ret1 = ret1 + Lc *dotnl;
            ret2 = ret2 + dotnl;

    }
    ret1 /= 100.0f;
    ret2 /= 100.0f;
    return ret1 / ret2;
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

vertexout VS(vertexin pin)
{
    vertexout pout;
    float4 posv = mul(float4(pin.position, 1.0f), VP);
  
    pout.positionV = posv;
    pout.positionH = posv;
    pout.positionW = pin.position;
    return pout;
}
float4 PS(vertexout pin) : SV_Target
{
 
    float3 R = normalize(pin.positionW);
    return float4(prefilter(R, roughness), 1.0f);

}