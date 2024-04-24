
struct vertexin
{
    float4 mv4LocalPos : POSITION;
    float4 mv4LocalNormal : NORMAL;
    float2 mv2UV : TEXCOORD;
    float4x4 mxModel2World : WORLD;
    uint mnInstanceId : SV_InstanceID;
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
Texture2D g_tex : register(t0);
Texture2D g_nmap : register(t1);
TextureCube g_skycube1 : register(t2);
Texture3D LPV3Dtex1 : register(t9);
Texture3D LPV3Dtex2 : register(t10);
Texture3D LPV3Dtex3 : register(t11);
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
int3 getindex(float3 pos)
{
    int3 ret;
    ret.x = (pos.x + 60) / 12;
    ret.y = pos.y / 10;
    ret.z = (pos.z + 60) / 12;
    return ret;
}
vertexout VS(vertexin pin)
{
    vertexout vout;
    float4 posW = mul(pin.mv4LocalPos, pin.mxModel2World);
    vout.positionH = mul(posW, VP);
    vout.uv = pin.mv2UV;
    vout.normal = pin.mv4LocalNormal;
    vout.positionW = posW;
    return vout;
}
float4 getirradiance(float3 n, int3 index)
{
    index += 0.5f;
    float3 E = float3(0, 0, 0);
    float3 uvw = float3(index.x,index.y,index.z);
    uvw = float3(uvw.x, uvw.y, uvw.z);
    float3 c0 = float3(LPV3Dtex1.Sample(g_sampler, uvw).r, LPV3Dtex2.Sample(g_sampler, uvw).r, LPV3Dtex3.Sample(g_sampler, uvw).r);
    float3 c1 = float3(LPV3Dtex1.Sample(g_sampler, uvw).g, LPV3Dtex2.Sample(g_sampler, uvw).g, LPV3Dtex3.Sample(g_sampler, uvw).g);
    float3 c2 = float3(LPV3Dtex1.Sample(g_sampler, uvw).b, LPV3Dtex2.Sample(g_sampler, uvw).b, LPV3Dtex3.Sample(g_sampler, uvw).b);
    float3 c3 = float3(LPV3Dtex1.Sample(g_sampler, uvw).a, LPV3Dtex2.Sample(g_sampler, uvw).a, LPV3Dtex3.Sample(g_sampler, uvw).a);
    E += PI * SHbase(n).r * c0;
    E += 2/3*PI * SHbase(n).g * c1;
    E += 2/3*PI * SHbase(n).b * c2;
    E += 2 / 3 * PI * SHbase(n).a * c3;
    return float4(E, 1.0f);
}
float4 PS(vertexout pin) : SV_Target
{
    float3 n = normalize(pin.normal);
    int3 index = getindex(pin.positionW.xyz);
    float4 E = getirradiance(n, index);
    return E;
}