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
//cbuffer CB : register(b0)
//{
//    int lastmip;
//}
#define PI 3.1415926585f
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
#define frontSolidAngle 0.400669f
#define sideSolidAngle 0.423431f
void getAsideIndex(int3 voxelIndex,out int3 asideIndex[6]){
    for (int i = 0; i < 6; i++)
    {
        asideIndex[i] = int3(-1, -1, -1);
    }
    if (voxelIndex.z + 1 <= 10)
        asideIndex[0] = int3(voxelIndex.x, voxelIndex.y, voxelIndex.z + 1);
    if (voxelIndex.z - 1 >= 0)
        asideIndex[1] = int3(voxelIndex.x, voxelIndex.y, voxelIndex.z - 1);
    if (voxelIndex.y - 1 >= 0)
        asideIndex[2] = int3(voxelIndex.x, voxelIndex.y - 1, voxelIndex.z);
    if (voxelIndex.y + 1 <= 10)
        asideIndex[3] = int3(voxelIndex.x, voxelIndex.y + 1, voxelIndex.z);
   
    if (voxelIndex.x - 1 >= 0)
            asideIndex[4] = int3(voxelIndex.x - 1, voxelIndex.y, voxelIndex.z);

    if(voxelIndex.x+1<=10)
        asideIndex[5] = int3(voxelIndex.x + 1, voxelIndex.y, voxelIndex.z);

   
    
}
float4 getirradiance(float3 n, int3 index)
{
    //index += 0.5f;
    float3 E = float3(0, 0, 0);
    float3 c0 = float3(DstTexture[index].r, DstTexture2[index].r, DstTexture3[index].r);
    float3 c1 = float3(DstTexture[index].g, DstTexture2[index].g, DstTexture3[index].g);
    float3 c2 = float3(DstTexture[index].b, DstTexture2[index].b, DstTexture3[index].b);
    float3 c3 = float3(DstTexture[index].a, DstTexture2[index].a, DstTexture3[index].a);
    E += PI * SHbase(n).r * c0;
    E += 2 / 3 * PI * SHbase(n).g * c1;
    E += 2 / 3 * PI * SHbase(n).b * c2;
    E += 2 / 3 * PI * SHbase(n).a * c3;
    return float4(E, 1.0f)/PI;
}
float3 getCellCenter(int3 index)
{
    return int3(-60 + 6 + 12 * index.x, 5 + 10 * index.y, -60 + 6 + 12 * index.z);
}
float3 Direction[30] =
{ //上下左右前后 cell的顺序
    //都是先对着的面再边上的面
    float3(0, 0, 1),
    float3(0, -0.5, 1),
    float3(-0.5, 0, 1),
    float3(0, 0.5, 1),
    float3(0.5, 0, 1),
    
    float3(0, 0, -1),
    float3(0, -0.5, -1),
    float3(-0.5, 0, -1),
    float3(0, 0.5, -1),
    float3(0.5, 0, -1),
    
    float3(0, -1, 0),
    float3(-0.5, -1, 0),
    float3(0, -1, 0.5),
    float3(0.5, -1, 0),
    float3(0, -1, -0.5),
    
    float3(0, 1, 0),
    float3(0.5, 1, 0),
    float3(0, 1, -0.5),
    float3(-0.5, 1, 0),
    float3(0, 1, 0.5),
    
    float3(1, 0, 0),
    float3(1, 0, 0.5),
    float3(1, -0.5, 0),
    float3(1, 0, -0.5),
    float3(1, 0.5, 0),
    
    float3(-1, 0, 0),
    float3(-1, -0.5, 0),
    float3(-1, 0, -0.5),
    float3(-1, 0.5, 0),
    float3(-1, 0, 0.5)
};

void propagateLight(int3 voxelIndex)
{
    int3 asideIndex[6];
    getAsideIndex(voxelIndex, asideIndex);
    float3 L00 = float3(0, 0, 0);
    float3 L1m1 = float3(0, 0, 0);
    float3 L10 = float3(0, 0, 0);
    float3 L11 = float3(0, 0, 0);
    for (int i = 0; i < 6; i++)
    {
        if(asideIndex[i].x==-1)
            continue;
        float3 nd = normalize(Direction[i * 5]);
        float4 SH = SHbase(nd);
        L00 += getirradiance(normalize(Direction[i * 5]), asideIndex[i]) * frontSolidAngle*SH.x;
        L1m1 += getirradiance(normalize(Direction[i * 5]), asideIndex[i]) * frontSolidAngle*SH.y;
        L10 += getirradiance(normalize(Direction[i * 5]), asideIndex[i]) * frontSolidAngle*SH.z;
        L11 += getirradiance(normalize(Direction[i * 5]), asideIndex[i]) * frontSolidAngle*SH.w;
        nd = normalize(Direction[i * 5 + 1]-Direction[i*5]);
         SH = SHbase(nd);
        L00 += getirradiance(normalize(Direction[i * 5 + 1]), asideIndex[i]) * sideSolidAngle * SH.x;
        L1m1 += getirradiance(normalize(Direction[i * 5 + 1]), asideIndex[i]) * sideSolidAngle * SH.y;
        L10 += getirradiance(normalize(Direction[i * 5 + 1]), asideIndex[i]) * sideSolidAngle * SH.z;
        L11 += getirradiance(normalize(Direction[i * 5 + 1]), asideIndex[i]) * sideSolidAngle * SH.w;
        nd = normalize(Direction[i * 5 + 2] - Direction[i * 5]);
        SH = SHbase(nd);
        L00 += getirradiance(normalize(Direction[i * 5 + 2]), asideIndex[i]) * sideSolidAngle * SH.x;
        L1m1 += getirradiance(normalize(Direction[i * 5 + 2]), asideIndex[i]) * sideSolidAngle * SH.y;
        L10 += getirradiance(normalize(Direction[i * 5 + 2]), asideIndex[i]) * sideSolidAngle * SH.z;
        L11 += getirradiance(normalize(Direction[i * 5 + 2]), asideIndex[i]) * sideSolidAngle * SH.w;
        nd = normalize(Direction[i * 5 + 3] - Direction[i * 5]);
        SH = SHbase(nd);
        L00 += getirradiance(normalize(Direction[i * 5 + 3]), asideIndex[i]) * sideSolidAngle * SH.x;
        L1m1 += getirradiance(normalize(Direction[i * 5 + 3]), asideIndex[i]) * sideSolidAngle * SH.y;
        L10 += getirradiance(normalize(Direction[i * 5 + 3]), asideIndex[i]) * sideSolidAngle * SH.z;
        L11 += getirradiance(normalize(Direction[i * 5 + 3]), asideIndex[i]) * sideSolidAngle * SH.w;
        nd = normalize(Direction[i * 5 + 4] - Direction[i * 5]);
        SH = SHbase(nd);
        L00 += getirradiance(normalize(Direction[i * 5 + 4]), asideIndex[i]) * sideSolidAngle * SH.x;
        L1m1 += getirradiance(normalize(Direction[i * 5 + 4]), asideIndex[i]) * sideSolidAngle * SH.y;
        L10 += getirradiance(normalize(Direction[i * 5 + 4]), asideIndex[i]) * sideSolidAngle * SH.z;
        L11 += getirradiance(normalize(Direction[i * 5 + 4]), asideIndex[i]) * sideSolidAngle * SH.w;
    }
    //DeviceMemoryBarrier();
    GroupMemoryBarrierWithGroupSync();
    //DstTexture4[voxelIndex] = float4(L00.x, L1m1.x, L10.x, L11.x)+DstTexture[voxelIndex];
    //DstTexture5[voxelIndex] = float4(L00.y, L1m1.y, L10.y, L11.y) + DstTexture2[voxelIndex];
    //DstTexture6[voxelIndex] = float4(L00.z, L1m1.z, L10.z, L11.z) + DstTexture3[voxelIndex];
    DstTexture[voxelIndex] += float4(L00.x, L1m1.x, L10.x, L11.x);
    DstTexture2[voxelIndex] += float4(L00.y, L1m1.y, L10.y, L11.y);
    DstTexture3[voxelIndex] += float4(L00.z, L1m1.z, L10.z, L11.z);

}
[numthreads(1, 1, 1)]
void CS(uint2 GroupId : SV_GroupID,
				 uint GroupThreadIndex : SV_GroupIndex,
				 uint3 DispatchThreadId : SV_DispatchThreadID)
{

    propagateLight(DispatchThreadId);
  
    //GroupMemoryBarrierWithGroupSync();
}