struct vertexin
{

    float3 position : POSITION;


};
struct vertexout
{
    float4 positionH : SV_POSITION;
    float3 positionW : POSITIONT;

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
float GGX(float3 alpha, float3 n, float3 h)
{
    alpha = alpha * alpha;
    float ret = (pow(alpha, 2) * Xplus(dot(h, n))) / (3.1415926585f * pow((1 + pow(dot(n, h), 2) * (alpha * alpha - 1)), 2));
    if (ret > 10)
        return 10 ;
    
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
    return (-1 + pow((1 + 1 / ( abs(dot(alpha, alpha)))), 0.5)) / 2;

}
float smithG2(float3 h, float3 l, float3 n, float roughness, float Dotnv, float Dothv)
{
    float a1 = dot(n, l) / (roughness * (pow((1 - pow(dot(n, l), 2)), 0.5)));
    float a2 = Dotnv / (roughness * (pow((1 - pow(Dotnv, 2)), 0.5)));

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
float3 Emu(float3 F0, float roughness, float3 v)
{
    float a = 0;
    float b = 0;
    float c = 0;
    float3 n = float3(0, 1.0f, 0);
    for (int j = 0; j < 50; j++)
    {
        float3 lit = normalize(UniformSampleHemisphere(float2(random(float2(j, j + 1024)), random(float2(j + 1, j + 1025)))).xyz);
        lit = float3(lit.x, lit.z, lit.y);
        float3 h = normalize(lit + v);
        float3 add = dot(lit, n) * SchlickFresnel(F0, n, h) * smithG2(h, lit, n, roughness, dot(n, v), dot(h, v)) * GGX(roughness, n, h) /
        (4 * abs(dot(n, lit)) * abs(dot(n, v)));

        a += add.x;
        b += add.y;
        c += add.z;
         
    }
    
    a /= 50.0000f;
    b /= 50.000f;
    c /= 50.000f;
  
    return float3(a * 2 * 3.1415926585f, b * 2 * 3.1415926585f, c * 2 * 3.1415926585f);
}
float3 aveEmu(float3 F0, float roughness)
{
    float3 outter = float3(0, 0, 0);
    for (int i = 0; i < 20; i++)
    {
     
        float mu = random(float2(i * i, i + 20));
        
        float3 emu = Emu(F0, roughness, float3(-1 * sqrt(1 - mu * mu), mu, 0));
        outter.x = outter.x + emu.x * 2 * mu;
        outter.y = outter.y + emu.y * 2 * mu;
        outter.z = outter.z + emu.z * 2 * mu;
    }
    outter /= 20.0f;
    return outter;

}
float3 fms(float3 v, float3 l, float3 F0, float roughness)
{

    float3 base1 = (1 - Emu(F0, roughness, v)) * (1 - Emu(F0, roughness, l));
    float3 base2 = 3.14159f * (1 - aveEmu(F0, roughness));
    return base1 / base2;
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
vertexout VS(vertexin pin)
{
    vertexout pout;
    pout.positionH = float4(pin.position, 1.0f);
    pout.positionW = pin.position;
    return pout;
}
float4 PS(vertexout pin) : SV_Target
{
    float mu = (pin.positionW.x + 1)/2;
    float sintheta = sqrt(1 - mu * mu);
    float3 v = float3(-sintheta, mu, 0);
    float roughness = (pin.positionW.y + 1.0f) / 2.0f;
    
    //float3 emu = Emu(float3(1.0f, 1.0f, 1.0f), roughness, v);
    float3 avgemu = aveEmu(float3(1, 1, 1), roughness);
    //return float4(emu.x, emu.y, emu.z, 1.0f);
    return float4(avgemu, 1.0f);

}