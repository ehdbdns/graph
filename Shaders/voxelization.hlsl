
struct vertexin
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 noraml : NORMAL;
    float3 tangentU : TANGENT;
    float AOk : AOk;
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
RWTexture3D<float4>g_clipmap : register(u1);
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

    while (maxDis - minVoxelSize*pow(2, level)*TexSize/2 > 0)
    {
        level++;
        
    }
    int voxelSize = minVoxelSize * pow(2, level);
    int3 index = floor(eyeToPos / voxelSize);
    index += (TexSize / 2);
    return int4(index, level);
}
int getMaxofNormal(float3 n)
{
    float maxn = max(max(n.x, n.y), n.z);
    if(maxn==n.x)
        return 1;
  else  if (maxn == n.y)
        return 2;
   else if (maxn == n.z)
        return 3;
    return 0;
}

vertexout VS(vertexin pin)
{
    vertexout vout;
    float4 Position = float4(pin.position.xyz, 1.0f);
    float4 posW = Position;
    int maxN = getMaxofNormal(pin.noraml);
    switch (maxN)
    {
        case 1:
            Position.xyz = Position.yzx;
            break;
        case 2:
            Position.xyz = Position.xzy;
            break;
        case 3:
            Position.xyz = Position.xyz;
            break;
    }
    vout.positionH = mul(Position, VP);
    vout.positionW = posW;
    vout.uv = pin.uv;
    vout.color = pin.color;
    return vout;
}
void PS(vertexout pin)
{
    int4 indexAndLevel = getindex(pin.positionW);
    int level = indexAndLevel.w;
    float4 texcolor;
    if (pin.color.x == 0 && pin.color.y == 0 && pin.color.z == 0)
    {
        texcolor.xyz = g_tex.Sample(g_sampler, pin.uv).xyz;
        texcolor.w = 0;
    }
    else
    {
        texcolor = float4(pin.color, 0);

    }
    //texcolor = float4(1.0f, 0, 0, 0);
    switch (level)
    {
        
        case 0:{
                //float4 voxelColor = g_clipmap[indexAndLevel.xyz];
                //int lastnum = voxelColor.w * 1000;
                //float3 color = voxelColor.xyz * lastnum;
                //color += texcolor.xyz;
                //g_clipmap[indexAndLevel.xyz] = float4(color / lastnum + 1, (lastnum+1)/1000);
                g_clipmap[indexAndLevel.xyz] = float4(texcolor);
            }
            break;
        case 1:{
                //float4 voxelColor = g_clipmap2[indexAndLevel.xyz];
                //int lastnum = voxelColor.w * 1000;
                //float3 color = voxelColor.xyz * lastnum;
                //color += texcolor.xyz;
                //g_clipmap2[indexAndLevel.xyz] = float4(color / lastnum + 1, (lastnum + 1) / 1000);
                g_clipmap2[indexAndLevel.xyz] = float4(texcolor);
            }
            break;
        case 2:{
                //float4 voxelColor = g_clipmap3[indexAndLevel.xyz];
                //int lastnum = voxelColor.w * 1000;
                //float3 color = voxelColor.xyz * lastnum;
                //color += texcolor.xyz;
                //g_clipmap3[indexAndLevel.xyz] = float4(color / lastnum + 1, (lastnum + 1) / 1000);
                g_clipmap3[indexAndLevel.xyz] = float4(texcolor);
            }
            break;
        case 3:{
                //float4 voxelColor = g_clipmap4[indexAndLevel.xyz];
                //int lastnum = voxelColor.w * 1000;
                //float3 color = voxelColor.xyz * lastnum;
                //color += texcolor.xyz;
                //g_clipmap4[indexAndLevel.xyz] = float4(color / lastnum + 1, (lastnum + 1) / 1000);
                g_clipmap4[indexAndLevel.xyz] = float4(texcolor);
            }
            break;
        case 4:{
                //float4 voxelColor = g_clipmap5[indexAndLevel.xyz];
                //int lastnum = voxelColor.w * 1000;
                //float3 color = voxelColor.xyz * lastnum;
                //color += texcolor.xyz;
                //g_clipmap5[indexAndLevel.xyz] = float4(color / lastnum + 1, (lastnum + 1) / 1000);
                g_clipmap5[indexAndLevel.xyz] = float4(texcolor);
            }
            break;
        case 5:{
                //float4 voxelColor = g_clipmap6[indexAndLevel.xyz];
                //int lastnum = voxelColor.w * 1000;
                //float3 color = voxelColor.xyz * lastnum;
                //color += texcolor.xyz;
                //g_clipmap6[indexAndLevel.xyz] = float4(color / lastnum + 1, (lastnum + 1) / 1000);
                g_clipmap6[indexAndLevel.xyz] = float4(texcolor);
            }
          
            break;
    }
}