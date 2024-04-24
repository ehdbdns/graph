Texture2D<float4> SrcTexture : register(t0);
Texture2D<float4> g_worldpos : register(t1);
Texture2D<float4> g_normal : register(t2);
Texture2D<float4> g_RSMflux : register(t3);
RWTexture3D<float4> DstTexture : register(u0);
RWTexture3D<float4> DstTexture2 : register(u1);
RWTexture3D<float4> DstTexture3 : register(u2);
SamplerState g_sampler : register(s0);
#define RSMwidth 1024.0f
#define RSMheight 824.0f
cbuffer CB : register(b0)
{
    int lastmip;
}
#define PI 3.1415926585f
#define SH_C0 0.282094792f // 1 / 2sqrt(pi)
#define SH_C1 0.488602512f // sqrt(3/pi) / 2

float4 SHbase(float3 n)
{
    float Y[4];
    Y[0] = SH_C0;
    Y[1] =SH_C1 * n.y;
    Y[2] = SH_C1 * n.z;
    Y[3] = SH_C1 * n.x;
    return float4(Y[0],Y[1],Y[2],Y[3]);
}
int3 getindex(float3 pos)
{
    int3 ret;
    ret.x = (pos.x + 60) / 12;
    ret.y = pos.y / 10;
    ret.z = (pos.z + 60) / 12;
    return ret;
}
float3 getCenter(int3 index)
{
    return float3(-60 + 6 + 12 * index.x, 5 + index.y * 10, -60 + 6 + 12 * index.z);
}
void injectLight(int2 RSMindex)
{

            float2  uv = float2(RSMindex.x / RSMwidth, RSMindex.y / RSMheight);
            float4 RSMcolor = g_RSMflux.SampleLevel(g_sampler, uv,0);
            float3 pos = g_worldpos.SampleLevel(g_sampler, uv,0).xyz*200.0f-100.0f;
            float3 n = normalize(g_normal.SampleLevel(g_sampler, uv, 0).xyz * 2.0f - 1.0f);
            pos += n * float3(6, 5, 6);
            int3 index = getindex(pos);
    float3 center = getCenter(index);
    float3 vplToCenter = normalize(center - pos);
    float4 SH = SHbase(vplToCenter);
    DstTexture[index] += RSMcolor.x * SH   / 100;
    DstTexture2[index] += RSMcolor.y * SH  / 100;
    DstTexture3[index] += RSMcolor.z * SH  / 100;
    
    
    


}
[numthreads(4, 4, 1)]
void CS(uint2 GroupId : SV_GroupID,
				 uint GroupThreadIndex : SV_GroupIndex,
				 uint2 DispatchThreadId : SV_DispatchThreadID)
{

    injectLight(DispatchThreadId);
   
    GroupMemoryBarrierWithGroupSync();
}