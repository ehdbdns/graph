Texture3D<float4> SrcTexture : register(t0);
RWTexture3D<float4> DstTexture : register(u0);
SamplerState g_sampler : register(s0);
cbuffer CB : register(b0)
{
    int lastmip;
}


[numthreads(8, 8, 8)]
void CS(uint2 GroupId : SV_GroupID,
				 uint GroupThreadIndex : SV_GroupIndex,
				 uint3 DispatchThreadId : SV_DispatchThreadID)
{

    float3 lastID = DispatchThreadId * 2;
    float3 size = 128 / pow(2, lastmip);
    float3 uvw = lastID/size;
    float dsize = 1 / size.x;
    float4 color = float4(0, 0, 0, 0);
     color += SrcTexture.SampleLevel(g_sampler, uvw, lastmip);
     color += SrcTexture.SampleLevel(g_sampler, uvw+float3(dsize,0,0), lastmip);
     color += SrcTexture.SampleLevel(g_sampler, uvw+float3(0,dsize,0), lastmip);
     color += SrcTexture.SampleLevel(g_sampler, uvw+float3(dsize,dsize,0), lastmip);
    color += SrcTexture.SampleLevel(g_sampler, uvw+float3(0,0,dsize), lastmip);
    color += SrcTexture.SampleLevel(g_sampler, uvw + float3(dsize, 0, dsize), lastmip);
    color += SrcTexture.SampleLevel(g_sampler, uvw + float3(0, dsize, dsize), lastmip);
    color += SrcTexture.SampleLevel(g_sampler, uvw + float3(dsize, dsize, dsize), lastmip);
    DstTexture[DispatchThreadId] =color/8 ;

   
    GroupMemoryBarrierWithGroupSync();
}