Texture2D<float4> SrcTexture : register(t0);
RWTexture2D<float4> DstTexture : register(u0);
SamplerState g_sampler : register(s0);
cbuffer CB : register(b0)
{
    int lastmip;
}

float getmin(int2 lastID)
{
    //float texelsize = 1 / (pow(2, 10 - lastmip));

 
    float d1 = SrcTexture[lastID + int2(0, 0)];
    float d2 = SrcTexture[lastID + int2(0, 1)];
    float d3 = SrcTexture[lastID + int2(1, 0)];
    float d4 = SrcTexture[lastID + int2(1, 1)];
    return min(min(d1, d2), min(d3, d4));
}
[numthreads(8, 8, 1)]
void CS(uint2 GroupId : SV_GroupID,
				 uint GroupThreadIndex : SV_GroupIndex,
				 uint2 DispatchThreadId : SV_DispatchThreadID)
{

    int2 lastID = DispatchThreadId * 2;
    float minZ = getmin(lastID);
    //if(minZ==0)
    //    minZ = 1;
    DstTexture[DispatchThreadId] = minZ;
    if (minZ != 1)
    {
    
        DstTexture[DispatchThreadId] = minZ - 0.5f;
    }
    else
    {
        DstTexture[DispatchThreadId] = minZ;
    }

   
    GroupMemoryBarrierWithGroupSync();
}