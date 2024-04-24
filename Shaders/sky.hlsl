
struct vertexin
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};
struct vertexout
{
    float4 position : SV_POSITION;
    float3 uv : TEXCOORD;
};

TextureCube g_skycube : register(t0);
Texture2D g_nmap : register(t1);
TextureCube g_skycube1 : register(t2);
SamplerState g_sampler : register(s0);
cbuffer passcb : register(b0)
{
    float4x4 MWVP;
    float3 eyepos;
    float pad1;
    float3 AL;
    float pad2;
    float3 BL;
    float m;
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
}
cbuffer objcb : register(b1)
{
    float4x4 world;
    float4x4 invTworld;
}
vertexout VS(vertexin pin)
{
    vertexout vout;
    vout.uv = pin.position.xyz;
    pin.position += float4(eyepos,0.0f);
    float4x4 MVP = mul(world, VP);
    vout.position = mul(pin.position, MVP);
  
    return vout;
}
float4 PS(vertexout pin):SV_TARGET
{
    return g_skycube.Sample(g_sampler, pin.uv);
}