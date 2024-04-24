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
[numthreads(2, 2, 2)]
void CS(uint2 GroupId : SV_GroupID,
				 uint GroupThreadIndex : SV_GroupIndex,
				 uint3 DispatchThreadId : SV_DispatchThreadID)
{

    DstTexture[DispatchThreadId] /= 100.0f;
    DstTexture2[DispatchThreadId] /= 100.0f;
    DstTexture3[DispatchThreadId] /= 100.0f;
  
}