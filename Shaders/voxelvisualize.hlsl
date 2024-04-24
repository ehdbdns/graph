

struct vertexin
{
    float4 mv4LocalPos : POSITION;
    float3 noraml : NORMAL;
    float3 center : CENTER;
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
    float3 center : CENTER;
};
Texture2D g_tex : register(t0);
Texture2D g_nmap : register(t1);
TextureCube g_skycube1 : register(t2);
SamplerState g_sampler : register(s0);
Texture3D clipmapsr : register(t19);
Texture3D clipmapsr2 : register(t20);
Texture3D clipmapsr3 : register(t21);
Texture3D clipmapsr4 : register(t22);
Texture3D clipmapsr5 : register(t23);
Texture3D clipmapsr6 : register(t24);
RWTexture3D<float4> g_clipmap : register(u1);
RWTexture3D<float4> g_clipmap2 : register(u2);
RWTexture3D<float4> g_clipmap3 : register(u3);
RWTexture3D<float4> g_clipmap4 : register(u4);
RWTexture3D<float4> g_clipmap5 : register(u5);
RWTexture3D<float4> g_clipmap6 : register(u6);
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
#define minVoxelSize 1
#define TexSize 128
int4 getindex(float3 posW)
{
    float3 eyeToPos = posW-eyepos;
    int level = 0;
    float maxDis = max(max(abs(eyeToPos.x), abs(eyeToPos.y)), abs(eyeToPos.z));

    while (maxDis - minVoxelSize * pow(2, level) * TexSize/2 > 0)
    {
        level++;
        
    }
    int voxelSize = minVoxelSize * pow(2, level);
    int3 index = floor(eyeToPos / voxelSize);
    index += (TexSize / 2);
    return int4(index, level);
}

vertexout VS(vertexin pin)
{
    vertexout vout;
    float4 Position = float4(pin.mv4LocalPos.xyz, 1.0f);
    float4 posW = mul(Position, pin.mxModel2World);
    //posW += float4(0, 40.0f, 0, 0);
    vout.positionH = mul(posW, VP);
    vout.normal = pin.noraml;
    vout.positionW = posW;
    float3 center = mul(float4(pin.center, 1.0f), pin.mxModel2World).xyz;
    vout.center = center;
    return vout;
}
float4 PS(vertexout pin):SV_Target
{
    
    int4 indexandlevel = getindex(pin.center);
    float4 color = float4(0, 0, 0,0);
    switch (indexandlevel.w)
    {
        case 0:
        {
                color = g_clipmap[indexandlevel.xyz];
                //clip((color.x > 0 || color.y > 0 || color.z > 0) - 0.1f);
                return color;
                break;
            }
        case 1:{
                color = g_clipmap2[indexandlevel.xyz];
                //clip((color.x > 0 || color.y > 0 || color.z > 0) - 0.1f);
                return color;
                break;
            }
        case 2:{
                color = g_clipmap3[indexandlevel.xyz];
                //clip((color.x > 0 || color.y > 0 || color.z > 0) - 0.1f);
                return color;
                break;
            }
        case 3:{
                color = g_clipmap4[indexandlevel.xyz];
                //clip((color.x > 0 || color.y > 0 || color.z > 0) - 0.1f);
                return color;
                break;
            }
        case 4:{
                color = g_clipmap5[indexandlevel.xyz];
                //clip((color.x > 0 || color.y > 0 || color.z > 0) - 0.1f);
                return color;
                break;
            }
        case 5:{
                color = g_clipmap6[indexandlevel.xyz];
                //clip((color.x > 0 || color.y > 0 || color.z > 0) - 0.1f);
                return color;
          
                break;
            }
        
    }
    return color;
}