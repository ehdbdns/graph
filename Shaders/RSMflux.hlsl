
struct vertexin
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 noraml : NORMAL;
    float3 tangentU : TANGENT;
    float3 color : COLOR;
};
struct vertexout
{
    float4 positionH : SV_POSITION;
    float3 positionW : POSITIONT;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tanegntU : TANGENT;
    float3 color : COLOR;
};
Texture2D g_tex : register(t0);
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
    float4x4 S;
}
cbuffer objcb : register(b1)
{
    float4x4 world;
    float4x4 worldinvT;
}
vertexout VS(vertexin pin)
{
    vertexout vout;
   // float4 posW = mul(pin.position, world);
    vout.positionH = mul(pin.position, S);
    vout.uv = pin.uv;
    vout.color = pin.color;
 //   vout.uv = pin.uv;
    return vout;
}
float4 PS(vertexout pin):SV_Target
{
    float4 texcolor;
    if (pin.color.x==0&&pin.color.y==0&&pin.color.z==0)
    {
    
         texcolor = g_tex.Sample(g_sampler, pin.uv);
    }
    else
    {
        texcolor = float4(pin.color, 1.0f);
    }
    return texcolor;
}