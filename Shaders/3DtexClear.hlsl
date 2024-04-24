Texture2D<float4> SrcTexture : register(t0);
Texture2D<float4> g_worldpos : register(t1);
Texture2D<float4> g_normal : register(t2);
Texture2D<float4> g_RSMflux : register(t3);
RWTexture3D<float4> DstTexture : register(u0);
RWTexture3D<float4> DstTexture2 : register(u1);
RWTexture3D<float4> DstTexture3 : register(u2);
RWTexture3D<float4> DstTexture4 : register(u3);
RWTexture3D<float4> DstTexture5 : register(u4);
RWTexture3D<float4> DstTexture6 : register(u5);
SamplerState g_sampler : register(s0);
#define RSMwidth 1024.0f
#define RSMheight 824.0f
cbuffer CB : register(b0)
{
    int lastmip;
}


[numthreads(2, 2, 2)]
void CS(uint2 GroupId : SV_GroupID,
				 uint GroupThreadIndex : SV_GroupIndex,
				 uint3 DispatchThreadId : SV_DispatchThreadID)
{

    DstTexture[DispatchThreadId] = float4(0, 0, 0, 0);
    DstTexture2[DispatchThreadId] = float4(0, 0, 0, 0);
    DstTexture3[DispatchThreadId] = float4(0, 0, 0, 0);
    DstTexture4[DispatchThreadId] = float4(0, 0, 0, 0);
    DstTexture5[DispatchThreadId] = float4(0, 0, 0, 0);
    DstTexture6[DispatchThreadId] = float4(0, 0, 0, 0);
   
    GroupMemoryBarrierWithGroupSync();
}