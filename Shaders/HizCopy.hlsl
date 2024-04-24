Texture2D<float4> SrcTexture : register(t0);
RWTexture2D<float4> DstTexture : register(u0);
SamplerState g_sampler : register(s0);
cbuffer CB : register(b0)
{
    int lastmip;
}


[numthreads(8, 8, 1)]
void CS(uint2 GroupId : SV_GroupID,
				 uint GroupThreadIndex : SV_GroupIndex,
				 uint2 DispatchThreadId : SV_DispatchThreadID)
{


     
        DstTexture[DispatchThreadId].rgba = SrcTexture[DispatchThreadId].rrrr;
        
    
   
    GroupMemoryBarrierWithGroupSync();
}