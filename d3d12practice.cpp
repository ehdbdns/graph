// d3d12practicelast.cpp : 定义应用程序的入口点。
//
#pragma once
#include"d3dUtil.h"
#include"textureLoader.h"
#include<cmath>
#include<process.h>
#include <atlcoll.h>
#include<windowsx.h>
#include"modelReader.h"
#define MAX_LOADSTRING 100
#define MAX_THREAD_NUM 9
#define GRS_WND_CLASS_NAME _T("GRS Game Window Class")
#define GRS_WND_TITLE	_T("GRS DirectX12 Trigger Sample")
HANDLE g_hOutput = 0;
UINT samplerindex = 0;
int framenum = 0;
UINT samplercount = 5;
#include <D3DCompiler.h>
UINT __stdcall threadfunc(void* ppara);
UINT __stdcall threadfuncnew(void* ppara);
class CGRSCOMException
{
public:
    CGRSCOMException(HRESULT hr) : m_hrError(hr)
    {
    }
    HRESULT Error() const
    {
        return m_hrError;
    }
private:
    const HRESULT m_hrError;
};
struct voxelVertex {
    XMFLOAT4 position;
    XMFLOAT3 normal;
    XMFLOAT3 center;
};
struct voxelInstanceData {
    XMFLOAT4X4 world;
};
struct Vertex
{
    XMFLOAT4 position;
    XMFLOAT2 uv;
    XMFLOAT3 normal;
    XMFLOAT3 TangentU;
    float AOk=0;
    XMFLOAT3 color;
};
struct LPVballVertex {
    XMFLOAT4 pos;
    XMFLOAT4 normal;
    XMFLOAT2 uv;
};
struct LPVballinstancedata {
    XMFLOAT4X4 world;
};

struct cubemapVertex {
    XMFLOAT3 position;
  
};
struct Hizmipsdata {
    int lastMiplevel;
};
struct passconstant {
    XMFLOAT4X4 MVP=MathHelper::Identity4x4();
    XMFLOAT3 eyepos;
    float pad1;
    XMFLOAT3 AL;
    float pad2;
    XMFLOAT3 BL;
    float m;
    XMFLOAT3 lightdir;
    float pad3;
    XMFLOAT4 md;
    XMFLOAT3 r0;
    float pad;
    XMFLOAT4X4 V;
    XMFLOAT4X4 W=MathHelper::Identity4x4();
    XMFLOAT4X4 VP;
    XMFLOAT4X4 WinvT;
    XMFLOAT4X4 P;
    XMFLOAT4X4 S;
    XMFLOAT3 lightPos;
    float pad5;
    XMFLOAT4X4 uvMAT;
    XMFLOAT4X4 invP;
    XMFLOAT4X4 invuvmat;
    float* randnum;
   // XMFLOAT4X4 offsetmat[58];
    XMFLOAT4X4 finalmats[58];
};
struct modelmat {
    XMFLOAT4X4 finalmats[58] = {MathHelper::Identity4x4()};
};
struct objectconstant {
    XMFLOAT4X4 world;
    XMFLOAT4X4 invTworld;
};
struct threadparas {
    UINT								nIndex;				//序号
    DWORD								dwThisThreadID;
    HANDLE								hThisThread;
    DWORD								dwMainThreadID;
    HANDLE								hMainThread;
    HANDLE								hRunEvent;
    HANDLE								hEventRenderOver;
    UINT								nCurrentFrameIndex;//当前渲染后缓冲序号
    ULONGLONG							nStartTime;		   //当前帧开始时间
    ULONGLONG							nCurrentTime;	   //当前时间
    XMFLOAT4							v4ModelPos;
    WCHAR*								pszDDSFile;
    std::vector<Vertex>    vertices;
    std::vector<modelVertex>    mvertices;
    std::vector<voxelVertex>*    voxelvertices;
   std::vector<std::uint16_t>indices;
   std::vector<std::uint16_t>*voxelindices;
    ID3D12Device4* device;
    ID3D12RootSignature* rs;
    ID3D12GraphicsCommandList* cmdlist;
    ID3D12CommandAllocator* cmdalloc;
    ID3D12PipelineState* PSO;
    passconstant passc;
    D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc;
    XMFLOAT4 md = { 0,0,0,0 };
    XMFLOAT3 r0 = { 0,0,0 };
    float m=0;
    ID3D12Resource* dsbuf;
    ID3D12Resource* SM;
    ID3D12Resource* cullaPrecompute;
    ID3D12Resource* cullaPrecomputeavg;
    ID3D12Resource* cullaPrecomputeFavg;
    ID3D12Resource* IBLLUT;
    ID3D12Resource* prefilterCube;
    ID3D12Resource* prefilterCube1;
    ID3D12Resource* prefilterCube2;
    ID3D12Resource* prefilterCube3;
    ID3D12Resource* prefilterCube4;
    ID3D12Resource* SSAOmap;
    ID3D12Resource* viewdepthmap;
    ID3D12Resource* RSMdepthmap;
    ID3D12Resource* RSMnormalmap;
    ID3D12Resource* RSMfluxmap;
    ID3D12Resource* RSMwposmap;
    ID3D12Resource* SSDODLmap;
    ID3D12Resource* SSDOnormalmap;
    //ID3D12Resource* FrameArr[3];
    ID3D12Resource* lastframe[2];
    ID3D12Resource* Hizmap;
    ID3D12Resource* LPVvoxel;
    ID3D12Resource* LPVvoxel2;
    ID3D12Resource* LPVvoxel3;
    ID3D12Resource* clipmap[6];
    ID3D12Resource* clipmapNormal[6];
    D3D12_VERTEX_BUFFER_VIEW(*            voxelvbv)[6][2];
    D3D12_INDEX_BUFFER_VIEW*            voxelibv;

};
struct threadparasnew {
    UINT								nIndex;				//序号
    DWORD								dwThisThreadID;
    HANDLE								hThisThread;
    DWORD								dwMainThreadID;
    HANDLE								hMainThread;
    HANDLE								hRunEvent;
    HANDLE								hEventRenderOver;
    UINT								nCurrentFrameIndex;//当前渲染后缓冲序号
    ULONGLONG							nStartTime;		   //当前帧开始时间
    ULONGLONG							nCurrentTime;	   //当前时间
    XMFLOAT4							v4ModelPos;
    WCHAR* pszDDSFile;
    WCHAR* skyFile;
    std::vector<Vertex>*    vertices;
    std::vector<std::uint16_t>*indices;
    ID3D12Device4* device;
    ID3D12RootSignature* rs;
    ID3D12GraphicsCommandList* cmdlist;
    ID3D12CommandAllocator* cmdalloc;
    ID3D12PipelineState* PSO;
    ID3D12PipelineState* skyPSO;
    ID3D12DescriptorHeap* rtvheap;
    passconstant passc;
    D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc;
    XMFLOAT4 md = { 0,0,0,0 };
    XMFLOAT3 r0 = { 0.5f,0.5f,0.5f };
    float m = 0;
    ID3D12Resource* SM;
};
void propagate(ID3D12GraphicsCommandList* cmdlist, ID3D12DescriptorHeap* heap, ID3D12Device4*device) {
   CD3DX12_GPU_DESCRIPTOR_HANDLE ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart());
   cmdlist->SetComputeRootDescriptorTable(2, ssaogpu);
  
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 12, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(0, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 46, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(1, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 43, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(4, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 44, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(5, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 45, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(6, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 47, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(7, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 48, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(8, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 49, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(9, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 50, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(10, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 51, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(11, ssaogpu);
    cmdlist->Dispatch(5, 5, 5);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 49, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(1, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 50, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(7, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 51, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(8, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 46, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(9, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 47, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(10, ssaogpu);
    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), 48, device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cmdlist->SetComputeRootDescriptorTable(11, ssaogpu);
    cmdlist->Dispatch(5, 5, 5);
}
void loadbvhVertex(BVHnode*node,std::vector<Vertex>*vertices) {
    if (node->left == nullptr || node->right == nullptr) {
        //for (int i = 0;i < node->triangles.size();i++) {
        //    Vertex v1, v2, v3;
        //    v1.position = XMFLOAT4{ node->triangles[i].pos[0].x, node->triangles[i].pos[0].y, node->triangles[i].pos[0].z,1.0f};
        //    v2.position = XMFLOAT4{ node->triangles[i].pos[1].x, node->triangles[i].pos[1].y, node->triangles[i].pos[1].z,1.0f};
        //    v3.position = XMFLOAT4{ node->triangles[i].pos[2].x, node->triangles[i].pos[2].y, node->triangles[i].pos[2].z,1.0f};
        //    vertices.push_back(v1);
        //    vertices.push_back(v2);
        //    vertices.push_back(v3);
        //}
        XMFLOAT3 c = node->box.Center;
        XMFLOAT3 e = node->box.Extents;
        Vertex v,v1,v2,v3,v4,v5,v6,v7;
        v.position = XMFLOAT4{c.x-e.x,c.y-e.y,c.z-e.z,1.0f};
        vertices->push_back(v);
        v1.position = XMFLOAT4{c.x-e.x,c.y-e.y,c.z+e.z,1.0f};
        vertices->push_back(v1);
        v2.position = XMFLOAT4{c.x+e.x,c.y-e.y,c.z-e.z,1.0f};
        vertices->push_back(v2);
        v3.position = XMFLOAT4{c.x+e.x,c.y-e.y,c.z+e.z,1.0f};
        vertices->push_back(v3);
        v4.position = XMFLOAT4{c.x-e.x,c.y+e.y,c.z-e.z,1.0f};
        vertices->push_back(v4);
        v5.position = XMFLOAT4{c.x-e.x,c.y+e.y,c.z+e.z,1.0f};
        vertices->push_back(v5);
        v6.position = XMFLOAT4{c.x+e.x,c.y+e.y,c.z-e.z,1.0f};
        vertices->push_back(v6);
        v7.position = XMFLOAT4{c.x+e.x,c.y+e.y,c.z+e.z,1.0f};
        vertices->push_back(v7);
    }
    else {
        loadbvhVertex(node->left,vertices);
        loadbvhVertex(node->right,vertices);
    }
}
XMFLOAT3 UniformSampleHemisphere(XMFLOAT2 E)
{
    float Phi = 2 * 3.1415926f * E.x;
    float CosTheta = E.y;
    float SinTheta = sqrt(1 - CosTheta * CosTheta);

    XMFLOAT3 H;
    H.x = SinTheta * cos(Phi);
    H.y = SinTheta * sin(Phi);
    H.z = CosTheta;

    float PDF = 1.0 / (2 * 3.1415926f);

    return XMFLOAT3{ H.x,H.z,H.y};
}
float calcAOk(Vertex v, BVHtree bvhtree) {
    float ret = 0;

    XMVECTOR nvec = XMVector3Normalize(XMLoadFloat3(&v.normal));

    for (int i = 0;i < 36;i++) {

        XMVECTOR sampleVec = MathHelper::RandHemisphereUnitVec3(nvec);
        XMVECTOR posvec = XMLoadFloat4(&v.position);
        float tmin=20;
        bvhtree.rayIntersect(posvec+nvec*0.01f, sampleVec, bvhtree.head, &tmin);
        float visibility;
        if (tmin >= 20)
            visibility = 1;
        else
            visibility = tmin / 400;   //  visibility = 0;// 
        XMVECTOR dotnl = XMVector3Dot(XMLoadFloat3(&v.normal), sampleVec);
        ret =ret+ visibility *XMVectorGetX(dotnl);
    }
    return ret * 2 / 36.0f;
}
meshdata subvide(meshdata mesh,int vsize,int isize) {
    std::vector<XMFLOAT3> vertices;
    std::vector<std::uint16_t> indices;
    for (int meshindex = 1;meshindex <= (isize / 3);meshindex++) {
        int a = mesh.indices[(meshindex - 1) * 3];//每个面源的点索引
        int b = mesh.indices[(meshindex - 1) * 3 + 1];
        int c = mesh.indices[(meshindex - 1) * 3 + 2];
        XMFLOAT3 v1 = XMFLOAT3{ (mesh.vertices[a].x + mesh.vertices[b].x) / 2,(mesh.vertices[a].y + mesh.vertices[b].y) / 2,(mesh.vertices[a].z + mesh.vertices[b].z) / 2 };
        XMFLOAT3 v2 = XMFLOAT3{ (mesh.vertices[b].x + mesh.vertices[c].x) / 2,(mesh.vertices[b].y + mesh.vertices[c].y) / 2,(mesh.vertices[b].z + mesh.vertices[c].z) / 2 };
        XMFLOAT3 v3 = XMFLOAT3{ (mesh.vertices[a].x + mesh.vertices[c].x) / 2,(mesh.vertices[a].y + mesh.vertices[c].y) / 2,(mesh.vertices[a].z + mesh.vertices[c].z) / 2 };
        vertices.push_back(mesh.vertices[a]);//0
        vertices.push_back(mesh.vertices[b]);//1
        vertices.push_back(mesh.vertices[c]);//2
        vertices.push_back(v1);//3
        vertices.push_back(v2);//4
        vertices.push_back(v3);//5
        int k = (meshindex - 1) * 6;
        indices.push_back(3+k);
        indices.push_back(1 + k);
        indices.push_back(4 + k);
        indices.push_back(0 +k);
        indices.push_back(3 + k);
        indices.push_back(5 + k);
        indices.push_back(3 + k);
        indices.push_back(4 + k);
        indices.push_back(5 + k);
        indices.push_back(5 + k);
        indices.push_back(4 + k);
        indices.push_back(2 + k);
    }
    meshdata ret;
    ret.vertices = vertices;
    ret.indices = indices;
    return ret;
}
UINT64 starttime = 0;
UINT64 currenttime = 0;
XMVECTOR eyepos = XMVectorSet(0.0f, 10.0f, -20.0f, 1.0f);
XMVECTOR target = XMVectorSet(0.0f, .0f, 1.0f, 0.0f);
XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
XMFLOAT2 mousepospre;
float theta, phi;
std::vector< boneAnimation> boneanimations;
std::vector<animationClips>animationclips ;
std::vector<XMFLOAT4X4>offsetMatrix;
std::vector<UINT> bonefamily;
float timesecond;
byte* SSAOmapped = nullptr;
byte* SSAOobjmapped = nullptr;
byte* SSRobjmapped = nullptr;
ComPtr<ID3D12DescriptorHeap>         pIRTVHeap;
ComPtr<ID3D12DescriptorHeap>         pIDSVHeap;
int iWidth = 1024;
int iHeight = 768;
modelReader mreader;
D3D12_VIEWPORT stViewPort = { 0.0f, 0.0f, static_cast<float>(iWidth), static_cast<float>(iHeight), D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
D3D12_VIEWPORT stSMViewPort = { 0.0f, 0.0f, static_cast<float>(2048), static_cast<float>(2048), D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
D3D12_RECT							stScissorRect = { 0, 0, static_cast<LONG>(iWidth), static_cast<LONG>(iHeight) };
D3D12_RECT							stSMScissorRect = { 0, 0, static_cast<LONG>(2048), static_cast<LONG>(2048) };
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int,HWND ,UINT,UINT);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void OnMouseDown(WPARAM wparam, int x, int y) {
    mousepospre.x = x;
    mousepospre.y = y;
}
void OnMouseMove(WPARAM wparam, int x, int y) {
    if ((wparam & MK_LBUTTON) != 0) {
        WriteConsole(g_hOutput, "1", 2, NULL, NULL);
        float dx = x - mousepospre.x;
        float dy =( y - mousepospre.y);
        float dtheta = XMConvertToRadians(0.25f * static_cast<float>(dx));
        float dphi = XMConvertToRadians(0.25f * static_cast<float>(dy));
        theta -= dtheta;
        phi -= dphi;
        if (phi >= XM_PI)
            phi -= XM_2PI;
        if (phi <= -XM_PI)
            phi += XM_2PI;
        if (theta >= XM_PI)
            theta -= XM_2PI;
        if (theta <= -XM_2PI)
            theta += XM_2PI;
        mousepospre.x = x;
        mousepospre.y = y;
    }
}
#define minVoxelSize 1
#define TexSize 128
void getindex(XMVECTOR posW,int(*index)[4])
{
    XMVECTOR eyeToPos = posW-eyepos;
    int level = 0;
    float maxDis =max( max(abs(XMVectorGetX(eyeToPos)), abs(XMVectorGetY(eyeToPos))),abs(XMVectorGetZ(eyeToPos)));

    while (maxDis - minVoxelSize * pow(2, level) * TexSize / 2 > 0)
    {
        level++;

    }
    int voxelSize = minVoxelSize * pow(2, level);
    XMVECTOR v = eyeToPos / voxelSize;
     (*index)[0] = floor(XMVectorGetX(v));
     (*index)[1] = floor(XMVectorGetY(v));
     (*index)[2] = floor(XMVectorGetZ(v));
     (*index)[0] += (TexSize / 2);
     (*index)[1] += (TexSize / 2);
     (*index)[2] += (TexSize / 2);
     (*index)[3] = level;
    
}
XMMATRIX lightviewproj;
XMMATRIX smuvmat(0.5f, 0.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f);
XMVECTOR lightposition = XMVectorSet(80.0f, 80.0f, 0, 0);
int countVoxelofLevel[6];
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    textureLoader texloader;
    HINSTANCE hInst;                                // 当前实例
    WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
    WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
    TCHAR								pszAppPath[MAX_PATH] = {};
    MSG  msg = {};

    // 此代码模块中包含的
    HWND hWnd = nullptr;
    AllocConsole();
    g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    const UINT nFrameBackBufCount = 3u;
  
    UINT nFrameIndex = 0;
    UINT nFrame = 0;
    float randarr[4096];
    UINT nDXGIFactoryFlags = 0U;
    UINT nRTVDescriptorSize = 0U;
    threadparas paras[MAX_THREAD_NUM];
    threadparasnew newparas[1];
    CAtlArray<HANDLE> HandleMessage[MAX_THREAD_NUM+1];
    CAtlArray<ID3D12CommandList*>cmdlists;
    float fAspectRatio = 3.0f;
    float rotationAngle = 0.0f;
 
  
    D3D12_VERTEX_BUFFER_VIEW stVertexBufferView = {};

    UINT64 n64FenceValue = 0ui64;
    HANDLE hFenceEvent = nullptr;
    UINT nSamplerDescriptorSize;
   
    ComPtr<ID3D12Resource>               pItex1UploadBuf;
    ComPtr<IDXGIFactory5>                pIDXGIFactory5;
    ComPtr<IDXGIAdapter1>                pIAdapter;
    ComPtr<ID3D12Device4>                pID3DDevice;
    ComPtr<ID3D12CommandQueue>           pICommandQueue;
    ComPtr<IDXGISwapChain1>              pISwapChain1;
    ComPtr<IDXGISwapChain1>              pIcullaSwapChain1;
    ComPtr<IDXGISwapChain3>              pISwapChain3;
    ComPtr<IDXGISwapChain3>              pIcullaSwapChain3;
   
    ComPtr<ID3D12Resource>               pIARenderTargets[nFrameBackBufCount];
    ComPtr<ID3D12Resource>               pIAcullaRenderTargets[2];
    ComPtr<ID3D12CommandAllocator>       pIcmdallpre;
    ComPtr<ID3D12CommandAllocator>       pIcmdallpost;
    ComPtr<ID3D12CommandAllocator>       pIcmdallssao;
    ComPtr<ID3D12RootSignature>          pIRootSignature;
    ComPtr<ID3D12RootSignature>          pICSRootSignature;
    ComPtr<ID3D12PipelineState>          pIPipelineState;
    ComPtr<ID3D12PipelineState>          pIwithoutPipelineState;
    ComPtr<ID3D12PipelineState>          pIwithoutPipelineStateModel;
    ComPtr<ID3D12PipelineState>          pIskyPSO;
    ComPtr<ID3D12PipelineState>          pISMPSO;
    ComPtr<ID3D12PipelineState>          pIRSMfluxPSO;
    ComPtr<ID3D12PipelineState>          pIRSMnormalPSO;
    ComPtr<ID3D12PipelineState>          pIRSMworldposPSO;
    ComPtr<ID3D12PipelineState>          pISSDOdirectLPSO;
    ComPtr<ID3D12PipelineState>          pISSDOnormalPSO;
    ComPtr<ID3D12PipelineState>          pISSRcolorBufferPSO;
    ComPtr<ID3D12PipelineState>          pIHi_zcomputePSO;
    ComPtr<ID3D12PipelineState>          pIHi_zcopyPSO;
    ComPtr<ID3D12PipelineState>          pIclip_levelPSO;
    ComPtr<ID3D12PipelineState>          pILPVinjectPSO;
    ComPtr<ID3D12PipelineState>          pILPVdiv100PSO;
    ComPtr<ID3D12PipelineState>          pILPVpropagatePSO;
    ComPtr<ID3D12PipelineState>          pILPVpropagationPSO;
    ComPtr<ID3D12PipelineState>          pI3DClearPSO;
    ComPtr<ID3D12PipelineState>          pImultiInstancePSO;
    ComPtr<ID3D12PipelineState>          pIVoxelizationPSO;
    ComPtr<ID3D12PipelineState>          pIVoxelizationNormalPSO;
    ComPtr<ID3D12PipelineState>          pIModelPSO;
    ComPtr<ID3D12PipelineState>          pIcullaPSO;
    ComPtr<ID3D12PipelineState>          pIIBLLUTPSO;
    ComPtr<ID3D12PipelineState>          pIviewDepthPSO;
    ComPtr<ID3D12PipelineState>          pISSAOPSO;
    ComPtr<ID3D12PipelineState>          pIcubePSO;
    ComPtr<ID3D12PipelineState>          pIcullaavgPSO;
    ComPtr<ID3D12PipelineState>          pIcullaFavgPSO;
    ComPtr<ID3D12PipelineState>          pIvoxelvisualizePSO;
    ComPtr<ID3D12GraphicsCommandList>    pIcmdlistpre;
    ComPtr<ID3D12GraphicsCommandList>    pIcmdlistpost;
    ComPtr<ID3D12GraphicsCommandList>    pIcmdlistssao;
    ComPtr<ID3D12Resource>               pIVertexBuffer;
    ComPtr<ID3D12Fence>                  pIFence;
    ComPtr<ID3D12Resource>               pItex1DefaultBuf;
    ComPtr<ID3D12Heap>                   pIUploadHeap;
    ComPtr<ID3D12DescriptorHeap>		 pISRVHeap;
    ComPtr<ID3D12DescriptorHeap>         pISamheap;
    ComPtr<ID3D12Resource>               pIIndexDefault;
    ComPtr<ID3D12Resource>               pIIndexUpload;
    ComPtr<ID3D12Resource>               pIpassCB;
    ComPtr<ID3D12Resource>               pIcubeCB[30];
    D3D12_INDEX_BUFFER_VIEW ibv;
    D3D12_INDEX_BUFFER_VIEW sphereibv;
    D3D12_VERTEX_BUFFER_VIEW spherevbv;
    D3D12_VERTEX_BUFFER_VIEW skyvbv;
    D3D12_INDEX_BUFFER_VIEW skyibv;
    passconstant currpasscb;
    ComPtr<ID3D12Heap>                  pIsphereuploadheap;
    ComPtr<ID3D12Heap>                  pIspheredefaultheap;
    ComPtr<ID3D12DescriptorHeap>                  pIcullacbvheap;
    ComPtr<ID3D12DescriptorHeap>                  pIcullasamheap;
    ComPtr<ID3D12Resource>              pIspherevb;
    ComPtr<ID3D12Resource>              pIspheredefaultvb;
    ComPtr<ID3D12Resource>              pIsphereib;
    ComPtr<ID3D12Resource>              pIspheredefaultib;
    ComPtr<ID3D12Resource>              pIskyuploadvb;
    ComPtr<ID3D12Resource>              pIskyuploadib;
    ComPtr<ID3D12Resource>              pIskytexupload;
    
    ComPtr<ID3D12Resource>              pIskytexdefault;
    ComPtr<ID3D12Resource>              pIsphereTextureCube;
    ComPtr<ID3D12Resource>              pIdsbuffer;
    DirectX::BoundingSphere             mboundingsphere;
    float mlightnearz;
    float mlightfarz;
    ComPtr<ID3D12Resource>              pIShadowMap;
    ComPtr<ID3D12DescriptorHeap>                  pIpresrvheap;
    ComPtr<ID3D12DescriptorHeap>                  pIpresamheap;
    ComPtr<ID3D12Resource>              pISMpassCB;
    ComPtr<ID3D12Resource>              pIRSMobjCB;
    ComPtr<ID3D12Resource>              pISSAOCB;
    ComPtr<ID3D12Resource>              pISSAOobjCB;
    ComPtr<ID3D12Resource>              pISSRobjCB;
    ComPtr<ID3D12Resource>              pIHizmipsCB[8];
    ComPtr<ID3D12Resource>              pIcullapassCB;
    ComPtr<ID3D12Resource>              pISMobjCB[4];
    ComPtr<ID3D12Resource>              pISMvb[3];
    ComPtr<ID3D12Resource>              pISMib[3];
    ComPtr<ID3D12Resource>              pIcullavb;
    ComPtr<ID3D12Resource>              RSMvb;
    ComPtr<ID3D12Resource>              LPVballvb;
    ComPtr<ID3D12Resource>              LPVballib;
    ComPtr<ID3D12Resource>              LPVballinstancedataB;
    ComPtr<ID3D12Resource>              pIssaovb;
    ComPtr<ID3D12Resource>              pIvoxelvb[6];
    ComPtr<ID3D12Resource>              pIvoxelInstanceBuffer[6];
    ComPtr<ID3D12Resource>              pIvoxelib;
    ComPtr<ID3D12Resource>              pIballvb;
    ComPtr<ID3D12Resource>              pIcullaib;
    ComPtr<ID3D12Resource>              RSMib;
    ComPtr<ID3D12Resource>              pIssaoib;
    ComPtr<ID3D12Resource>              pIballib;
    ComPtr<ID3D12Resource>              pIcubemapvb;
    ComPtr<ID3D12Resource>              pIcubemapib;
    D3D12_VERTEX_BUFFER_VIEW            SMvbv[3];
    D3D12_VERTEX_BUFFER_VIEW            cullavbv;
    D3D12_VERTEX_BUFFER_VIEW            RSMvbv;
    D3D12_VERTEX_BUFFER_VIEW            ssaovbv;
    D3D12_VERTEX_BUFFER_VIEW            voxelvbv[6][2];

    D3D12_VERTEX_BUFFER_VIEW            multivbv[2];

    D3D12_VERTEX_BUFFER_VIEW            ballvbv;
    D3D12_VERTEX_BUFFER_VIEW            cubevbv;
    D3D12_INDEX_BUFFER_VIEW            ssaoibv;
    D3D12_INDEX_BUFFER_VIEW            voxelibv;
    D3D12_INDEX_BUFFER_VIEW            multiibv[2];
    D3D12_INDEX_BUFFER_VIEW            ballibv;
    D3D12_INDEX_BUFFER_VIEW            SMibv[3];
    D3D12_INDEX_BUFFER_VIEW            cullaibv;
    D3D12_INDEX_BUFFER_VIEW            RSMibv;
    D3D12_INDEX_BUFFER_VIEW            cubeibv;
    ComPtr<ID3D12Resource>              SMtex1;
    ComPtr<ID3D12Resource>              SMtex2;
    ComPtr<ID3D12Resource>              SMtex3;
    ComPtr<ID3D12Resource>              SMtex1up;
    ComPtr<ID3D12Resource>              SMtex2up;
    ComPtr<ID3D12Resource>              SMtex3up;

    ComPtr<ID3D12Resource>              cullaPrecomputeEmu;
    ComPtr<ID3D12Resource>              cullaPrecomputeEmuavg;
    ComPtr<ID3D12Resource>              cullaPrecomputeFmuavg;
    ComPtr<ID3D12Resource>              IBLLUT;
    ComPtr<ID3D12Resource>              prefiltercubemap;
    ComPtr<ID3D12Resource>              prefiltercubemap1;
    ComPtr<ID3D12Resource>              prefiltercubemap2;
    ComPtr<ID3D12Resource>              prefiltercubemap3;
    ComPtr<ID3D12Resource>              prefiltercubemap4;
    ComPtr<ID3D12Resource>              SSAOmap;
    ComPtr<ID3D12Resource>              SSAOdepthmap;
    ComPtr<ID3D12Resource>              RSMdepthmap;
    ComPtr<ID3D12Resource>              RSMnormalmap;
    ComPtr<ID3D12Resource>              RSMfluxmap;
    ComPtr<ID3D12Resource>              RSMwposmap;
    ComPtr<ID3D12Resource>              SSDOdirectLightmap;
    ComPtr<ID3D12Resource>              SSDOnormalmap;
    ComPtr<ID3D12Resource>              SSDOposmap;
    ComPtr<ID3D12Resource>              headdiff;
    ComPtr<ID3D12Resource>              jacketdiff;
    ComPtr<ID3D12Resource>              pantsdiff;
    ComPtr<ID3D12Resource>              upbodydiff;
    ComPtr<ID3D12Resource>              headdiffup;
    ComPtr<ID3D12Resource>              jacketdiffup;
    ComPtr<ID3D12Resource>              pantsdiffup;
    ComPtr<ID3D12Resource>              upbodydiffup;
    ComPtr<ID3D12Resource>              lastframebuffer[2];
    ComPtr<ID3D12Resource>              colorBuffer;
    ComPtr<ID3D12Resource>              Hi_zMipmap;
    ComPtr<ID3D12Resource>              LPVvoxelTex;
    ComPtr<ID3D12Resource>              LPVvoxelTex2;
    ComPtr<ID3D12Resource>              LPVvoxelTex3;
    ComPtr<ID3D12Resource>              LPVvoxelTex4;
    ComPtr<ID3D12Resource>              LPVvoxelTex5;
    ComPtr<ID3D12Resource>              LPVvoxelTex6;
    ComPtr<ID3D12Resource>              clipMapArray[6];
    ComPtr<ID3D12Resource>              clipMapNormalArray[6];
    int ssaoflag = 0;
    byte* Hizmipsmap[8];
    int voxelTable[6][TexSize][TexSize][TexSize];

    std::vector<voxelVertex>voxelv;
    std::vector<std::uint16_t>voxeli;

try{
   // WriteConsole(g_hOutput, L"heihei", strlen("heihei"), NULL, NULL);
  
    {
        if (0 == ::GetModuleFileName(nullptr, pszAppPath, MAX_PATH))
        {
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }
     
        WCHAR* lastSlash = _tcsrchr(pszAppPath, _T('\\'));
        if (lastSlash)
        {//删除Exe文件名
            *(lastSlash) = _T('\0');
        }

        lastSlash = _tcsrchr(pszAppPath, _T('\\'));
        if (lastSlash)
        {//删除x64路径
            *(lastSlash) = _T('\0');
        }

        lastSlash = _tcsrchr(pszAppPath, _T('\\'));
        if (lastSlash)
        {//删除Debug 或 Release路径
            *(lastSlash + 1) = _T('\0');
        }
      //  WriteConsole(g_hOutput,pszAppPath, sizeof(pszAppPath), NULL, NULL);得到当前目录
    }
    {
        WNDCLASSEX wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_GLOBALCLASS;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);		//防止无聊的背景重绘
        wcex.lpszClassName = GRS_WND_CLASS_NAME;
        RegisterClassEx(&wcex);

        DWORD dwWndStyle = WS_OVERLAPPED | WS_SYSMENU;
        RECT rtWnd = { 0, 0, iWidth, iHeight };
        AdjustWindowRect(&rtWnd, dwWndStyle, FALSE);

        // 计算窗口居中的屏幕坐标
        INT posX = (GetSystemMetrics(SM_CXSCREEN) - rtWnd.right - rtWnd.left) / 2;
        INT posY = (GetSystemMetrics(SM_CYSCREEN) - rtWnd.bottom - rtWnd.top) / 2;

        hWnd = CreateWindowW(GRS_WND_CLASS_NAME
            , GRS_WND_TITLE
            , dwWndStyle
            , posX
            , posY
            , rtWnd.right - rtWnd.left
            , rtWnd.bottom - rtWnd.top
            , nullptr
            , nullptr
            , hInstance
            , nullptr);

        if (!hWnd)
        {
            return FALSE;
        }

        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);
    }

    // 打开显示子系统的调试支持
    {
#if defined(_DEBUG)
        ComPtr<ID3D12Debug> debugController;
        ComPtr<ID3D12Debug1>debugController1;
        ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
        debugController->EnableDebugLayer();
            debugController.As(&debugController1);
            debugController1->SetEnableGPUBasedValidation(true);
            // 打开附加的调试支持
            nDXGIFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        
#endif
    }



    {
        CreateDXGIFactory2(nDXGIFactoryFlags, IID_PPV_ARGS(&pIDXGIFactory5));
        ThrowIfFailed(pIDXGIFactory5->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER));
    }
    {
        DXGI_ADAPTER_DESC1 desc = {};
        for (UINT index = 0;DXGI_ERROR_NOT_FOUND != pIDXGIFactory5->EnumAdapters1(index, &pIAdapter);index++) {

            pIAdapter->GetDesc1(&desc);
            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
                continue;
            }
            if (SUCCEEDED(D3D12CreateDevice(pIAdapter.Get(), D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr)))
            {

                break;
            }
        }
        //try {
            ThrowIfFailed(D3D12CreateDevice(pIAdapter.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&pID3DDevice)));
       /* }
        catch (DxException& e) {
            WriteConsole(g_hOutput, e.ToString().c_str(), e.ToString().size(), NULL, NULL);
            while (1);
        }*/
        TCHAR pszWndTitle[MAX_PATH] = {};
        ThrowIfFailed(pIAdapter->GetDesc1(&desc));
        ::GetWindowText(hWnd, pszWndTitle, MAX_PATH);
     /*   StringCchPrintf(pszWndTitle
            , MAX_PATH
            , _T("%s (GPU:%s)")
            , pszWndTitle
            , desc.Description);*/
        ::SetWindowText(hWnd, pszWndTitle);
    }
    {
        D3D12_COMMAND_QUEUE_DESC commandqueuedesc = {};
        commandqueuedesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        ThrowIfFailed(pID3DDevice->CreateCommandQueue(&commandqueuedesc, IID_PPV_ARGS(&pICommandQueue)));
    }

    {
        DXGI_SWAP_CHAIN_DESC1 swapchaindesc = {};
        swapchaindesc.BufferCount = nFrameBackBufCount;
        swapchaindesc.Width = iWidth;
        swapchaindesc.Height =  iHeight;
        swapchaindesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swapchaindesc.SampleDesc.Count = 1;
        if (hWnd == nullptr)
            WriteConsole(g_hOutput, L"no", 3, NULL, NULL);
        ThrowIfFailed(pIDXGIFactory5->CreateSwapChainForHwnd(pICommandQueue.Get(), hWnd, &swapchaindesc, nullptr, nullptr, &pISwapChain1));
        swapchaindesc.BufferCount = 2;
        //ThrowIfFailed(pIDXGIFactory5->CreateSwapChainForHwnd(pICommandQueue.Get(), hWnd, &swapchaindesc, nullptr, nullptr, &pIcullaSwapChain1));
        ThrowIfFailed(pISwapChain1.As(&pISwapChain3));
        //ThrowIfFailed(pIcullaSwapChain1.As(&pIcullaSwapChain3));
        nFrameIndex = pISwapChain3->GetCurrentBackBufferIndex();

        D3D12_DESCRIPTOR_HEAP_DESC rtvheapdesc = {};
        rtvheapdesc.NumDescriptors = nFrameBackBufCount+6+3+6+1+4*6+1+3+1+1+2+1;//三个交换链，6个动态立方体，三个预计算 六个precubemap 一个IBLLUT 24个其余precubemap 1个SSAOmap 3个RSM渲染图(flux,normal,worldpos) 1个SSDOdirectmap  1个SSDOnormal（viewnormal） 2个lastframe 1个colorBuffer
        rtvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        ThrowIfFailed(pID3DDevice->CreateDescriptorHeap(&rtvheapdesc, IID_PPV_ARGS(&pIRTVHeap)));
        nRTVDescriptorSize = pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvcpuhandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart());
        for (UINT i = 0;i < 3;i++) {
            ThrowIfFailed(pISwapChain3->GetBuffer(i, IID_PPV_ARGS(&pIARenderTargets[i])));
            pID3DDevice->CreateRenderTargetView(pIARenderTargets[i].Get(), nullptr, rtvcpuhandle);
            rtvcpuhandle.Offset(1, nRTVDescriptorSize);
        }
    }
    D3D12_DESCRIPTOR_HEAP_DESC dsvheapdesc = {};
    dsvheapdesc.NumDescriptors = 4;//1+shadowmap+viewDepth+RSMdepthmap
    dsvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    dsvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    ThrowIfFailed(pID3DDevice->CreateDescriptorHeap(&dsvheapdesc, IID_PPV_ARGS(&pIDSVHeap)));
    {//跟签名
        D3D12_FEATURE_DATA_ROOT_SIGNATURE stFeatureData = {};
        // 检测是否支持V1.1版本的根签名
        stFeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
        if (FAILED(pID3DDevice->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &stFeatureData, sizeof(stFeatureData))))
        {
            stFeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
        }
        //描述符表
        CD3DX12_DESCRIPTOR_RANGE roottables[41] = {};
        roottables[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
        roottables[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, 0);
        roottables[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
        roottables[3].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1);
        roottables[4].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 2);
        roottables[5].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);
        roottables[6].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 3);
        roottables[7].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 2);
        roottables[8].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 4);//precube
        roottables[9].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 5);
        roottables[10].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 6);
        roottables[11].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 7);
        roottables[12].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 8);//ssao
        roottables[13].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 9);
        roottables[14].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 10);
        roottables[15].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 11);
        roottables[16].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 12);
        roottables[17].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 13);//SSDOnormal
        roottables[18].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 14);//lastframe
        roottables[19].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 15);//hiz
        roottables[20].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 16);//LPVVoxel
        roottables[21].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 17);//LPVVoxel2
        roottables[22].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 18);//LPVVoxel3
        roottables[23].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 1);//clipmap
        roottables[24].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 2);//clipmap
        roottables[25].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 3);//clipmap
        roottables[26].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 4);//clipmap
        roottables[27].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 5);//clipmap
        roottables[28].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 6);//clipmap

        roottables[29].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 19);//clipmap
        roottables[30].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 20);//clipmap
        roottables[31].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 21);//clipmap
        roottables[32].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 22);//clipmap
        roottables[33].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 23);//clipmap
        roottables[34].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 24);//clipmap

        roottables[35].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 25);//clipmapnormal
        roottables[36].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 26);//clipmap
        roottables[37].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 27);//clipmap
        roottables[38].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 28);//clipmap
        roottables[39].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 29);//clipmap
        roottables[40].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 30);//clipmap
       
        //跟参数
        CD3DX12_ROOT_PARAMETER rootparas[41] = {};
        rootparas[0].InitAsDescriptorTable(1, &roottables[0], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[1].InitAsDescriptorTable(1, &roottables[1], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[2].InitAsDescriptorTable(1, &roottables[2], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[3].InitAsDescriptorTable(1, &roottables[3], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[4].InitAsDescriptorTable(1, &roottables[4], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[5].InitAsDescriptorTable(1, &roottables[5], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[6].InitAsDescriptorTable(1, &roottables[6], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[7].InitAsDescriptorTable(1, &roottables[7], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[8].InitAsDescriptorTable(1, &roottables[8], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[9].InitAsDescriptorTable(1, &roottables[9], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[10].InitAsDescriptorTable(1, &roottables[10], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[11].InitAsDescriptorTable(1, &roottables[11], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[12].InitAsDescriptorTable(1, &roottables[12], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[13].InitAsDescriptorTable(1, &roottables[13], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[14].InitAsDescriptorTable(1, &roottables[14], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[15].InitAsDescriptorTable(1, &roottables[15], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[16].InitAsDescriptorTable(1, &roottables[16], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[17].InitAsDescriptorTable(1, &roottables[17], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[18].InitAsDescriptorTable(1, &roottables[18], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[19].InitAsDescriptorTable(1, &roottables[19], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[20].InitAsDescriptorTable(1, &roottables[20], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[21].InitAsDescriptorTable(1, &roottables[21], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[22].InitAsDescriptorTable(1, &roottables[22], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[23].InitAsDescriptorTable(1, &roottables[23], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[24].InitAsDescriptorTable(1, &roottables[24], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[25].InitAsDescriptorTable(1, &roottables[25], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[26].InitAsDescriptorTable(1, &roottables[26], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[27].InitAsDescriptorTable(1, &roottables[27], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[28].InitAsDescriptorTable(1, &roottables[28], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[29].InitAsDescriptorTable(1, &roottables[29], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[30].InitAsDescriptorTable(1, &roottables[30], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[31].InitAsDescriptorTable(1, &roottables[31], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[32].InitAsDescriptorTable(1, &roottables[32], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[33].InitAsDescriptorTable(1, &roottables[33], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[34].InitAsDescriptorTable(1, &roottables[34], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[35].InitAsDescriptorTable(1, &roottables[35], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[36].InitAsDescriptorTable(1, &roottables[36], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[37].InitAsDescriptorTable(1, &roottables[37], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[38].InitAsDescriptorTable(1, &roottables[38], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[39].InitAsDescriptorTable(1, &roottables[39], D3D12_SHADER_VISIBILITY_ALL);
        rootparas[40].InitAsDescriptorTable(1, &roottables[40], D3D12_SHADER_VISIBILITY_ALL);
  
     
        CD3DX12_ROOT_SIGNATURE_DESC rootdesc(41,rootparas, 0,nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        ComPtr<ID3DBlob>rootsignature = nullptr;
        ComPtr<ID3DBlob>error = nullptr;
        ThrowIfFailed(D3D12SerializeRootSignature(&rootdesc, D3D_ROOT_SIGNATURE_VERSION_1, rootsignature.GetAddressOf(), error.GetAddressOf()));
        assert(rootsignature != nullptr);
        ThrowIfFailed(pID3DDevice->CreateRootSignature(0, rootsignature->GetBufferPointer(), rootsignature->GetBufferSize(), IID_PPV_ARGS(&pIRootSignature)));
        assert(pIRootSignature != nullptr);







        //CS跟签名
        CD3DX12_DESCRIPTOR_RANGE csroottables[12] = {};
        csroottables[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
        csroottables[1].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 0);
        csroottables[2].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, 1, 0);
        csroottables[3].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
        csroottables[4].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1);
        csroottables[5].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 2);
        csroottables[6].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 3);
        csroottables[7].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 1);
        csroottables[8].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 2);
        csroottables[9].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 3);
        csroottables[10].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 4);
        csroottables[11].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 5);

        //跟参数
        CD3DX12_ROOT_PARAMETER csrootparas[12] = {};
        csrootparas[0].InitAsDescriptorTable(1, &csroottables[0], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[1].InitAsDescriptorTable(1, &csroottables[1], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[2].InitAsDescriptorTable(1, &csroottables[2], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[3].InitAsDescriptorTable(1, &csroottables[3], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[4].InitAsDescriptorTable(1, &csroottables[4], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[5].InitAsDescriptorTable(1, &csroottables[5], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[6].InitAsDescriptorTable(1, &csroottables[6], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[7].InitAsDescriptorTable(1, &csroottables[7], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[8].InitAsDescriptorTable(1, &csroottables[8], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[9].InitAsDescriptorTable(1, &csroottables[9], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[10].InitAsDescriptorTable(1, &csroottables[10], D3D12_SHADER_VISIBILITY_ALL);
        csrootparas[11].InitAsDescriptorTable(1, &csroottables[11], D3D12_SHADER_VISIBILITY_ALL);



        CD3DX12_ROOT_SIGNATURE_DESC csrootdesc(12, csrootparas, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        ComPtr<ID3DBlob>csrootsignature = nullptr;
        ComPtr<ID3DBlob>cserror = nullptr;
        ThrowIfFailed(D3D12SerializeRootSignature(&csrootdesc, D3D_ROOT_SIGNATURE_VERSION_1, csrootsignature.GetAddressOf(), cserror.GetAddressOf()));
        assert(csrootsignature != nullptr);
        ThrowIfFailed(pID3DDevice->CreateRootSignature(0, csrootsignature->GetBufferPointer(), csrootsignature->GetBufferSize(), IID_PPV_ARGS(&pICSRootSignature)));
        assert(pICSRootSignature != nullptr);
    }
    {
        ThrowIfFailed(pID3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pIcmdallpre)));
        ThrowIfFailed(pID3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pIcmdallpost)));
        ThrowIfFailed(pID3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pIcmdallssao)));
        ThrowIfFailed(pID3DDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pIcmdallpre.Get(), pIPipelineState.Get(), IID_PPV_ARGS(&pIcmdlistpre)));
        ThrowIfFailed(pID3DDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pIcmdallpost.Get(), pIPipelineState.Get(), IID_PPV_ARGS(&pIcmdlistpost)));
        ThrowIfFailed(pID3DDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pIcmdallssao.Get(), pIModelPSO.Get(), IID_PPV_ARGS(&pIcmdlistssao)));
    }

    {
        ComPtr<ID3DBlob>vsshader = nullptr;
        ComPtr<ID3DBlob>psshader = nullptr;
        ComPtr<ID3DBlob>skyvsshader = nullptr;
        ComPtr<ID3DBlob>skypsshader = nullptr;
        ComPtr<ID3DBlob>SMvsshader = nullptr;
        ComPtr<ID3DBlob>SMpsshader = nullptr;
        ComPtr<ID3DBlob>Mvsshader = nullptr;
        ComPtr<ID3DBlob>Mpsshader = nullptr;
        ComPtr<ID3DBlob>cullavsshader = nullptr;
        ComPtr<ID3DBlob>cullapsshader = nullptr;
        ComPtr<ID3DBlob>cullaavgvsshader = nullptr;
        ComPtr<ID3DBlob>cullaavgpsshader = nullptr;
        ComPtr<ID3DBlob>cubevsshader = nullptr;
        ComPtr<ID3DBlob>cubepsshader = nullptr;
        ComPtr<ID3DBlob>LUTvsshader = nullptr;
        ComPtr<ID3DBlob>LUTpsshader = nullptr;
        ComPtr<ID3DBlob>viewDepthvs = nullptr;
        ComPtr<ID3DBlob>viewDepthps = nullptr;
        ComPtr<ID3DBlob>SSAOvs = nullptr;
        ComPtr<ID3DBlob>SSAOps = nullptr;
        ComPtr<ID3DBlob>RSMfluxvs = nullptr;
        ComPtr<ID3DBlob>RSMfluxps = nullptr;
        ComPtr<ID3DBlob>RSMnormalvs = nullptr;
        ComPtr<ID3DBlob>RSMnormalps = nullptr;
        ComPtr<ID3DBlob>RSMwposvs = nullptr;
        ComPtr<ID3DBlob>RSMwposps = nullptr;
        ComPtr<ID3DBlob>SSDODLvs = nullptr;
        ComPtr<ID3DBlob>SSDODLps = nullptr;
        ComPtr<ID3DBlob>SSDOnormalvs = nullptr;
        ComPtr<ID3DBlob>SSDOnormalps = nullptr;
        ComPtr<ID3DBlob>SSRcolorvs = nullptr;
        ComPtr<ID3DBlob>SSRcolorps = nullptr;
        ComPtr<ID3DBlob>withoutssrvs = nullptr;
        ComPtr<ID3DBlob>withoutssrps = nullptr;
        ComPtr<ID3DBlob>Hi_zcs = nullptr;
        ComPtr<ID3DBlob>Hi_zCopycs = nullptr;
        ComPtr<ID3DBlob>LPVinjectcs = nullptr;
        ComPtr<ID3DBlob>LPVdiv100cs = nullptr;
        ComPtr<ID3DBlob>LPVpropagatecs = nullptr;
        ComPtr<ID3DBlob>clip_levelcs = nullptr;
        ComPtr<ID3DBlob>multivs = nullptr;
        ComPtr<ID3DBlob>multips = nullptr;
        ComPtr<ID3DBlob>Voxelizationvs = nullptr;
        ComPtr<ID3DBlob>Voxelizationps = nullptr;
        ComPtr<ID3DBlob>VoxelizationNormalvs = nullptr;
        ComPtr<ID3DBlob>VoxelizationNormalps = nullptr;
        ComPtr<ID3DBlob>Voxelvisualizevs = nullptr;
        ComPtr<ID3DBlob>Voxelvisualizeps = nullptr;
        ComPtr<ID3DBlob>DtexClearcs = nullptr;
#if defined(_DEBUG)
        UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
        UINT compileFlags = 0;
#endif
        compileFlags |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
        const D3D_SHADER_MACRO skinnedDefines[] =
        {
            "SKINNED", "1",
            NULL, NULL
        };

        vsshader = d3dUtil::CompileShader(L"Shaders//default.hlsl", nullptr, "VS", "vs_5_0");
        psshader = d3dUtil::CompileShader(L"Shaders//default.hlsl", nullptr, "PS", "ps_5_0");
        skyvsshader = d3dUtil::CompileShader(L"Shaders//sky.hlsl", nullptr, "VS", "vs_5_0");
        skypsshader = d3dUtil::CompileShader(L"Shaders//sky.hlsl", nullptr, "PS", "ps_5_0");
        SMvsshader = d3dUtil::CompileShader(L"Shaders//shadowmap.hlsl", nullptr, "VS", "vs_5_0");
        SMpsshader = d3dUtil::CompileShader(L"Shaders//shadowmap.hlsl", nullptr, "PS", "ps_5_0");
        Mvsshader = d3dUtil::CompileShader(L"Shaders//default.hlsl", skinnedDefines, "VS", "vs_5_0");
        Mpsshader = d3dUtil::CompileShader(L"Shaders//default.hlsl", skinnedDefines, "PS", "ps_5_0");
        cullavsshader = d3dUtil::CompileShader(L"Shaders//culla-conty.hlsl", nullptr, "VS", "vs_5_0");
        cullapsshader = d3dUtil::CompileShader(L"Shaders//culla-conty.hlsl", nullptr, "PS", "ps_5_0");
        cullaavgvsshader = d3dUtil::CompileShader(L"Shaders//culla-contyEavg.hlsl", nullptr, "VS", "vs_5_0");
        cullaavgpsshader = d3dUtil::CompileShader(L"Shaders//culla-contyEavg.hlsl", nullptr, "PS", "ps_5_0");
        cubevsshader = d3dUtil::CompileShader(L"Shaders//IBLprefilter.hlsl", nullptr, "VS", "vs_5_0");
        cubepsshader = d3dUtil::CompileShader(L"Shaders//IBLprefilter.hlsl", nullptr, "PS", "ps_5_0");
        LUTvsshader = d3dUtil::CompileShader(L"Shaders//IBLpostfilter.hlsl", nullptr, "VS", "vs_5_0");
        LUTpsshader = d3dUtil::CompileShader(L"Shaders//IBLpostfilter.hlsl", nullptr, "PS", "ps_5_0");
        viewDepthvs = d3dUtil::CompileShader(L"Shaders//viewDepth.hlsl", nullptr, "VS", "vs_5_0");
        viewDepthps = d3dUtil::CompileShader(L"Shaders//viewDepth.hlsl", nullptr, "PS", "ps_5_0");
        SSAOvs = d3dUtil::CompileShader(L"Shaders//SSAO.hlsl", nullptr, "VS", "vs_5_0");
        SSAOps = d3dUtil::CompileShader(L"Shaders//SSAO.hlsl", nullptr, "PS", "ps_5_0");
        RSMfluxvs = d3dUtil::CompileShader(L"Shaders//RSMflux.hlsl", nullptr, "VS", "vs_5_0");
        RSMfluxps = d3dUtil::CompileShader(L"Shaders//RSMflux.hlsl", nullptr, "PS", "ps_5_0");
        RSMnormalvs = d3dUtil::CompileShader(L"Shaders//RSMnormal.hlsl", nullptr, "VS", "vs_5_0");
        RSMnormalps = d3dUtil::CompileShader(L"Shaders//RSMnormal.hlsl", nullptr, "PS", "ps_5_0");
        RSMwposvs = d3dUtil::CompileShader(L"Shaders//RSMworldpos.hlsl", nullptr, "VS", "vs_5_0");
        RSMwposps = d3dUtil::CompileShader(L"Shaders//RSMworldpos.hlsl", nullptr, "PS", "ps_5_0");
        SSDODLvs = d3dUtil::CompileShader(L"Shaders//SSDOdirectL.hlsl", nullptr, "VS", "vs_5_0");
        SSDODLps = d3dUtil::CompileShader(L"Shaders//SSDOdirectL.hlsl", nullptr, "PS", "ps_5_0");
        SSDOnormalvs = d3dUtil::CompileShader(L"Shaders//SSDOnormal.hlsl", nullptr, "VS", "vs_5_0");
        SSDOnormalps = d3dUtil::CompileShader(L"Shaders//SSDOnormal.hlsl", nullptr, "PS", "ps_5_0");
        SSRcolorvs = d3dUtil::CompileShader(L"Shaders//SSRlastColorBuffer.hlsl", nullptr, "VS", "vs_5_0");
        SSRcolorps = d3dUtil::CompileShader(L"Shaders//SSRlastColorBuffer.hlsl", nullptr, "PS", "ps_5_0");
        withoutssrvs = d3dUtil::CompileShader(L"Shaders//withoutSSR.hlsl", nullptr, "VS", "vs_5_0");
        withoutssrps = d3dUtil::CompileShader(L"Shaders//withoutSSR.hlsl", nullptr, "PS", "ps_5_0");
        Hi_zcs = d3dUtil::CompileShader(L"Shaders//Hi_zCS.hlsl", nullptr, "CS", "cs_5_0");
        Hi_zCopycs = d3dUtil::CompileShader(L"Shaders//HizCopy.hlsl", nullptr, "CS", "cs_5_0");
        LPVinjectcs = d3dUtil::CompileShader(L"Shaders//LPVcreate3DTex.hlsl", nullptr, "CS", "cs_5_0");
        LPVdiv100cs = d3dUtil::CompileShader(L"Shaders//LPV3Dvoxeldiv100.hlsl", nullptr, "CS", "cs_5_0");
        LPVpropagatecs = d3dUtil::CompileShader(L"Shaders//propagation.hlsl", nullptr, "CS", "cs_5_0");
        DtexClearcs = d3dUtil::CompileShader(L"Shaders//3DtexClear.hlsl", nullptr, "CS", "cs_5_0");
        clip_levelcs = d3dUtil::CompileShader(L"Shaders//clip_level.hlsl", nullptr, "CS", "cs_5_0");
        multivs = d3dUtil::CompileShader(L"Shaders//multiInstance.hlsl", nullptr, "VS", "vs_5_0");
        multips = d3dUtil::CompileShader(L"Shaders//multiInstance.hlsl", nullptr, "PS", "ps_5_0");
        Voxelizationvs = d3dUtil::CompileShader(L"Shaders//voxelization.hlsl", nullptr, "VS", "vs_5_0");
        Voxelizationps = d3dUtil::CompileShader(L"Shaders//voxelization.hlsl", nullptr, "PS", "ps_5_0");
        VoxelizationNormalvs = d3dUtil::CompileShader(L"Shaders//voxelizationNormal.hlsl", nullptr, "VS", "vs_5_0");
        VoxelizationNormalps = d3dUtil::CompileShader(L"Shaders//voxelizationNormal.hlsl", nullptr, "PS", "ps_5_0");
        Voxelvisualizevs = d3dUtil::CompileShader(L"Shaders//voxelvisualize.hlsl", nullptr, "VS", "vs_5_0");
        Voxelvisualizeps = d3dUtil::CompileShader(L"Shaders//voxelvisualize.hlsl", nullptr, "PS", "ps_5_0");
        D3D12_INPUT_ELEMENT_DESC inputdesc[] = {
            {"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            {"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            {"TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            {"AOk",0,DXGI_FORMAT_R32_FLOAT, 0, 48, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            {"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
        };
    //    D3D12_INPUT_ELEMENT_DESC voxelinputdesc[] = {
    //{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    //{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    //{"CENTER",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    //    };
        D3D12_INPUT_ELEMENT_DESC modelinputdesc[] = {
       {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TANGENT",0,DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
          {"AOk",0,DXGI_FORMAT_R32_FLOAT, 0, 48, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
          {"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        
        {"WEIGHTS",0,DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"BONEINDICES",0,DXGI_FORMAT_R8G8B8A8_UINT, 0, 80, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
        };
        D3D12_INPUT_ELEMENT_DESC cullainputdesc[] = {
   {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
  
        };
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psodesc = {};
        //ZeroMemory(&psodesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
        psodesc.InputLayout = { inputdesc,_countof(inputdesc) };
        psodesc.pRootSignature = pIRootSignature.Get();
        psodesc.VS = { reinterpret_cast<BYTE*>(vsshader->GetBufferPointer()),vsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(psshader->GetBufferPointer()),psshader->GetBufferSize() };
        psodesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
        psodesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
        
        psodesc.BlendState.AlphaToCoverageEnable = FALSE;
        psodesc.BlendState.IndependentBlendEnable = FALSE;
        psodesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
        //psodesc.BlendState.RenderTarget[1].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

        psodesc.DepthStencilState.DepthEnable = TRUE;
        psodesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
        psodesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
        psodesc.DepthStencilState.StencilEnable = FALSE;
        psodesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

        psodesc.NumRenderTargets = 1;
        
        psodesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        //psodesc.RTVFormats[1] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psodesc.SampleMask = UINT_MAX;
        psodesc.SampleDesc.Count = 1;
        psodesc.SampleDesc.Quality = 0;
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIPipelineState)));
        //psodesc.InputLayout = { modelinputdesc,_countof(modelinputdesc) };
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
        psodesc.VS = { reinterpret_cast<BYTE*>(withoutssrvs->GetBufferPointer()),withoutssrvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(withoutssrps->GetBufferPointer()),withoutssrps->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIwithoutPipelineState)));
        psodesc.InputLayout = { modelinputdesc,_countof(modelinputdesc) };
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
        psodesc.VS = { reinterpret_cast<BYTE*>(withoutssrvs->GetBufferPointer()),withoutssrvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(withoutssrps->GetBufferPointer()),withoutssrps->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIwithoutPipelineStateModel)));
        psodesc.NumRenderTargets = 1;
        psodesc.SampleDesc.Count = 1;
        psodesc.InputLayout = { inputdesc,_countof(inputdesc) };
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
        psodesc.VS = { reinterpret_cast<BYTE*>(skyvsshader->GetBufferPointer()),skyvsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(skypsshader->GetBufferPointer()),skypsshader->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIskyPSO)));
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
        psodesc.VS = { reinterpret_cast<BYTE*>(SMvsshader->GetBufferPointer()),SMvsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(SMpsshader->GetBufferPointer()),SMpsshader->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pISMPSO)));
        psodesc.InputLayout = { modelinputdesc,_countof(modelinputdesc) };
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
        psodesc.VS = { reinterpret_cast<BYTE*>(Mvsshader->GetBufferPointer()),Mvsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(Mpsshader->GetBufferPointer()),Mpsshader->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIModelPSO)));
        psodesc.InputLayout = { cullainputdesc,_countof(cullainputdesc) };
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
        psodesc.VS = { reinterpret_cast<BYTE*>(cullavsshader->GetBufferPointer()),cullavsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(cullapsshader->GetBufferPointer()),cullapsshader->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIcullaPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(cullaavgvsshader->GetBufferPointer()),cullaavgvsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(cullaavgpsshader->GetBufferPointer()),cullaavgpsshader->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIcullaavgPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(cullaavgvsshader->GetBufferPointer()),cullaavgvsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(cullaavgpsshader->GetBufferPointer()),cullaavgpsshader->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIcullaFavgPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(cubevsshader->GetBufferPointer()),cubevsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(cubepsshader->GetBufferPointer()),cubepsshader->GetBufferSize() };
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIcubePSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(LUTvsshader->GetBufferPointer()),LUTvsshader->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(LUTpsshader->GetBufferPointer()),LUTpsshader->GetBufferSize() };
        psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIIBLLUTPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(viewDepthvs->GetBufferPointer()),viewDepthvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(viewDepthps->GetBufferPointer()),viewDepthps->GetBufferSize() };
        psodesc.InputLayout = { inputdesc,_countof(inputdesc) };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIviewDepthPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(SSAOvs->GetBufferPointer()),SSAOvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(SSAOps->GetBufferPointer()),SSAOps->GetBufferSize() };
        psodesc.InputLayout = { inputdesc,_countof(inputdesc) };

        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pISSAOPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(RSMfluxvs->GetBufferPointer()),RSMfluxvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(RSMfluxps->GetBufferPointer()),RSMfluxps->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIRSMfluxPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(RSMnormalvs->GetBufferPointer()),RSMnormalvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(RSMnormalps->GetBufferPointer()),RSMnormalps->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIRSMnormalPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(RSMwposvs->GetBufferPointer()),RSMwposvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(RSMwposps->GetBufferPointer()),RSMwposps->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIRSMworldposPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(SSDODLvs->GetBufferPointer()),SSDODLvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(SSDODLps->GetBufferPointer()),SSDODLps->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pISSDOdirectLPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(SSDOnormalvs->GetBufferPointer()),SSDOnormalvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(SSDOnormalps->GetBufferPointer()),SSDOnormalps->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pISSDOnormalPSO)));
        psodesc.VS = { reinterpret_cast<BYTE*>(SSRcolorvs->GetBufferPointer()),SSRcolorvs->GetBufferSize() };
        psodesc.PS = { reinterpret_cast<BYTE*>(SSRcolorps->GetBufferPointer()),SSRcolorps->GetBufferSize() };
        //psodesc.DS = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetGPUDescriptorHandleForHeapStart());
        ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pISSRcolorBufferPSO)));
        D3D12_COMPUTE_PIPELINE_STATE_DESC computePSOdesc = {};
        computePSOdesc.pRootSignature = pICSRootSignature.Get();
        computePSOdesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
        computePSOdesc.CS= { reinterpret_cast<BYTE*>(Hi_zcs->GetBufferPointer()),Hi_zcs->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateComputePipelineState(&computePSOdesc, IID_PPV_ARGS(&pIHi_zcomputePSO)));
        computePSOdesc.CS = { reinterpret_cast<BYTE*>(Hi_zCopycs->GetBufferPointer()),Hi_zCopycs->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateComputePipelineState(&computePSOdesc, IID_PPV_ARGS(&pIHi_zcopyPSO)));

        computePSOdesc.CS = { reinterpret_cast<BYTE*>(clip_levelcs->GetBufferPointer()),clip_levelcs->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateComputePipelineState(&computePSOdesc, IID_PPV_ARGS(&pIclip_levelPSO)));
        computePSOdesc.CS = { reinterpret_cast<BYTE*>(LPVinjectcs->GetBufferPointer()),LPVinjectcs->GetBufferSize() };
        
        ThrowIfFailed(pID3DDevice->CreateComputePipelineState(&computePSOdesc, IID_PPV_ARGS(&pILPVinjectPSO)));
        computePSOdesc.CS = { reinterpret_cast<BYTE*>(LPVdiv100cs->GetBufferPointer()),LPVdiv100cs->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateComputePipelineState(&computePSOdesc, IID_PPV_ARGS(&pILPVdiv100PSO)));
        computePSOdesc.CS = { reinterpret_cast<BYTE*>(LPVpropagatecs->GetBufferPointer()),LPVpropagatecs->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateComputePipelineState(&computePSOdesc, IID_PPV_ARGS(&pILPVpropagationPSO)));
        computePSOdesc.CS = { reinterpret_cast<BYTE*>(DtexClearcs->GetBufferPointer()),DtexClearcs->GetBufferSize() };
        ThrowIfFailed(pID3DDevice->CreateComputePipelineState(&computePSOdesc, IID_PPV_ARGS(&pI3DClearPSO)));
D3D12_INPUT_ELEMENT_DESC stIALayoutSphere[] =
{
                // 前三个是每顶点数据从插槽0传入
                { "POSITION",0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
                { "NORMAL",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0,16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
                { "TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT,      0,32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

                // 下面的是没实例数据从插槽1传入，前四个向量共同组成一个矩阵，将实例从模型局部空间变换到世界空间
                { "WORLD",   0, DXGI_FORMAT_R32G32B32A32_FLOAT,1, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 },
                { "WORLD",   1, DXGI_FORMAT_R32G32B32A32_FLOAT,1,16, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 },
                { "WORLD",   2, DXGI_FORMAT_R32G32B32A32_FLOAT,1,32, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 },
                { "WORLD",   3, DXGI_FORMAT_R32G32B32A32_FLOAT,1,48, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 }
       
            };
psodesc.InputLayout = { stIALayoutSphere, _countof(stIALayoutSphere) };
psodesc.VS = { reinterpret_cast<BYTE*>(multivs->GetBufferPointer()),multivs->GetBufferSize() };
psodesc.PS = { reinterpret_cast<BYTE*>(multips->GetBufferPointer()),multips->GetBufferSize() };
ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pImultiInstancePSO)));
psodesc.InputLayout = { inputdesc, _countof(inputdesc) };
psodesc.VS = { reinterpret_cast<BYTE*>(Voxelizationvs->GetBufferPointer()),Voxelizationvs->GetBufferSize() };
psodesc.PS = { reinterpret_cast<BYTE*>(Voxelizationps->GetBufferPointer()),Voxelizationps->GetBufferSize() };
ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIVoxelizationPSO)));
psodesc.VS = { reinterpret_cast<BYTE*>(VoxelizationNormalvs->GetBufferPointer()),VoxelizationNormalvs->GetBufferSize() };
psodesc.PS = { reinterpret_cast<BYTE*>(VoxelizationNormalps->GetBufferPointer()),VoxelizationNormalps->GetBufferSize() };
ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIVoxelizationNormalPSO)));
D3D12_INPUT_ELEMENT_DESC voxelinputdesc[] =
{
    // 前三个是每顶点数据从插槽0传入
    { "POSITION",0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0,16, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    { "CENTER",0, DXGI_FORMAT_R32G32B32_FLOAT,      0,28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

    // 下面的是没实例数据从插槽1传入，前四个向量共同组成一个矩阵，将实例从模型局部空间变换到世界空间
    { "WORLD",   0, DXGI_FORMAT_R32G32B32A32_FLOAT,1, 0, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 },
    { "WORLD",   1, DXGI_FORMAT_R32G32B32A32_FLOAT,1,16, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 },
    { "WORLD",   2, DXGI_FORMAT_R32G32B32A32_FLOAT,1,32, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 },
    { "WORLD",   3, DXGI_FORMAT_R32G32B32A32_FLOAT,1,48, D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA, 1 }

};
psodesc.VS = { reinterpret_cast<BYTE*>(Voxelvisualizevs->GetBufferPointer()),Voxelvisualizevs->GetBufferSize() };
psodesc.PS = { reinterpret_cast<BYTE*>(Voxelvisualizeps->GetBufferPointer()),Voxelvisualizeps->GetBufferSize() };
psodesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
psodesc.InputLayout = { voxelinputdesc,_countof(voxelinputdesc) };
ThrowIfFailed(pID3DDevice->CreateGraphicsPipelineState(&psodesc, IID_PPV_ARGS(&pIvoxelvisualizePSO)));
    //创建dsv
    //ThrowIfFailed(pIcmdallpre->Reset());
    //ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), nullptr));
    D3D12_RESOURCE_DESC dsdesc = {};
    dsdesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    dsdesc.Alignment = 0;
    dsdesc.Width = iWidth;
    dsdesc.Height = iHeight;
    dsdesc.DepthOrArraySize = 1;
    dsdesc.MipLevels = 1;
    dsdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsdesc.SampleDesc.Count = 1;
    dsdesc.SampleDesc.Quality = 0;
    dsdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    dsdesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    D3D12_CLEAR_VALUE dsclear = {};
    dsclear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsclear.DepthStencil.Depth = 1.0f;
    dsclear.DepthStencil.Stencil = 0;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &dsdesc, D3D12_RESOURCE_STATE_COMMON, &dsclear, IID_PPV_ARGS(&pIdsbuffer)));
    dsdesc.Width = iWidth;
    dsdesc.Height = iHeight;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &dsdesc, D3D12_RESOURCE_STATE_COMMON, &dsclear, IID_PPV_ARGS(&SSAOdepthmap)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &dsdesc, D3D12_RESOURCE_STATE_COMMON, &dsclear, IID_PPV_ARGS(&RSMdepthmap)));
    pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIdsbuffer.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
    pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSAOdepthmap.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
    pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMdepthmap.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
    //pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIARenderTargets[2].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvhandle(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvdesc = {};
    dsvdesc.Flags = D3D12_DSV_FLAG_NONE;
    dsvdesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvdesc.Texture2D.MipSlice = 0;
    pID3DDevice->CreateDepthStencilView(pIdsbuffer.Get(), &dsvdesc, dsvhandle);


  
    mboundingsphere.Center = XMFLOAT3{ 120.0f,0.0f,90 };
    mboundingsphere.Radius = 40.0f;
    //shadowmapdsv
    dsdesc.Width = iWidth;
    dsdesc.Height = iHeight;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &dsdesc, D3D12_RESOURCE_STATE_COMMON, &dsclear, IID_PPV_ARGS(&pIShadowMap)));
    pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIShadowMap.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
    dsvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV));
    pID3DDevice->CreateDepthStencilView(pIShadowMap.Get(), nullptr, dsvhandle);
    dsvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV));
    pID3DDevice->CreateDepthStencilView(SSAOdepthmap.Get(), nullptr, dsvhandle);
    dsvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV));
    pID3DDevice->CreateDepthStencilView(RSMdepthmap.Get(), nullptr, dsvhandle);

    mreader.readFileHeader("C:\\mytinyrenderproj\\d3d12practicelast\\d3d12practicelast\\soldier.m3d");
    animationclips = mreader.animationclips;
    offsetMatrix = mreader.offsetMatrix;
    bonefamily = mreader.boneFamily;
    //读取数据
    std::vector<BVHtriangle>bvhtris;
    bvhtris.resize(mreader.mindices.size() / 3);
    for (int i = 0;i < mreader.mindices.size() / 3;i++) {
        bvhtris[i].pos[0] = mreader.mvertices[mreader.mindices[i * 3]].position;
        bvhtris[i].pos[1] = mreader.mvertices[mreader.mindices[i * 3 + 1]].position;
        bvhtris[i].pos[2] = mreader.mvertices[mreader.mindices[i * 3 + 2]].position;
    }
    BVHtree bvhtree(bvhtris);
   
    std::vector<int>Vshared(mreader.mvertices.size());
    //for (int i = 0;i < mreader.mindices.size()/3;i++) {
    //    XMVECTOR v1 = XMLoadFloat3(&mreader.mvertices[mreader.mindices[i * 3]].position);
    //    XMVECTOR v2 = XMLoadFloat3(&mreader.mvertices[mreader.mindices[i * 3+1]].position);
    //    XMVECTOR v3 = XMLoadFloat3(&mreader.mvertices[mreader.mindices[i * 3+2]].position);
    //    XMVECTOR eg1 = v2 - v1;
    //    XMVECTOR eg2 = v3 - v1;
    //    XMVECTOR normal = XMVector3Normalize(XMVector3Cross(eg2, eg1));
    //    XMVECTOR gravity = (v1 + v2 + v3) / 3.0f;
    //    XMFLOAT3 gf3;
    //    XMStoreFloat3(&gf3, gravity);
    //    XMFLOAT4 gf4 = XMFLOAT4{ gf3.x,gf3.y,gf3.z,1.0f };
    //    Vertex v;
    //    v.position = gf4;
    //    XMStoreFloat3(&v.normal, normal);
    //    float AOk = calcAOk(v, bvhtree);
    //    mreader.mvertices[mreader.mindices[i * 3]].AOk += AOk;
    //    Vshared[mreader.mindices[i * 3]] += 1;
    //    mreader.mvertices[mreader.mindices[i * 3+1]].AOk += AOk;
    //    Vshared[mreader.mindices[i * 3+1]] += 1;
    //    mreader.mvertices[mreader.mindices[i * 3+2]].AOk += AOk;
    //    Vshared[mreader.mindices[i * 3+2]] += 1;

    //}
  //  for (int i = 0;i < mreader.mvertices.size();i++) {
  //      mreader.mvertices[i].AOk /= Vshared[i];
  //}
    std::vector<Vertex>bvhV;
    loadbvhVertex(bvhtree.head, &bvhV);
    std::vector<std::uint16_t>bvhI;
    for (int i = 0;i < bvhV.size()/8;i++) {
        bvhI.push_back(i*8);
        bvhI.push_back(i*8+1);
        bvhI.push_back(i*8+1);
        bvhI.push_back(i*8+3);
        bvhI.push_back(i*8+3);
        bvhI.push_back(i*8+2);
        bvhI.push_back(i*8+2);
        bvhI.push_back(i*8);
        bvhI.push_back(i*8+4);
        bvhI.push_back(i*8+5);
        bvhI.push_back(i*8+5);
        bvhI.push_back(i*8+7);

        bvhI.push_back(i * 8+7);
        bvhI.push_back(i * 8+6);
        bvhI.push_back(i * 8+6);
        bvhI.push_back(i * 8+4);
        bvhI.push_back(i * 8);
        bvhI.push_back(i * 8+4);
        bvhI.push_back(i * 8+1);
        bvhI.push_back(i * 8+5);
        bvhI.push_back(i * 8+2);
        bvhI.push_back(i * 8+6);
        bvhI.push_back(i * 8+3);
        bvhI.push_back(i * 8+7);
        
    }

    boneanimations.resize(5);
    
    boneanimations[0].keyframes.resize(4);
    //boneani的keyframes
    boneanimations[0].numkeyframe = 4;
    boneanimations[0].keyframes[0].starttime = 0;
    boneanimations[0].keyframes[0].translation = XMFLOAT3(-7.0f,0,0);
    boneanimations[0].keyframes[0].scale = XMFLOAT3(0.25f,0.25f,0.25f);
    XMStoreFloat4(&boneanimations[0].keyframes[0].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(22.5f)));//旋转轴的方向，需要原点确定具体的旋转轴
   
    boneanimations[0].keyframes[1].starttime = 2.0f;
    boneanimations[0].keyframes[1].translation = XMFLOAT3(-7.0f, 0, 0);
    boneanimations[0].keyframes[1].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[0].keyframes[1].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(45.0f)));
   
    boneanimations[0].keyframes[2].starttime = 4.0f;
    boneanimations[0].keyframes[2].translation = XMFLOAT3(-7.0f, 0, 0);
    boneanimations[0].keyframes[2].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[0].keyframes[2].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(67.5f)));
 
    boneanimations[0].keyframes[3].starttime = 6.0f;
    boneanimations[0].keyframes[3].translation = XMFLOAT3(-7.0f, 0, 0);
    boneanimations[0].keyframes[3].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[0].keyframes[3].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(90.0f)));



    boneanimations[1].keyframes.resize(4);
   
    boneanimations[1].numkeyframe = 4;
    boneanimations[1].keyframes[0].starttime = 0;
    boneanimations[1].keyframes[0].translation = XMFLOAT3(-10.0f, 0, 0);
    boneanimations[1].keyframes[0].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[1].keyframes[0].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));//旋转轴的方向，需要原点确定具体的旋转轴

    boneanimations[1].keyframes[1].starttime = 2.0f;
    boneanimations[1].keyframes[1].translation = XMFLOAT3(-10.0f, 0, 0);
    boneanimations[1].keyframes[1].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[1].keyframes[1].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));

    boneanimations[1].keyframes[2].starttime = 4.0f;
    boneanimations[1].keyframes[2].translation = XMFLOAT3(-10.0f, 0, 0);
    boneanimations[1].keyframes[2].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[1].keyframes[2].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));

    boneanimations[1].keyframes[3].starttime = 6.0f;
    boneanimations[1].keyframes[3].translation = XMFLOAT3(-10.0f, 0, 0);
    boneanimations[1].keyframes[3].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[1].keyframes[3].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));

    boneanimations[2].keyframes.resize(4);

    boneanimations[2].numkeyframe = 4;
    boneanimations[2].keyframes[0].starttime = 0;
    boneanimations[2].keyframes[0].translation = XMFLOAT3(-4.0f, 0, 0);
    boneanimations[2].keyframes[0].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[2].keyframes[0].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));//旋转轴的方向，需要原点确定具体的旋转轴

    boneanimations[2].keyframes[1].starttime = 2.0f;
    boneanimations[2].keyframes[1].translation = XMFLOAT3(-4.0f, 0, 0);
    boneanimations[2].keyframes[1].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[2].keyframes[1].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));

    boneanimations[2].keyframes[2].starttime = 4.0f;
    boneanimations[2].keyframes[2].translation = XMFLOAT3(-4.0f, 0, 0);
    boneanimations[2].keyframes[2].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[2].keyframes[2].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));

    boneanimations[2].keyframes[3].starttime = 6.0f;
    boneanimations[2].keyframes[3].translation = XMFLOAT3(-4.0f, 0, 0);
    boneanimations[2].keyframes[3].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[2].keyframes[3].quat, XMQuaternionRotationAxis(XMVectorSet(1.0f, .0f, 0, 0), XMConvertToRadians(0)));


    boneanimations[3].keyframes.resize(4);

    boneanimations[3].numkeyframe = 4;
    boneanimations[3].keyframes[0].starttime = 0;
    boneanimations[3].keyframes[0].translation = XMFLOAT3(5.0f, 0, 0);
    boneanimations[3].keyframes[0].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[3].keyframes[0].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(22.5f)));//旋转轴的方向，需要原点确定具体的旋转轴

    boneanimations[3].keyframes[1].starttime = 2.0f;
    boneanimations[3].keyframes[1].translation = XMFLOAT3(5.0f, 0, 0);
    boneanimations[3].keyframes[1].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[3].keyframes[1].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(45.0f)));

    boneanimations[3].keyframes[2].starttime = 4.0f;
    boneanimations[3].keyframes[2].translation = XMFLOAT3(5.0f, 0, 0);
    boneanimations[3].keyframes[2].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[3].keyframes[2].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(67.5f)));

    boneanimations[3].keyframes[3].starttime = 6.0f;
    boneanimations[3].keyframes[3].translation = XMFLOAT3(5.0f, 0, 0);
    boneanimations[3].keyframes[3].scale = XMFLOAT3(0.25f, 0.25f, 0.25f);
    XMStoreFloat4(&boneanimations[3].keyframes[3].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(90.0f)));

    boneanimations[4].keyframes.resize(4);//第二个立方体的第二次旋转（以第一个立方体为原点）//每个骨头都是先旋转（以坐标000）再平移(转换坐标)往右移动一相当于原点向左平移1
                                          //当模型所有点都在一个坐标系下时，对于某个骨骼的某个点，只需先转换至骨骼坐标然后旋转当前骨骼的角度，然后通过和父骨骼的位置关系将原点平移到父节点，然后
                                           //应用父节点的旋转，再平移至祖父节点，以此类推，直到根节点，以上就是最终变换矩阵（先偏移至骨骼坐标，然后偏移至跟坐标），最后将跟坐标转换至世界坐标，就可以draw了
    boneanimations[4].numkeyframe = 4;
    boneanimations[4].keyframes[0].starttime = 0;
    boneanimations[4].keyframes[0].translation = XMFLOAT3(-8.0f, 0, 0);
    boneanimations[4].keyframes[0].scale = XMFLOAT3(1, 1, 1);
    XMStoreFloat4(&boneanimations[4].keyframes[0].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(22.5f)));//旋转轴的方向，需要原点确定具体的旋转轴

    boneanimations[4].keyframes[1].starttime = 2.0f;
    boneanimations[4].keyframes[1].translation = XMFLOAT3(-8.0f, 0, 0);
    boneanimations[4].keyframes[1].scale = XMFLOAT3(1, 1, 1);
    XMStoreFloat4(&boneanimations[4].keyframes[1].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(45.0f)));

    boneanimations[4].keyframes[2].starttime = 4.0f;
    boneanimations[4].keyframes[2].translation = XMFLOAT3(-8.0f, 0, 0);
    boneanimations[4].keyframes[2].scale = XMFLOAT3(1, 1, 1);
    XMStoreFloat4(&boneanimations[4].keyframes[2].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(67.5f)));

    boneanimations[4].keyframes[3].starttime = 6.0f;
    boneanimations[4].keyframes[3].translation = XMFLOAT3(-8.0f, 0, 0);
    boneanimations[4].keyframes[3].scale = XMFLOAT3(1, 1, 1);
    XMStoreFloat4(&boneanimations[4].keyframes[3].quat, XMQuaternionRotationAxis(XMVectorSet(0, 1.0f, 0, 0), XMConvertToRadians(90.0f)));

    //采样器
 /*   D3D12_DESCRIPTOR_HEAP_DESC samheapdesc = {};
    samheapdesc.NumDescriptors = 5;
    samheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
    samheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    ThrowIfFailed(pID3DDevice->CreateDescriptorHeap(&samheapdesc, IID_PPV_ARGS(&pISamheap)));
    D3D12_SAMPLER_DESC stSamplerDesc = {};
    stSamplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    stSamplerDesc.MipLODBias = 0;
    stSamplerDesc.MaxAnisotropy = 1;
    stSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    stSamplerDesc.MinLOD = 0.0f;
    stSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
    CD3DX12_CPU_DESCRIPTOR_HANDLE samplecpu(pISamheap->GetCPUDescriptorHandleForHeapStart());
    nSamplerDescriptorSize = pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
    pID3DDevice->CreateSampler(&stSamplerDesc, samplecpu);
    samplecpu.Offset(1, nSamplerDescriptorSize);
    stSamplerDesc.BorderColor[0] = 1.0f;
    stSamplerDesc.BorderColor[1] = 0;
    stSamplerDesc.BorderColor[2] = 1.0f;
    stSamplerDesc.BorderColor[3] = 1.0f;
    stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    pID3DDevice->CreateSampler(&stSamplerDesc, samplecpu);
    samplecpu.Offset(1, nSamplerDescriptorSize);
    stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    pID3DDevice->CreateSampler(&stSamplerDesc, samplecpu);
    samplecpu.Offset(1, nSamplerDescriptorSize);
    stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
    stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
    stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
    pID3DDevice->CreateSampler(&stSamplerDesc, samplecpu);
    samplecpu.Offset(1, nSamplerDescriptorSize);
    stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE;
    stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE;
    stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE;
    pID3DDevice->CreateSampler(&stSamplerDesc, samplecpu);*/
    //创建定位上传堆（passcb）
    //D3D12_HEAP_DESC placedUplaodHeapdesc = {};
    //placedUplaodHeapdesc.SizeInBytes = GRS_UPPER(2 * sizeof(passconstant), D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT);
    //placedUplaodHeapdesc.Alignment = 0;
    //placedUplaodHeapdesc.Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
    //placedUplaodHeapdesc.Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    //placedUplaodHeapdesc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    //placedUplaodHeapdesc.Flags = D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS;
    //ThrowIfFailed(pID3DDevice->CreateHeap(&placedUplaodHeapdesc, IID_PPV_ARGS(&pIUploadHeap)));
    //pID3DDevice->CreatePlacedResource(pIUploadHeap.Get(), 0, &CD3DX12_RESOURCE_DESC::Buffer(2 * ((sizeof(passconstant) + 255) & ~255)//常量buffer必须在每个格子里还要256对其
    //), D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&pIpassCB));
    //byte* passcbmappeddata;
    //pIpassCB->Map(0, NULL, reinterpret_cast<void**>(&passcbmappeddata));
    ////帝宝立方体顶点
    float texturenum = 1.0f;
   std::vector< Vertex> vertices = {
        {XMFLOAT4{-7.5f,-7.5f ,-5.0f,1.0f},XMFLOAT2{0.0f,1.0f * texturenum},XMFLOAT3{0,0,-1.0f},XMFLOAT3{1.0f,0,0}},//前
        {XMFLOAT4{-7.5 ,7.5 ,-5.0f,1.0f},XMFLOAT2{0.0f,0.0f},XMFLOAT3{0,0,-1.0f},XMFLOAT3{1.0f,0,0}},//
        {XMFLOAT4{7.5 ,-7.5 ,-5.0f,1.0f},XMFLOAT2{1.0f * texturenum,1.0f * texturenum},XMFLOAT3{0,0,-1.0f},XMFLOAT3{1.0f,0,0}},
        {XMFLOAT4{7.5 ,7.5,-5.0f,1.0f},XMFLOAT2{1.0f * texturenum,0.0f},XMFLOAT3{0,0,-1.0f},XMFLOAT3{1.0f,0,0}},//
        {XMFLOAT4{-7.5 ,7.5,-5.0f,1.0f},XMFLOAT2{0.0f,1.0f * texturenum},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0}},//上
        {XMFLOAT4{-7.5 ,7.5,2.5f,1.0f},XMFLOAT2{.0f,.0f},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0}},//上
        {XMFLOAT4{7.5 ,7.5,-5.0f,1.0f},XMFLOAT2{1.0f * texturenum,1.0f * texturenum},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0}},//上
        {XMFLOAT4{7.5 ,7.5,2.5f,1.0f},XMFLOAT2{1.0f * texturenum,0.0f},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0}},//上
        {XMFLOAT4{-7.5 ,7.5,2.5f,1.0f},XMFLOAT2{.0f,1.0f * texturenum},XMFLOAT3{0,0,1.0f},XMFLOAT3{-1.0f,0,0}},//后
        {XMFLOAT4{-7.5 ,-7.5,2.5f,1.0f},XMFLOAT2{.0f,.0f},XMFLOAT3{0,0,1.0f},XMFLOAT3{-1.0f,0,0}},//后
        {XMFLOAT4{7.5 ,7.5,2.5f,1.0f},XMFLOAT2{1.0f * texturenum,1.0f * texturenum},XMFLOAT3{0,0,1.0f},XMFLOAT3{-1.0f,0,0}},//后
        {XMFLOAT4{7.5 ,-7.5,2.5f,1.0f},XMFLOAT2{1.0f * texturenum,.0f},XMFLOAT3{0,0,1.0f},XMFLOAT3{-1.0f,0,0}},//后//
        {XMFLOAT4{-7.5 ,-7.5,2.5f,1.0f},XMFLOAT2{.0f,1.0f * texturenum},XMFLOAT3{0,-1.0f,0},XMFLOAT3{1.0f,0,0}},//下
        {XMFLOAT4{-7.5 ,-7.5,-5.0f,1.0f},XMFLOAT2{.0f,.0f},XMFLOAT3{0,-1.0f,0},XMFLOAT3{1.0f,0,0}},//下
        {XMFLOAT4{7.5 ,-7.5,2.5f,1.0f},XMFLOAT2{1.0f * texturenum,1.0f * texturenum},XMFLOAT3{0,-1.0f,0},XMFLOAT3{1.0f,0,0}},//下//
        {XMFLOAT4{7.5 ,-7.5,-5.0f,1.0f},XMFLOAT2{1.0f * texturenum,.0f},XMFLOAT3{0,-1.0f,0},XMFLOAT3{1.0f,0,0}},//下
        {XMFLOAT4{-7.5 ,-7.5,2.5f,1.0f},XMFLOAT2{.0f,1.0f * texturenum},XMFLOAT3{-1.0f,0,0},XMFLOAT3{0,0,-1.0f}},//左
        {XMFLOAT4{-7.5 ,7.5,2.5f,1.0f},XMFLOAT2{.0f,.0f},XMFLOAT3{-1.0f,0,0},XMFLOAT3{0,0,-1.0f}},//左
        {XMFLOAT4{-7.5 ,-7.5,-5.0f,1.0f},XMFLOAT2{1.0f * texturenum,1.0f * texturenum},XMFLOAT3{-1.0f,0,0},XMFLOAT3{0,0,-1.0f}},//左
        {XMFLOAT4{-7.5 ,7.5,-5.0f,1.0f},XMFLOAT2{1.0f * texturenum,.0f},XMFLOAT3{-1.0f,0,0},XMFLOAT3{0,0,-1.0f}},//左
        {XMFLOAT4{7.5 ,-7.5,-5.0f,1.0f},XMFLOAT2{.0f,1.0f * texturenum},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,1.0f}},//右
        {XMFLOAT4{7.5 ,7.5,-5.0f,1.0f},XMFLOAT2{.0f,.0f},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,1.0f}},//  
        {XMFLOAT4{7.5 ,-7.5,2.5f,1.0f},XMFLOAT2{1.0f * texturenum,1.0f * texturenum},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,1.0f}},//  //
        {XMFLOAT4{7.5 ,7.5,2.5f,1.0f},XMFLOAT2{1.0f * texturenum,.0f},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,1.0f}}//
    };

    std::vector< std::uint16_t> indices = {
      0,1,3,0,3,2,
      4,5,7,4,7,6,
     11,10,8,11,8,9,
      12,13,15,12,15,14,
      16,17,19,16,19,18,
      20,21,23,20,23,22

    };

    std::vector<Vertex>planev = {
        {XMFLOAT4{-60.0f+6,5,60.0f,1.0f},XMFLOAT2{0,.0f},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0},0},
        {XMFLOAT4{60.0f,5,60.0f,1.0f},XMFLOAT2{1.0f,.0f},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0},0},
        {XMFLOAT4{-60.0f+6,5,-60.0f,1.0f},XMFLOAT2{0,1.0f},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0},0},
        {XMFLOAT4{60.0f,  5 ,-60.0f,1.0f},XMFLOAT2{1.0f,1.0f},XMFLOAT3{0,1.0f,0},XMFLOAT3{1.0f,0,0},0},

        {XMFLOAT4{-60.0f+6, 100.0f ,-60.0f,1.0f},XMFLOAT2{0,0},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,-1.0f},0},
        {XMFLOAT4{-60.0f+6, 100.0f ,60.0f,1.0f},XMFLOAT2{1.0f,0},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,-1.0f},0},
        {XMFLOAT4{-60.0f+6,5,-60.0f,1.0f},XMFLOAT2{0,1.0f},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,-1.0f},0},
        {XMFLOAT4{-60.0f+6,5,60.0f,1.0f},XMFLOAT2{1.0f,1.0f},XMFLOAT3{1.0f,0,0},XMFLOAT3{0,0,-1.0f},0}
    };
    for (int i = 0;i < 4;i++) {
        planev[i].color = XMFLOAT3{ 1.0f,0,0 };
        planev[i].normal = XMFLOAT3{ 0,1.0f,0 };
    }
    for (int i = 4;i < 8;i++) {
        planev[i].color = XMFLOAT3{ 0,0,1.0f };
        planev[i].normal = XMFLOAT3{ 1.0f,0,0 };
    }
    std::vector<std::uint16_t>planei = {
        0,1,2,2,1,3,
        4,5,6,6,5,7
    };
    std::vector<Vertex>RSMv;
    std::vector<std::uint16_t>RSMi = {
        0,1,2,2,1,3,
        4,5,6,6,5,7
    };
    RSMv.assign(&planev[0], &planev[7]);
    RSMv.push_back(planev[7]);
    for (int i = 0;i < mreader.mvertices.size(); i++) {
        Vertex v;
        v.normal = mreader.mvertices[i].normal;
        v.position = XMFLOAT4{ mreader.mvertices[i].position.x,mreader.mvertices[i].position.y,mreader.mvertices[i].position.z+40.0f,1.0f };
        v.TangentU = XMFLOAT3{ mreader.mvertices[i].tangent.x,mreader.mvertices[i].tangent.y,mreader.mvertices[i].tangent.z };
        v.uv = mreader.mvertices[i].texuv;
        v.color = XMFLOAT3{ 0,0,0};
        RSMv.push_back(v);
    }
    for (int i = 0;i < mreader.mindices.size();i++) {
        RSMi.push_back(mreader.mindices[i] + 8);
    }
    const float X = 0.5257f;
    const float Z = 0.8506f;
    XMFLOAT3 sphereVertices[] = {
      XMFLOAT3(-X, 0.0f, Z),  XMFLOAT3(X, 0.0f, Z),
  XMFLOAT3(-X, 0.0f, -Z), XMFLOAT3(X, 0.0f, -Z),
  XMFLOAT3(0.0f, Z, X),   XMFLOAT3(0.0f, Z, -X),
  XMFLOAT3(0.0f, -Z, X),  XMFLOAT3(0.0f, -Z, -X),
  XMFLOAT3(Z, X, 0.0f),   XMFLOAT3(-Z, X, 0.0f),
  XMFLOAT3(Z, -X, 0.0f),  XMFLOAT3(-Z, -X, 0.0f)
    };
    std::uint16_t sphereIndices[] = {
    1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
    1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
    3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
    10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7
    };

    //culla-conty预计算顶点
    std::vector<XMFLOAT3>cullav;
    
    for (int i = -100;i < 100;i++) {
        for (int j = -100;j < 100;j++) {
            cullav.push_back(XMFLOAT3{ i / 100.0f,j / 100.0f,1.0f });
        }
    }
    std::vector<std::uint16_t>cullai;
    for (int j = 0;j < 199;j++) {
        for (int i = 0;i < 199;i++) {
            
            cullai.push_back(i+j*200);
            cullai.push_back(i +j*200+ 1);
            cullai.push_back(i +j*200+ 200);
            cullai.push_back(i +j*200+ 200);
            cullai.push_back(i +j*200+ 1);
            cullai.push_back(i +j*200+ 201);
        }
    }

    //prefilter-cubemap顶点
    std::vector<cubemapVertex> cubemapv = {
        {XMFLOAT3{1.0f,1.0f,1.0f}},
        {XMFLOAT3{1.0f,1.0f,-1.0f}},
        {XMFLOAT3{1.0f,-1.0f,1.0f}},
        {XMFLOAT3{1.0f,-1.0f,-1.0f}},

        {XMFLOAT3{-1.0f,1.0f,-1.0f}},
        {XMFLOAT3{-1.0f,1.0f,1.0f}},
        {XMFLOAT3{-1.0f,-1.0f,-1.0f}},
        {XMFLOAT3{-1.0f,-1.0f,1.0f}},

        {XMFLOAT3{-1.0f,1.0f,-1.0f}},
        {XMFLOAT3{1.0f,1.0f,-1.0f}},
        {XMFLOAT3{-1.0f,1.0f,1.0f}},
        {XMFLOAT3{1.0f,1.0f,1.0f}},

        {XMFLOAT3{-1.0f,-1.0f,1.0f}},
        {XMFLOAT3{1.0f,-1.0f,1.0f}},
        {XMFLOAT3{-1.0f,-1.0f,-1.0f}},
        {XMFLOAT3{1.0f,-1.0f,-1.0f}},

        {XMFLOAT3{-1.0f,1.0f,1.0f}},
        {XMFLOAT3{1.0f,1.0f,1.0f}},
        {XMFLOAT3{-1.0f,-1.0f,1.0f}},
        {XMFLOAT3{1.0f,-1.0f,1.0f}},

        {XMFLOAT3{1.0f,1.0f,-1.0f}},
        {XMFLOAT3{-1.0f,1.0f,-1.0f}},
        {XMFLOAT3{1.0f,-1.0f,-1.0f}},
        {XMFLOAT3{-1.0f,-1.0f,-1.0f}},
    };
    //for (int i = 0;i < 24;i++)
    //    cubemapv[i].position = XMFLOAT3{ cubemapv[i].position.x*200, cubemapv[i].position.y * 200, cubemapv[i].position.z * 200 };
    cubemapv.resize(24);
  

  
    
    std::vector<std::uint16_t>cubemapi;
       for (int i = 0;i < 6;i++) {
           cubemapi.push_back(0 + i * 4);
           cubemapi.push_back(1 + i * 4);
           cubemapi.push_back(2 + i * 4);
           cubemapi.push_back(2 + i * 4);
           cubemapi.push_back(1 + i * 4);
           cubemapi.push_back(3 + i * 4);
    }
    //球体顶点
  
    meshdata mesh12;
    mesh12.indices.insert(mesh12.indices.end(), std::begin(sphereIndices), std::end(sphereIndices));
    mesh12.vertices.insert(mesh12.vertices.end(), std::begin(sphereVertices), std::end(sphereVertices));

    for (int i = 0;i < 3;i++)
        mesh12 = subvide(mesh12, mesh12.vertices.size(), mesh12.indices.size());
    std::vector<Vertex>spherev;
    for (int i = 0;i < mesh12.vertices.size();i++) {
        XMVECTOR vec = { mesh12.vertices[i].x, mesh12.vertices[i].y, mesh12.vertices[i].z };
        vec = XMVector3Normalize(vec);
        float theta = std::atanf(XMVectorGetZ(vec) / XMVectorGetX(vec));
        if (theta < 0)
            theta += XM_2PI;
        float thetak = theta / XM_2PI;
        float phi = std::acosf(XMVectorGetY(vec)/1.0f);
        float phik = phi / XM_PI;
        Vertex ver;
        float r = 5.0f;

        ver.position = XMFLOAT4{ XMVectorGetX(vec) * r ,XMVectorGetY(vec) * r,XMVectorGetZ(vec) * r,1.0f };
        ver.uv = { thetak ,phik  };
        ver.TangentU = XMFLOAT3{r*sin(phi)*sin(theta),0,r*sin(phi)*cos(theta)};
        ver.color = XMFLOAT3{ 0,0,0.001f };
        XMStoreFloat3(&ver.normal,vec);
        spherev.push_back(ver);
    }
    std::vector<Vertex>skyv;
    for (int i = 0;i < mesh12.vertices.size();i++) {
        XMVECTOR vec = { mesh12.vertices[i].x, mesh12.vertices[i].y, mesh12.vertices[i].z };
        vec = XMVector3Normalize(vec);
        float theta = std::atanf(XMVectorGetZ(vec) / XMVectorGetX(vec));
        if (theta < 0)
            theta += XM_2PI;
        float thetak = theta / XM_2PI;
        float phi = std::atanf(sqrt(XMVectorGetZ(vec) * XMVectorGetZ(vec) + XMVectorGetX(vec) * XMVectorGetX(vec)) / XMVectorGetY(vec));
        float phik = phi / XM_PI;
        if (phi < 0)
            phi += XM_PI;
        Vertex ver;
        float r = 500.0f;

        ver.position = XMFLOAT4{ XMVectorGetX(vec) * r ,XMVectorGetY(vec) * r,XMVectorGetZ(vec) * r,1.0f };
        ver.uv = { thetak*0.5f,phik*0.5f };
        ver.TangentU = XMFLOAT3{ r * sin(phi) * sin(theta),0,r * sin(phi) * cos(theta) };
        skyv.push_back(ver);
    }
    std::vector<LPVballVertex>LPVballv;
    for (int i = 0;i < mesh12.vertices.size();i++) {
        XMVECTOR vec = { mesh12.vertices[i].x, mesh12.vertices[i].y, mesh12.vertices[i].z };
        vec = XMVector3Normalize(vec);
        float theta = std::atanf(XMVectorGetZ(vec) / XMVectorGetX(vec));
        if (theta < 0)
            theta += XM_2PI;
        float thetak = theta / XM_2PI;
        float phi = std::atanf(sqrt(XMVectorGetZ(vec) * XMVectorGetZ(vec) + XMVectorGetX(vec) * XMVectorGetX(vec)) / XMVectorGetY(vec));
        float phik = phi / XM_PI;
        if (phi < 0)
            phi += XM_PI;
        LPVballVertex ver;
        float r = 1.0f;

        ver.pos = XMFLOAT4{ XMVectorGetX(vec) * r ,XMVectorGetY(vec) * r,XMVectorGetZ(vec) * r,1.0f };
        ver.uv = { thetak * 0.5f,phik * 0.5f };
        XMStoreFloat4(&ver.normal, vec);
        //ver.TangentU = XMFLOAT3{ r * sin(phi) * sin(theta),0,r * sin(phi) * cos(theta) };
        LPVballv.push_back(ver);
    }
    D3D12_RESOURCE_DESC spherecubetext = {};
    spherecubetext.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    spherecubetext.Alignment = 0;
    spherecubetext.Width = 2000;
    spherecubetext.Height = 2000;
    spherecubetext.DepthOrArraySize = 1;
    spherecubetext.MipLevels = 1;
    spherecubetext.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    spherecubetext.SampleDesc.Count = 1;
    spherecubetext.SampleDesc.Quality = 0;
    spherecubetext.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    spherecubetext.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&cullaPrecomputeEmu)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&cullaPrecomputeEmuavg)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&cullaPrecomputeFmuavg)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&IBLLUT)));
    spherecubetext.Width = 1024;
    spherecubetext.Height = 824;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RSMwposmap)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RSMfluxmap)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RSMnormalmap)));
    spherecubetext.Width = 1024;
    spherecubetext.Height = 1024;
    spherecubetext.DepthOrArraySize = 6;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&prefiltercubemap)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&prefiltercubemap1)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&prefiltercubemap2)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&prefiltercubemap3)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&prefiltercubemap4)));
    spherecubetext.Width = iWidth;
    spherecubetext.Height = iHeight;
    spherecubetext.DepthOrArraySize = 1;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&SSAOmap)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&SSDOdirectLightmap)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&SSDOnormalmap)));

    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&lastframebuffer[0])));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&lastframebuffer[1])));
    //spherecubetext.Width = 500;
    //spherecubetext.Height = 500;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&colorBuffer)));
    spherecubetext.MipLevels = 11;
    spherecubetext.Width = 1024;
spherecubetext.Height = 1024;

    spherecubetext.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&Hi_zMipmap)));
    spherecubetext.Width = 10;
    spherecubetext.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
    spherecubetext.Height = 10;
    spherecubetext.DepthOrArraySize=10;
    spherecubetext.MipLevels=1;
    spherecubetext.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&LPVvoxelTex)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&LPVvoxelTex2)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&LPVvoxelTex3)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&LPVvoxelTex4)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&LPVvoxelTex5)));
    ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&LPVvoxelTex6)));
    spherecubetext.Width = TexSize;
    spherecubetext.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
    spherecubetext.Height = TexSize;
    spherecubetext.DepthOrArraySize = TexSize;
    spherecubetext.MipLevels = 8;
    spherecubetext.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    for (int i = 0;i < 6;i++) {

        ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&clipMapArray[i])));
        ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&clipMapNormalArray[i])));
       UINT vbsize = (UINT)sizeof(voxelVertex) * 36;

       ThrowIfFailed( pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIvoxelvb[i])));
        vbsize = (UINT)sizeof(voxelInstanceData) * (UINT)8000;
        ThrowIfFailed( pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIvoxelInstanceBuffer[i])));
    }
    //spherecubetext.MipLevels = 1;
    //spherecubetext.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
    //线程的创建
    //XMFLOAT3 litdir = XMFLOAT3{ 1.0f,1.0f,0};
    //XMVECTOR lightpos = XMLoadFloat3(&litdir) * 4.0f * mboundingsphere.Radius;
    //XMStoreFloat3(&currpasscb.lightPos, lightpos);
    //XMVECTOR lighttarget = XMLoadFloat3(&mboundingsphere.Center);
    //XMVECTOR lightup = XMVectorSet(0, 1.0f, 0, 0);
    //XMMATRIX lightview = XMMatrixLookAtLH(lightpos, lighttarget, lightup);
    //XMFLOAT3 boundingcenterlightcoord;
    //XMStoreFloat3(&boundingcenterlightcoord, XMVector3TransformCoord(lighttarget, lightview));
    //float l = boundingcenterlightcoord.x - mboundingsphere.Radius * 4.0f;
    //float b = boundingcenterlightcoord.y - mboundingsphere.Radius * 4.0f;
    //float n = boundingcenterlightcoord.z - mboundingsphere.Radius * 8.0f;
    //float r = boundingcenterlightcoord.x + mboundingsphere.Radius * 4.0f;
    //float t = boundingcenterlightcoord.y + mboundingsphere.Radius * 4.0f;
    //float f = boundingcenterlightcoord.z + mboundingsphere.Radius * 4.0f;
    //XMMATRIX projmat = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)1 / (FLOAT)1, 0.1f, 1000.0f);
    //mlightnearz = n;
    //mlightfarz = f;
    //lightviewproj = XMMatrixMultiply(lightview, XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f));

    //XMStoreFloat4x4(&currpasscb.S, XMMatrixTranspose(lightviewproj));
    //XMMATRIX UVmat(0.5f, 0.0f, 0.0f, 0.0f,
    //    0.0f, -0.5f, 0.0f, 0.0f,
    //    0.0f, 0.0f, 1.0f, 0.0f,
    //    0.5f, 0.5f, 0.0f, 1.0f);
    //XMStoreFloat4x4(&currpasscb.uvMAT, XMMatrixTranspose(UVmat));

        D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc = {};
        srvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
       
        //srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;//注释掉的时在线程里赋值得的
        // srvdesc.Format = pITexture->GetDesc().Format;
       // srvdesc.Texture2D.MipLevels = pITexture->GetDesc().MipLevels;
        
      /*  srvdesc.TextureCube.MostDetailedMip = 0;
        srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;*/
        //天空球
        paras[0].pszDDSFile = L"Texture\\snowcube1024.dds";
        paras[0].v4ModelPos = { 0,0,0,0 };
        paras[0].PSO = pIskyPSO.Get();
        
        paras[0].vertices = skyv;
        paras[0].indices = mesh12.indices;
        paras[0].srvdesc = srvdesc;
        D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc1 = {};
        srvdesc1.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
      //  srvdesc1.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
       /* srvdesc1.Texture2D.MipLevels = 11;
        srvdesc1.Texture2D.MostDetailedMip = 0;
        srvdesc1.Texture2D.ResourceMinLODClamp = 0.0f;*/
        //帝宝球1
        paras[1].pszDDSFile = L"Texture\\checkboard.dds";
        paras[1].v4ModelPos = { 0,5.0f,0,0 };
        paras[1].PSO = pIPipelineState.Get();
        paras[1].vertices = spherev;
        paras[1].indices = mesh12.indices;
        paras[1].srvdesc = srvdesc1;
        paras[1].md = XMFLOAT4{ 1.0f,0.6f,1.0f,1.0f };
        paras[1].r0 = XMFLOAT3{ 0.1f,0.1f,0.1f };
        paras[1].m = 0.25f;
        //帝宝球2
        paras[2].pszDDSFile = L"Texture\\checkboard.dds";
        paras[2].v4ModelPos = { 0,0,0,0 };
        paras[2].PSO = pIPipelineState.Get();
        paras[2].vertices = spherev;
        paras[2].indices  = mesh12.indices;
        paras[2].srvdesc = srvdesc1;
        paras[2].md = XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f };
        paras[2].r0 = XMFLOAT3{ 0.5f,0.5f,0.5f };
        paras[2].m = 0.25f;
        //plane
        paras[3].pszDDSFile = L"Texture\\checkboard.dds";
        paras[3].v4ModelPos = { 0,0,0,0 };
        paras[3].PSO = pIwithoutPipelineState.Get();
        paras[3].vertices = planev;
        paras[3].indices = planei;
        paras[3].srvdesc = srvdesc1;
        paras[3].md = XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f };
        paras[3].r0 = XMFLOAT3{ 0.5f,0.5f,0.5f };
        paras[3].m = 0.25f;
        //3
        paras[4].pszDDSFile = L"Texture\\checkboard.dds";
        paras[4].v4ModelPos = { 0,0,0,0 };
        paras[4].PSO = pIPipelineState.Get();
        paras[4].vertices = spherev;
        paras[4].indices = mesh12.indices;
        paras[4].srvdesc = srvdesc1;
        paras[4].md = XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f };
        paras[4].r0 = XMFLOAT3{ 0.5f,0.5f,0.5f };
        paras[4].m = 0.25f;
        //4
        paras[5].pszDDSFile = L"Texture\\checkboard.dds";
        paras[5].v4ModelPos = { 0,0,0,0 };
        paras[5].PSO = pIPipelineState.Get();
        paras[5].vertices = spherev;
        paras[5].indices = mesh12.indices;
        paras[5].srvdesc = srvdesc1;
        paras[5].md = XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f };
        paras[5].r0 = XMFLOAT3{ 0.5f,0.5f,0.5f };
        paras[5].m = 0.25f;

        paras[6].pszDDSFile = L"Texture\\checkboard.dds";
        paras[6].v4ModelPos = { 0,0,0,0 };
        paras[6].PSO = pIwithoutPipelineStateModel.Get();
        paras[6].mvertices = mreader.mvertices;
        paras[6].indices = mreader.mindices;
        paras[6].srvdesc = srvdesc1;
        paras[6].md = XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f };
        paras[6].r0 = XMFLOAT3{ 0.5f,0.5f,0.5f };
        paras[6].m = 0.25f;

        paras[7].pszDDSFile = L"Texture\\checkboard.dds";
        paras[7].v4ModelPos = { 0,0,0,0 };
        paras[7].PSO = pIPipelineState.Get();
        paras[7].vertices = bvhV;
        paras[7].indices = bvhI;
        paras[7].srvdesc = srvdesc1;
        paras[7].md = XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f };
        paras[7].r0 = XMFLOAT3{ 0.5f,0.5f,0.5f };
        paras[7].m = 0.25f;

        paras[8].pszDDSFile = L"Texture\\checkboard.dds";
        paras[8].v4ModelPos = { 0,0,0,0 };
        paras[8].PSO = pIvoxelvisualizePSO.Get();
        paras[8].voxelvertices = &voxelv;
        paras[8].voxelindices = &voxeli;
        paras[8].srvdesc = srvdesc1;
            paras[8].voxelvbv = &voxelvbv;//数组指针解索引后是数组的首地址，之后加一是移动一个数组元素的字节而不是整个数组的字节（编译器也不知道如何获取数组大小啊，只知道这个数据类型有多大）
        
        paras[8].voxelibv = &voxelibv;
        paras[8].md = XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f };
        paras[8].r0 = XMFLOAT3{ 0.5f,0.5f,0.5f };
        paras[8].m = 0.25f;
        for (int i = 0;i < MAX_THREAD_NUM;i++) {
          
            paras[i].rs = pIRootSignature.Get();
            paras[i].device = pID3DDevice.Get();
            paras[i].dwMainThreadID = ::GetCurrentThreadId();
            paras[i].hMainThread = ::GetCurrentThread();
            paras[i].hEventRenderOver = ::CreateEvent(NULL, FALSE, NULL, FALSE);
            paras[i].hRunEvent = ::CreateEvent(NULL, FALSE, NULL, FALSE);
            ThrowIfFailed(pID3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&paras[i].cmdalloc)));
            ThrowIfFailed(pID3DDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, paras[i].cmdalloc, nullptr, IID_PPV_ARGS(&paras[i].cmdlist)));//这行出了异常，把pso变成para[0]的好了，又变回i的，又好了，真抽象，真玄学            
            paras[i].nIndex = i;
            paras[i].SM = pIShadowMap.Get();
            paras[i].cullaPrecompute = cullaPrecomputeEmu.Get();
            paras[i].cullaPrecomputeavg = cullaPrecomputeEmuavg.Get();
            paras[i].cullaPrecomputeFavg = cullaPrecomputeFmuavg.Get();
            paras[i].IBLLUT = IBLLUT.Get();
            paras[i].prefilterCube = prefiltercubemap.Get();
            paras[i].prefilterCube1 = prefiltercubemap1.Get();
            paras[i].prefilterCube2 = prefiltercubemap2.Get();
            paras[i].prefilterCube3 = prefiltercubemap3.Get();
            paras[i].prefilterCube4 = prefiltercubemap4.Get();
            paras[i].SSAOmap = SSAOmap.Get();
            paras[i].RSMdepthmap = RSMdepthmap.Get();
            paras[i].RSMfluxmap = RSMfluxmap.Get();
            paras[i].RSMnormalmap = RSMnormalmap.Get();
            paras[i].RSMwposmap = RSMwposmap.Get();
            paras[i].SSDODLmap = SSDOdirectLightmap.Get();
            paras[i].SSDOnormalmap = SSDOnormalmap.Get();
            paras[i].viewdepthmap = SSAOdepthmap.Get();
            paras[i].Hizmap = Hi_zMipmap.Get();
            paras[i].lastframe[0] = lastframebuffer[0].Get();
            paras[i].lastframe[1] = lastframebuffer[1].Get();
            paras[i].LPVvoxel = LPVvoxelTex.Get();
            paras[i].LPVvoxel2 = LPVvoxelTex2.Get();
            paras[i].LPVvoxel3 = LPVvoxelTex3.Get();
            paras[i].clipmap[0] = clipMapArray[0].Get();
            paras[i].clipmap[1] = clipMapArray[1].Get();
            paras[i].clipmap[2] = clipMapArray[2].Get();
            paras[i].clipmap[3] = clipMapArray[3].Get();
            paras[i].clipmap[4] = clipMapArray[4].Get();
            paras[i].clipmap[5] = clipMapArray[5].Get();
            paras[i].clipmapNormal[0] = clipMapNormalArray[0].Get();
            paras[i].clipmapNormal[1] = clipMapNormalArray[1].Get();
            paras[i].clipmapNormal[2] = clipMapNormalArray[2].Get();
            paras[i].clipmapNormal[3] = clipMapNormalArray[3].Get();
            paras[i].clipmapNormal[4] = clipMapNormalArray[4].Get();
            paras[i].clipmapNormal[5] = clipMapNormalArray[5].Get();
            paras[i].hThisThread = (HANDLE)_beginthreadex(nullptr, 0, threadfunc, (void*)&paras[i], CREATE_SUSPENDED,(UINT*)&(paras[i].dwThisThreadID));
            HandleMessage->Add(paras[i].hEventRenderOver);
        }
        
        std::vector<Vertex>newvertices[4];
        newvertices[0] = skyv;
        newvertices[1] = spherev;
        newvertices[2] = vertices;
        newvertices[3] = planev;
        std::vector<std::uint16_t>newindices[4];
        newindices[0] = mesh12.indices;
        newindices[1] = mesh12.indices;
        newindices[2] = indices;
        newindices[3] = planei;
        newparas[0].vertices = newvertices;
        newparas[0].indices = newindices;
        newparas[0].pszDDSFile= L"Texture\\bricks2.dds";
        newparas[0].skyFile= L"C:\\mytinyrenderproj\\d3d12practicelast\\d3d12practicelast\\Texture\\sunsetcube1024.dds";
        newparas[0].PSO = pIPipelineState.Get();
        newparas[0].skyPSO = pIskyPSO.Get();
        newparas[0].device = pID3DDevice.Get();
        newparas[0].rs = pIRootSignature.Get();
        ThrowIfFailed(pID3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&newparas[0].cmdalloc)));
        ThrowIfFailed(pID3DDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, newparas[0].cmdalloc, newparas[0].skyPSO, IID_PPV_ARGS(&newparas[0].cmdlist)));
        newparas[0].dwMainThreadID = ::GetCurrentThreadId();
        newparas[0].hMainThread = ::GetCurrentThread();
        newparas[0].hEventRenderOver = ::CreateEvent(NULL, FALSE, NULL, FALSE);
        newparas[0].hRunEvent = ::CreateEvent(NULL, FALSE, NULL, FALSE);
        newparas[0].hThisThread = (HANDLE)_beginthreadex(nullptr, 0, threadfuncnew, (void*)&newparas[0], CREATE_SUSPENDED, (UINT*)&(newparas[0].dwThisThreadID));
        newparas[0].rtvheap = pIRTVHeap.Get();
        newparas[0].SM = pIShadowMap.Get();
        HandleMessage->Add(newparas[0].hEventRenderOver);
        for (int i = 0;i < MAX_THREAD_NUM;i++) {
            ::ResumeThread(paras[i].hThisThread);
        }
        ::ResumeThread(newparas[0].hThisThread);
    


        //这个是用定位方式创建默认顶点以及索引缓冲区，注意其中堆的格式以及和创建资源时的偏移

        ////创建资源堆
        //placedUplaodHeapdesc.SizeInBytes = 2*GRS_UPPER(2 * spherevbsize, D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT);//4 2
        //ThrowIfFailed(pID3DDevice->CreateHeap(&placedUplaodHeapdesc, IID_PPV_ARGS(&pIsphereuploadheap)));
        //D3D12_HEAP_DESC stdefaultheapdesc = {};
        //stdefaultheapdesc.SizeInBytes = 2*GRS_UPPER(2* spherevbsize, D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT);//4 2
        //stdefaultheapdesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
        //stdefaultheapdesc.Properties.Type = D3D12_HEAP_TYPE_DEFAULT;		//默认堆类型
        //stdefaultheapdesc.Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        //stdefaultheapdesc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        //stdefaultheapdesc.Flags = D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES;
        //ThrowIfFailed(pID3DDevice->CreateHeap(&stdefaultheapdesc, IID_PPV_ARGS(&pIspheredefaultheap)));




        ////创建资源
        //ThrowIfFailed(pID3DDevice->CreatePlacedResource(pIsphereuploadheap.Get(), 0, &CD3DX12_RESOURCE_DESC::Buffer(spherevbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIspherevb)));
        //ThrowIfFailed(pID3DDevice->CreatePlacedResource(pIspheredefaultheap.Get(), 0, &CD3DX12_RESOURCE_DESC::Buffer(spherevbsize), D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&pIspheredefaultvb)));
        //ThrowIfFailed(pID3DDevice->CreatePlacedResource(pIsphereuploadheap.Get(),GRS_UPPER( spherevbsize, D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT), &CD3DX12_RESOURCE_DESC::Buffer(sphereibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIsphereib)));
        //ThrowIfFailed(pID3DDevice->CreatePlacedResource(pIspheredefaultheap.Get(),GRS_UPPER(spherevbsize, D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT), &CD3DX12_RESOURCE_DESC::Buffer(sphereibsize), D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&pIspheredefaultib)));
        //            //偏移一定要是堆的alignment的本身或是倍数，资源自己大小不能太大,有点像一个一个格子，ali就是格子的大小
        //
        ////update
        //D3D12_SUBRESOURCE_DATA spherevsub;
        //spherevsub.pData = spherev.data();
        //spherevsub.RowPitch = spherevbsize;
        //spherevsub.SlicePitch = spherevsub.RowPitch;
        //UpdateSubresources<1>(pICommandList.Get(), pIspheredefaultvb.Get(), pIspherevb.Get(), 0, 0, 1, &spherevsub);
        //spherevsub.pData = mesh12.indices.data();
        //spherevsub.RowPitch = sphereibsize;
        //spherevsub.SlicePitch = spherevsub.RowPitch;
        //UpdateSubresources<1>(pICommandList.Get(), pIspheredefaultib.Get(), pIsphereib.Get(), 0, 0, 1, &spherevsub);
        ////切记资源转换
        //pICommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIspheredefaultvb.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
        //pICommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIspheredefaultib.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));



        //spherevbv.BufferLocation = pIspheredefaultvb->GetGPUVirtualAddress();
        //spherevbv.SizeInBytes = spherevbsize;
        //spherevbv.StrideInBytes = sizeof(Vertex);
        //sphereibv.BufferLocation = pIspheredefaultib->GetGPUVirtualAddress();
        //sphereibv.SizeInBytes = sphereibsize;
        //sphereibv.Format = DXGI_FORMAT_R16_UINT;


        //这个是在上面已经创建过的定位堆上创建动态顶点以及索引缓冲


        //skysphere
       /* std::vector<Vertex>skyv;
        for (int i = 0;i < mesh12.vertices.size();i++) {
            XMVECTOR vec = { mesh12.vertices[i].x, mesh12.vertices[i].y, mesh12.vertices[i].z };
            vec = XMVector3Normalize(vec);
            float theta = std::atanf(XMVectorGetZ(vec) / XMVectorGetX(vec));
            if (theta < 0)
                theta += XM_2PI;
            float thetak = theta / XM_2PI;
            float phi = std::atanf(sqrt(XMVectorGetZ(vec) * XMVectorGetZ(vec) + XMVectorGetX(vec) * XMVectorGetX(vec)) / XMVectorGetY(vec));
            float phik = phi / XM_PI;
            if (phi < 0)
                phi += XM_PI;
            Vertex ver;
            float r = 200.0f;

            ver.position = XMFLOAT4{ XMVectorGetX(vec) * r ,XMVectorGetY(vec) * r,XMVectorGetZ(vec) * r,1.0f };
            ver.uv = { thetak,phik };
            skyv.push_back(ver);
        }                               
        UINT64 skyvbsize = sizeof(Vertex) * skyv.size();
        ThrowIfFailed(pID3DDevice->CreatePlacedResource(pIsphereuploadheap.Get(), 2 * D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT, &CD3DX12_RESOURCE_DESC::Buffer(skyvbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIskyuploadvb)));
        ThrowIfFailed(pID3DDevice->CreatePlacedResource(pIsphereuploadheap.Get(), 3 * D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT, &CD3DX12_RESOURCE_DESC::Buffer(sphereibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIskyuploadib)));
        byte* skymapdatav = nullptr;
        pIskyuploadvb->Map(0, nullptr, reinterpret_cast<void**>(&skymapdatav));
        memcpy(skymapdatav, skyv.data(), skyvbsize);
        byte* skymapdatai = nullptr;
        pIskyuploadib->Map(0, nullptr, reinterpret_cast<void**>(&skymapdatai));
        memcpy(skymapdatai, mesh12.indices.data(), sphereibsize);
        skyvbv.BufferLocation = pIskyuploadvb->GetGPUVirtualAddress();
        skyvbv.SizeInBytes = skyvbsize;
        skyvbv.StrideInBytes = sizeof(Vertex);
        skyibv.BufferLocation = pIskyuploadib->GetGPUVirtualAddress();
        skyibv.Format = DXGI_FORMAT_R16_UINT;
        skyibv.SizeInBytes = sphereibsize;*/






        //loadtex并为其创建描述符堆




        //texloader.LoadTextureFromFile(pID3DDevice.Get(), pICommandList.Get(), pICommandQueue.Get(), L"C:\\picture\\th.jpg", pItex1DefaultBuf.GetAddressOf(), pItex1UploadBuf.GetAddressOf());
        //std::wstring file = L"Texture\\ice.dds";
        //CreateDDSTextureFromFile12(pID3DDevice.Get(), pICommandList.Get(), L"C:\\mytinyrenderproj\\d3d12practicelast\\d3d12practicelast\\Texture\\sunsetcube1024.dds", pIskytexdefault,pIskytexupload);
        ////CreateDDSTextureFromFile12(pID3DDevice.Get(), pICommandList.Get(), file.c_str(), pItex1DefaultBuf, pItex1UploadBuf);
        //assert(pItex1DefaultBuf != nullptr);
        //assert(pIskytexdefault != nullptr);
        //D3D12_DESCRIPTOR_HEAP_DESC heapdesc = {};
        //heapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        //heapdesc.NumDescriptors = 3;
        //
        //heapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        //ThrowIfFailed(pID3DDevice->CreateDescriptorHeap(&heapdesc, IID_PPV_ARGS(&pISRVHeap)));
        //D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc = {};

        //srvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        //srvdesc.Format = pItex1DefaultBuf->GetDesc().Format;
        //srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        //srvdesc.Texture2D.MipLevels = pItex1DefaultBuf->GetDesc().MipLevels;
        //srvdesc.Texture2D.MostDetailedMip = 0;
        //srvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
        //pID3DDevice->CreateShaderResourceView(pItex1DefaultBuf.Get(), &srvdesc, pISRVHeap->GetCPUDescriptorHandleForHeapStart());
        //srvdesc.Format = pIskytexdefault->GetDesc().Format;
        //srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        //srvdesc.TextureCube.MipLevels = pIskytexdefault->GetDesc().MipLevels;
        //srvdesc.TextureCube.MostDetailedMip = 0;
        //srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
        //CD3DX12_CPU_DESCRIPTOR_HANDLE skycpuhandle(pISRVHeap->GetCPUDescriptorHandleForHeapStart());
        //skycpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //pID3DDevice->CreateShaderResourceView(pIskytexdefault.Get(), &srvdesc, skycpuhandle);
  
        {
            ThrowIfFailed(pID3DDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pIFence)));
            n64FenceValue = 1;
            hFenceEvent = CreateEvent(nullptr, false, false, nullptr);
            if (hFenceEvent == nullptr) {
                ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
            }
        }
        DWORD dwRet = 0;
        BOOL bExit = FALSE;
        UINT nStates = 0; //初始状态为0
        UINT n64fence = 0;
        ThrowIfFailed(pIcmdlistpre->Close());
        ThrowIfFailed(pIcmdlistpost->Close());
        ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);
        cmdlists.RemoveAll();
        cmdlists.Add(pIcmdlistpre.Get());
        for (int i = 0;i < MAX_THREAD_NUM;i++)
            cmdlists.Add(paras[i].cmdlist);
        cmdlists.Add(newparas[0].cmdlist);
        pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
        n64fence = n64FenceValue;
        n64FenceValue++;
        pICommandQueue->Signal(pIFence.Get(), n64fence);
        pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
        
        ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);
        HandleMessage->RemoveAll();
        for (int i = 0;i < MAX_THREAD_NUM;i++)
            HandleMessage->Add(paras[i].hEventRenderOver);
        HandleMessage->Add(newparas[0].hEventRenderOver);
        for (int i = 0;i < MAX_THREAD_NUM;i++)
            SetEvent(paras[i].hRunEvent);
        SetEvent(newparas[0].hRunEvent);
        SetTimer(hWnd, WM_USER + 100, 1, nullptr);//waitfor需要消息来停止阻塞
    while (!bExit)
    {
        if (nStates == 2) {//渲染完一帧再处理消息,不然一个state处理一次就会卡顿
            while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//用if会卡顿
            {
                if (WM_QUIT != msg.message)
                {
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                }
                else
                {
                    bExit = TRUE;
                }
            }
        }
        dwRet = ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);//返回接受到事件在事件数组中索引,否则阻塞
        UINT a = (UINT)(dwRet - WAIT_OBJECT_0);
        char s[] = { char(a) };
        WriteConsole(g_hOutput, s, 2, NULL, NULL);
        if ((dwRet - WAIT_OBJECT_0)==0)
        {
            switch (nStates) {
            case 0: 
            {
        //预处理
                //加载纹理
                ThrowIfFailed(pIcmdallpre->Reset());
                ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                D3D12_RESOURCE_DESC spherecubetext = {};
                spherecubetext.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
                spherecubetext.Alignment = 0;
                spherecubetext.Width = 2000;
                spherecubetext.Height = 2000;
                spherecubetext.DepthOrArraySize = 1;
                spherecubetext.MipLevels = 1;
                spherecubetext.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                spherecubetext.SampleDesc.Count = 1;
                spherecubetext.SampleDesc.Quality = 0;
                spherecubetext.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
                spherecubetext.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

             ThrowIfFailed(   CreateDDSTextureFromFile12(pID3DDevice.Get(), pIcmdlistpre.Get(), L"Texture\\bricks2.dds", SMtex1, SMtex1up));
              ThrowIfFailed(  CreateDDSTextureFromFile12(pID3DDevice.Get(), pIcmdlistpre.Get(), L"Texture\\bricks2_nmap.dds", SMtex2, SMtex2up));
              ThrowIfFailed(CreateDDSTextureFromFile12(pID3DDevice.Get(), pIcmdlistpre.Get(), L"Texture\\head_diff.dds", headdiff, headdiffup));
              ThrowIfFailed(CreateDDSTextureFromFile12(pID3DDevice.Get(), pIcmdlistpre.Get(), L"Texture\\jacket_diff.dds", jacketdiff, jacketdiffup));
              ThrowIfFailed(CreateDDSTextureFromFile12(pID3DDevice.Get(), pIcmdlistpre.Get(), L"Texture\\pants_diff.dds", pantsdiff, pantsdiffup));
              ThrowIfFailed(CreateDDSTextureFromFile12(pID3DDevice.Get(), pIcmdlistpre.Get(), L"Texture\\upBody_diff.dds", upbodydiff, upbodydiffup));

                CreateDDSTextureFromFile12(pID3DDevice.Get(), pIcmdlistpre.Get(), L"Texture\\snowcube1024.dds", SMtex3, SMtex3up);

                //创建rtv
                CD3DX12_CPU_DESCRIPTOR_HANDLE rtvhandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 9 * pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
              
                D3D12_RENDER_TARGET_VIEW_DESC cullartvdesc = {};
                cullartvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
                cullartvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                cullartvdesc.Texture2D.MipSlice = 0;
                cullartvdesc.Texture2D.PlaneSlice = 0;
                pID3DDevice->CreateRenderTargetView(cullaPrecomputeEmu.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(cullaPrecomputeEmuavg.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(cullaPrecomputeFmuavg.Get(), &cullartvdesc, rtvhandle);
                for (int i = 0;i < 6;i++) {
                    rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                    D3D12_RENDER_TARGET_VIEW_DESC cubertvdesc = {};
                    cubertvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
                    cubertvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    cubertvdesc.Texture2DArray.MipSlice = 0;
                    cubertvdesc.Texture2DArray.PlaneSlice = 0;
                    cubertvdesc.Texture2DArray.FirstArraySlice = i;
                    cubertvdesc.Texture2DArray.ArraySize = 1;
                    pID3DDevice->CreateRenderTargetView(prefiltercubemap.Get(), &cubertvdesc, rtvhandle);

                }
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(IBLLUT.Get(), &cullartvdesc, rtvhandle);
                for (int i = 0;i < 6;i++) {
                    rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                    D3D12_RENDER_TARGET_VIEW_DESC cubertvdesc = {};
                    cubertvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
                    cubertvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    cubertvdesc.Texture2DArray.MipSlice = 0;
                    cubertvdesc.Texture2DArray.PlaneSlice = 0;
                    cubertvdesc.Texture2DArray.FirstArraySlice = i;
                    cubertvdesc.Texture2DArray.ArraySize = 1;
                    pID3DDevice->CreateRenderTargetView(prefiltercubemap1.Get(), &cubertvdesc, rtvhandle);

                }
                for (int i = 0;i < 6;i++) {
                    rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                    D3D12_RENDER_TARGET_VIEW_DESC cubertvdesc = {};
                    cubertvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
                    cubertvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    cubertvdesc.Texture2DArray.MipSlice = 0;
                    cubertvdesc.Texture2DArray.PlaneSlice = 0;
                    cubertvdesc.Texture2DArray.FirstArraySlice = i;
                    cubertvdesc.Texture2DArray.ArraySize = 1;
                    pID3DDevice->CreateRenderTargetView(prefiltercubemap2.Get(), &cubertvdesc, rtvhandle);

                }
                for (int i = 0;i < 6;i++) {
                    rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                    D3D12_RENDER_TARGET_VIEW_DESC cubertvdesc = {};
                    cubertvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
                    cubertvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    cubertvdesc.Texture2DArray.MipSlice = 0;
                    cubertvdesc.Texture2DArray.PlaneSlice = 0;
                    cubertvdesc.Texture2DArray.FirstArraySlice = i;
                    cubertvdesc.Texture2DArray.ArraySize = 1;
                    pID3DDevice->CreateRenderTargetView(prefiltercubemap3.Get(), &cubertvdesc, rtvhandle);

                }
                for (int i = 0;i < 6;i++) {
                    rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                    D3D12_RENDER_TARGET_VIEW_DESC cubertvdesc = {};
                    cubertvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
                    cubertvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    cubertvdesc.Texture2DArray.MipSlice = 0;
                    cubertvdesc.Texture2DArray.PlaneSlice = 0;
                    cubertvdesc.Texture2DArray.FirstArraySlice = i;
                    cubertvdesc.Texture2DArray.ArraySize = 1;
                    pID3DDevice->CreateRenderTargetView(prefiltercubemap4.Get(), &cubertvdesc, rtvhandle);

                }
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                cullartvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
                cullartvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                pID3DDevice->CreateRenderTargetView(SSAOmap.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(RSMfluxmap.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(RSMnormalmap.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(RSMwposmap.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(SSDOdirectLightmap.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(SSDOnormalmap.Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(lastframebuffer[0].Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(lastframebuffer[1].Get(), &cullartvdesc, rtvhandle);
                rtvhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pID3DDevice->CreateRenderTargetView(colorBuffer.Get(), &cullartvdesc, rtvhandle);//第52个
                //加载preSM顶点数据
                std::vector<Vertex>SMvertices[3];
                
                SMvertices[0] = spherev;
                SMvertices[1] = vertices;
                SMvertices[2] = planev;
                std::vector<std::uint16_t>SMindices[3];
               
                SMindices[0] = mesh12.indices;
                SMindices[1] = indices;
                SMindices[2] = planei;
                for (int i = 0;i < 3;i++) {
                    UINT vbsize = (UINT)sizeof(Vertex) * (UINT)SMvertices[i].size();
                    UINT ibsize = (UINT)sizeof(std::uint16_t) * (UINT)SMindices[i].size();
                   pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pISMvb[i]));
                   pID3DDevice ->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pISMib[i]));
                    UINT8* mapib = nullptr;UINT8* mapvb = nullptr;
                    D3D12_RANGE range = { 0,0 };
                    pISMvb[i]->Map(0, &range, reinterpret_cast<void**>(&mapvb));
                    pISMib[i]->Map(0, &range, reinterpret_cast<void**>(&mapib));

                    memcpy(mapvb, SMvertices[i].data(), vbsize);
                    memcpy(mapib,SMindices[i].data(), ibsize);
                    pISMvb[i]->Unmap(0, nullptr);
                    pISMib[i]->Unmap(0, nullptr);
                    SMvbv[i].BufferLocation = pISMvb[i]->GetGPUVirtualAddress();
                    SMvbv[i].SizeInBytes = vbsize;
                    SMvbv[i].StrideInBytes = sizeof(Vertex);
                    SMibv[i].Format = DXGI_FORMAT_R16_UINT;
                    SMibv[i].SizeInBytes = ibsize;
                    SMibv[i].BufferLocation = pISMib[i]->GetGPUVirtualAddress();
                }
                //SSAO顶点数据
                UINT vbsize = (UINT)sizeof(modelVertex) * (UINT)mreader.mvertices.size();
                UINT ibsize = (UINT)sizeof(std::uint16_t) * (UINT)mreader.mindices.size();
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIssaovb));

                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIssaoib));

                UINT8* ssaovbmap = nullptr;UINT8* ssaoibmap = nullptr;
                D3D12_RANGE range = { 0,0 };
                pIssaovb->Map(0, &range, reinterpret_cast<void**>(&ssaovbmap));
                pIssaoib->Map(0, &range, reinterpret_cast<void**>(&ssaoibmap));

                memcpy(ssaovbmap, mreader.mvertices.data(), vbsize);
                memcpy(ssaoibmap, mreader.mindices.data(), ibsize);
                pIssaovb->Unmap(0, nullptr);
                pIssaoib->Unmap(0, nullptr);
                ssaovbv.BufferLocation = pIssaovb->GetGPUVirtualAddress();
                ssaovbv.SizeInBytes = vbsize;
                ssaovbv.StrideInBytes = sizeof(modelVertex);
                ssaoibv.Format = DXGI_FORMAT_R16_UINT;
                ssaoibv.SizeInBytes = ibsize;
                ssaoibv.BufferLocation = pIssaoib->GetGPUVirtualAddress();
                //ball顶点
                 vbsize = (UINT)sizeof(Vertex) * (UINT)mesh12.vertices.size();
                 ibsize = (UINT)sizeof(std::uint16_t) * (UINT)mesh12.indices.size();
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIballvb));

                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIballib));

                UINT8* ballvbmap = nullptr;UINT8* ballibmap = nullptr;
                 range = { 0,0 };
       /*         pIballvb->Map(0, &range, reinterpret_cast<void**>(&ballvbmap));
                pIballib->Map(0, &range, reinterpret_cast<void**>(&ballibmap));

                memcpy(ballvbmap, mesh12.vertices.data(), vbsize);
                memcpy(ballibmap, mesh12.indices.data(), ibsize);*/
        /*        pIballvb->Unmap(0, nullptr);
                pIballib->Unmap(0, nullptr);*/
                //ballvbv.BufferLocation = pIballvb->GetGPUVirtualAddress();
                //ballvbv.SizeInBytes = vbsize;
                //ballvbv.StrideInBytes = sizeof(Vertex);
                //ballibv.Format = DXGI_FORMAT_R16_UINT;
                //ballibv.SizeInBytes = ibsize;
                //ballibv.BufferLocation = pIballib->GetGPUVirtualAddress();
                //culla顶点
                 vbsize = (UINT)sizeof(XMFLOAT3) * (UINT)cullav.size();
                 ibsize = (UINT)sizeof(std::uint16_t) * (UINT)cullai.size();
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIcullavb));

                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIcullaib));

                UINT8* cullamappedvb = nullptr;UINT8* cullamappedib = nullptr;
                 range = { 0,0 };
                pIcullavb->Map(0, &range, reinterpret_cast<void**>(&cullamappedvb));
                pIcullaib->Map(0, &range, reinterpret_cast<void**>(&cullamappedib));
                
                memcpy(cullamappedvb, cullav.data(), vbsize);
                memcpy(cullamappedib, cullai.data(), ibsize);
                pIcullavb->Unmap(0, nullptr);
                pIcullaib->Unmap(0, nullptr);
                cullavbv.BufferLocation = pIcullavb->GetGPUVirtualAddress();
                cullavbv.SizeInBytes = vbsize;
                cullavbv.StrideInBytes = sizeof(XMFLOAT3);
                cullaibv.Format = DXGI_FORMAT_R16_UINT;
                cullaibv.SizeInBytes = ibsize;
                cullaibv.BufferLocation = pIcullaib->GetGPUVirtualAddress();
                //RSM顶点
                vbsize = (UINT)sizeof(Vertex) * (UINT)RSMv.size();
                ibsize = (UINT)sizeof(std::uint16_t) * (UINT)RSMi.size();
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RSMvb));

                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RSMib));

                UINT8* RSMmapv = nullptr;UINT8* RSMmapi = nullptr;
                range = { 0,0 };
                RSMvb->Map(0, &range, reinterpret_cast<void**>(&RSMmapv));
                RSMib->Map(0, &range, reinterpret_cast<void**>(&RSMmapi));

                memcpy(RSMmapv, RSMv.data(), vbsize);
                memcpy(RSMmapi, RSMi.data(), ibsize);
                RSMvb->Unmap(0, nullptr);
                RSMib->Unmap(0, nullptr);
                RSMvbv.BufferLocation = RSMvb->GetGPUVirtualAddress();
                RSMvbv.SizeInBytes = vbsize;
                RSMvbv.StrideInBytes = sizeof(Vertex);
                RSMibv.Format = DXGI_FORMAT_R16_UINT;
                RSMibv.SizeInBytes = ibsize;
                RSMibv.BufferLocation = RSMib->GetGPUVirtualAddress();
                //multiball顶点
                vbsize = (UINT)sizeof(LPVballVertex) * (UINT)LPVballv.size();
                ibsize = (UINT)sizeof(std::uint16_t) * (UINT)mesh12.indices.size();
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&LPVballvb));

                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&LPVballib));

                UINT8* LPVballvmap = nullptr;UINT8* LPVballimap = nullptr;
                range = { 0,0 };
                LPVballvb->Map(0, &range, reinterpret_cast<void**>(&LPVballvmap));
                LPVballib->Map(0, &range, reinterpret_cast<void**>(&LPVballimap));

                memcpy(LPVballvmap, LPVballv.data(), vbsize);
                memcpy(LPVballimap, mesh12.indices.data(), ibsize);
                LPVballib->Unmap(0, nullptr);
                LPVballvb->Unmap(0, nullptr);
                multivbv[0].BufferLocation = LPVballvb->GetGPUVirtualAddress();
                multivbv[0].SizeInBytes = vbsize;
                multivbv[0].StrideInBytes = sizeof(LPVballVertex);
                multiibv[0].Format = DXGI_FORMAT_R16_UINT;
                multiibv[0].SizeInBytes = ibsize;
                multiibv[0].BufferLocation = LPVballib->GetGPUVirtualAddress();
                //multiballinstancedata
                vbsize = (UINT)sizeof(LPVballinstancedata) * (UINT)1000;
                LPVballinstancedata* LPVballinstancedatamap = nullptr;
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&LPVballinstancedataB));
                LPVballinstancedataB->Map(0, &range, reinterpret_cast<void**>(&LPVballinstancedatamap));
                for (int x = 0;x < 10;x++) {
                    for (int y = 0;y < 10;y++) {
                        for (int z = 0;z < 10;z++) {
                            XMMATRIX w = XMMatrixTranslation(x * 12-60+6, y * 10+5, z * 12-60+6);;
                            XMStoreFloat4x4(&LPVballinstancedatamap[x + y * 10 + z * 100].world, XMMatrixTranspose(w));
                        }
                    }
                }
                LPVballinstancedataB->Unmap(0, nullptr);
                multivbv[1].BufferLocation = LPVballinstancedataB->GetGPUVirtualAddress();
                multivbv[1].SizeInBytes = vbsize;
                multivbv[1].StrideInBytes = sizeof(LPVballinstancedata);
              
                //cubemap顶点
                 vbsize = (UINT)sizeof(cubemapVertex) * (UINT)cubemapv.size();
                 ibsize = (UINT)sizeof(std::uint16_t) * (UINT)cubemapi.size();
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIcubemapvb));
                pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIcubemapib));
                UINT8* cubemapmappedvb = nullptr;UINT8* cubemapmappedib = nullptr;
                 range = { 0,0 };
                pIcubemapvb->Map(0, &range, reinterpret_cast<void**>(&cubemapmappedvb));
                pIcubemapib->Map(0, &range, reinterpret_cast<void**>(&cubemapmappedib));

                memcpy(cubemapmappedvb, cubemapv.data(), vbsize);
                memcpy(cubemapmappedib, cubemapi.data(), ibsize);
                pIcubemapvb->Unmap(0, nullptr);
                pIcubemapib->Unmap(0, nullptr);
                cubevbv.BufferLocation = pIcubemapvb->GetGPUVirtualAddress();
                cubevbv.SizeInBytes = vbsize;
                cubevbv.StrideInBytes = sizeof(cubemapVertex);
                cubeibv.Format = DXGI_FORMAT_R16_UINT;
                cubeibv.SizeInBytes = ibsize;
                cubeibv.BufferLocation = pIcubemapib->GetGPUVirtualAddress();



                
         
                pIcmdlistpre->Close();
                cmdlists.RemoveAll();

                cmdlists.Add(pIcmdlistpre.Get());
                pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                n64fence = n64FenceValue;
                n64FenceValue++;
                pICommandQueue->Signal(pIFence.Get(), n64fence);
                pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                HandleMessage->RemoveAll();
                HandleMessage->Add(hFenceEvent);
                ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);
                XMVECTOR targetvec[6] = {
        XMVector4Normalize(XMVectorSet(1.0f,0,0,0)),
          XMVector4Normalize(XMVectorSet(-1.0f,0,0,0)),
          XMVector4Normalize(XMVectorSet(0,1.0f,0,0)),
           XMVector4Normalize(XMVectorSet(0,-1.0f,0,0)),
          XMVector4Normalize(XMVectorSet(0,0,1.0f,0)),
          XMVector4Normalize(XMVectorSet(0,0,-1.0f,0))
                };
                XMVECTOR upvec[6] = {
                    XMVectorSet(0,1.0f,0,0),
                    XMVectorSet(0,1.0f,0,0),
                    XMVectorSet(0,0,-1.0f,0),
                    XMVectorSet(0,0,1.0f,0),
                    XMVectorSet(0,1.0f,0,0),
                    XMVectorSet(0,1.0f,0,0)
                };
                D3D12_DESCRIPTOR_HEAP_DESC presrvheapdesc = {};
                presrvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
                presrvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
                presrvheapdesc.NumDescriptors = 8+24;//1 kulla 6 cube 1srv 24cube
                ThrowIfFailed(pID3DDevice->CreateDescriptorHeap(&presrvheapdesc, IID_PPV_ARGS(&pIcullacbvheap)));
                D3D12_DESCRIPTOR_HEAP_DESC samheapdesc = {};
                samheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
                samheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
                samheapdesc.NumDescriptors = 1;
                pID3DDevice->CreateDescriptorHeap(&samheapdesc, IID_PPV_ARGS(&pIcullasamheap));
                //采样器
                D3D12_SAMPLER_DESC stSamplerDesc = {};
                stSamplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
                stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
                stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
                stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
                stSamplerDesc.MipLODBias = 0;
                stSamplerDesc.MaxAnisotropy = 1;
                stSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
                stSamplerDesc.MinLOD = 0.0f;
                stSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
                CD3DX12_CPU_DESCRIPTOR_HANDLE samcpu(pIcullasamheap->GetCPUDescriptorHandleForHeapStart());
                pID3DDevice->CreateSampler(&stSamplerDesc, samcpu);
                 range = { 0,0 };
                byte* mappedcb[30];
                CD3DX12_CPU_DESCRIPTOR_HANDLE srvheapcpu = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetCPUDescriptorHandleForHeapStart());
                for (int i = 0;i < 30;i++) {
                    srvheapcpu.Offset(pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(passconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIcubeCB[i]));
                    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvdesc = {};
                    cbvdesc.BufferLocation = pIcubeCB[i]->GetGPUVirtualAddress();
                    cbvdesc.SizeInBytes = sizeof(passconstant) + 255 & ~255;
                    pID3DDevice->CreateConstantBufferView(&cbvdesc, srvheapcpu);
                    pIcubeCB[i]->Map(0, &range, reinterpret_cast<void**>(&mappedcb[i]));
                    if(i==5)
                        srvheapcpu.Offset(pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                }
                srvheapcpu = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetCPUDescriptorHandleForHeapStart(), 7, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                D3D12_SHADER_RESOURCE_VIEW_DESC cubesrvdesc = {};
                cubesrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
                cubesrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
                cubesrvdesc.Format = SMtex3->GetDesc().Format;
                cubesrvdesc.Texture2D.MostDetailedMip = 0;
                cubesrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
                cubesrvdesc.Texture2D.MipLevels = SMtex3->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(SMtex3.Get(), &cubesrvdesc, srvheapcpu);
                for (int i = 0;i < 30;i++) {
                    passconstant pass;
                    pass.eyepos = XMFLOAT3(15.0f, 15.0f, 0);
                    XMVECTOR eyeposv = XMVectorSet(0, 0, 0, 0);
                    if(i<6)
                    pass.m = 0.2f;
                    if (i >= 6&&i<12)
                        pass.m = 0.4f;
                    if (i >= 12&&i<18)
                        pass.m = 0.6f;
                    if (i >= 18&&i<24)
                        pass.m = 0.8f;
                    if (i >= 24&&i<30)
                        pass.m = 1.0f;
                    XMMATRIX passview = XMMatrixLookToLH(eyeposv, targetvec[i%6], upvec[i%6]);
                    XMStoreFloat4x4(&pass.V, XMMatrixTranspose(passview));
                    XMMATRIX passproj = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)1024 / (FLOAT)1024, 0.1f, 1000.0f);
                    XMStoreFloat4x4(&pass.VP, XMMatrixTranspose(XMMatrixMultiply(passview, passproj)));
                    XMStoreFloat3(&pass.lightPos, lightposition);
                    XMStoreFloat4x4(&pass.S, lightviewproj);
                    XMStoreFloat4x4(&pass.uvMAT, smuvmat);
                    memcpy(mappedcb[i], &pass, sizeof(passconstant));
                }
               
                ThrowIfFailed(pIcmdallpre->Reset());
                ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                //drawculla
                pIcmdlistpre->SetPipelineState(pIcullaPSO.Get());
                pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(cullaPrecomputeEmu.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                CD3DX12_CPU_DESCRIPTOR_HANDLE rtvhandlecp = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 9, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            

                pIcmdlistpre->OMSetRenderTargets(1,&rtvhandlecp , FALSE, nullptr);
                pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                pIcmdlistpre->IASetVertexBuffers(0, 1, &cullavbv);
                pIcmdlistpre->IASetIndexBuffer(&cullaibv);
                pIcmdlistpre->DrawIndexedInstanced(cullai.size(), 1, 0, 0, 0);
             
                pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(cullaPrecomputeEmu.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));



                pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(cullaPrecomputeEmuavg.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                rtvhandlecp.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pIcmdlistpre->SetPipelineState(pIcullaavgPSO.Get());
                pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);

                pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                pIcmdlistpre->IASetVertexBuffers(0, 1, &cullavbv);
                pIcmdlistpre->IASetIndexBuffer(&cullaibv);
          
                pIcmdlistpre->DrawIndexedInstanced(cullai.size(), 1, 0, 0, 0);
                pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(cullaPrecomputeEmuavg.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));

       /*         pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(cullaPrecomputeFmuavg.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                rtvhandlecp.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                pIcmdlistpre->SetPipelineState(pIcullaFavgPSO.Get());
                pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);

                pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                pIcmdlistpre->IASetVertexBuffers(0, 1, &cullavbv);
                pIcmdlistpre->IASetIndexBuffer(&cullaibv);

                pIcmdlistpre->DrawIndexedInstanced(cullai.size(), 1, 0, 0, 0);
                pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(cullaPrecomputeFmuavg.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));*/
                pIcmdlistpre->Close();
                cmdlists.RemoveAll();

                cmdlists.Add(pIcmdlistpre.Get());
                pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                n64fence = n64FenceValue;
                n64FenceValue++;
                pICommandQueue->Signal(pIFence.Get(), n64fence);
                pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                HandleMessage->RemoveAll();
                HandleMessage->Add(hFenceEvent);
                ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);
                //drawprecubemap
             
                D3D12_VIEWPORT stpreViewPort = { 0.0f, 0.0f, static_cast<float>(1024), static_cast<float>(1024), D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
     
                D3D12_RECT							stpreScissorRect = { 0, 0, static_cast<LONG>(2048), static_cast<LONG>(2048) };
                ThrowIfFailed(pIcmdallpre->Reset());
                ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                pIcmdlistpre->SetPipelineState(pIcubePSO.Get());
                pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                pIcmdlistpre->RSSetScissorRects(1, &stpreScissorRect);
                pIcmdlistpre->RSSetViewports(1, &stpreViewPort);
                pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                ID3D12DescriptorHeap* heapscube[] = { pIcullacbvheap.Get() ,pIcullasamheap.Get() };
                pIcmdlistpre->SetDescriptorHeaps(2, heapscube);
                CD3DX12_GPU_DESCRIPTOR_HANDLE cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(),7,pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistpre->SetGraphicsRootDescriptorTable(4, cubegpuhandle);
                rtvhandlecp = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 11, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                  cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart());
             
              
                 for (int i = 0;i < 6;i++) {
                     rtvhandlecp.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                     cubegpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              
                     pIcmdlistpre->SetGraphicsRootDescriptorTable(2, cubegpuhandle);

                     pIcmdlistpre->SetGraphicsRootDescriptorTable(1, pIcullasamheap->GetGPUDescriptorHandleForHeapStart());
                     pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);
                     pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                     pIcmdlistpre->IASetVertexBuffers(0, 1, &cubevbv);
                     pIcmdlistpre->IASetIndexBuffer(&cubeibv);
                     pIcmdlistpre->DrawIndexedInstanced(6,1, i*6, 0, 0);
                 }
              
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));

                     pIcmdlistpre->Close();
                     cmdlists.RemoveAll();

                     cmdlists.Add(pIcmdlistpre.Get());
                     pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                     n64fence = n64FenceValue;
                     n64FenceValue++;
                     pICommandQueue->Signal(pIFence.Get(), n64fence);
                     pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                     HandleMessage->RemoveAll();
                     HandleMessage->Add(hFenceEvent);
                     ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);




                     ThrowIfFailed(pIcmdallpre->Reset());
                     ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                     pIcmdlistpre->SetPipelineState(pIcubePSO.Get());
                     pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                     pIcmdlistpre->RSSetScissorRects(1, &stpreScissorRect);
                     pIcmdlistpre->RSSetViewports(1, &stpreViewPort);
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap1.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                    
                     pIcmdlistpre->SetDescriptorHeaps(2, heapscube);
                      cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(), 7, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                     pIcmdlistpre->SetGraphicsRootDescriptorTable(4, cubegpuhandle);
                     rtvhandlecp = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 18, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                     cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(), 7, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));


                     for (int i = 0;i < 6;i++) {
                         rtvhandlecp.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                         cubegpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(2, cubegpuhandle);

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(1, pIcullasamheap->GetGPUDescriptorHandleForHeapStart());
                         pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);
                         pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                         pIcmdlistpre->IASetVertexBuffers(0, 1, &cubevbv);
                         pIcmdlistpre->IASetIndexBuffer(&cubeibv);
                         pIcmdlistpre->DrawIndexedInstanced(6, 1, i * 6, 0, 0);
                     }
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap1.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));

                     pIcmdlistpre->Close();
                     cmdlists.RemoveAll();

                     cmdlists.Add(pIcmdlistpre.Get());
                     pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                     n64fence = n64FenceValue;
                     n64FenceValue++;
                     pICommandQueue->Signal(pIFence.Get(), n64fence);
                     pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                     HandleMessage->RemoveAll();
                     HandleMessage->Add(hFenceEvent);
                     ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);



                     ThrowIfFailed(pIcmdallpre->Reset());
                     ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                     pIcmdlistpre->SetPipelineState(pIcubePSO.Get());
                     pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                     pIcmdlistpre->RSSetScissorRects(1, &stpreScissorRect);
                     pIcmdlistpre->RSSetViewports(1, &stpreViewPort);
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                    
                     pIcmdlistpre->SetDescriptorHeaps(2, heapscube);
                      cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(), 7, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                     pIcmdlistpre->SetGraphicsRootDescriptorTable(4, cubegpuhandle);
                   //  rtvhandlecp = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 24, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                     cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(), 13, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));


                     for (int i = 0;i < 6;i++) {
                         rtvhandlecp.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                         cubegpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(2, cubegpuhandle);

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(1, pIcullasamheap->GetGPUDescriptorHandleForHeapStart());
                         pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);
                         pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                         pIcmdlistpre->IASetVertexBuffers(0, 1, &cubevbv);
                         pIcmdlistpre->IASetIndexBuffer(&cubeibv);
                         pIcmdlistpre->DrawIndexedInstanced(6, 1, i * 6, 0, 0);
                     }
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));

                     pIcmdlistpre->Close();
                     cmdlists.RemoveAll();

                     cmdlists.Add(pIcmdlistpre.Get());
                     pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                     n64fence = n64FenceValue;
                     n64FenceValue++;
                     pICommandQueue->Signal(pIFence.Get(), n64fence);
                     pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                     HandleMessage->RemoveAll();
                     HandleMessage->Add(hFenceEvent);
                     ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);



                     ThrowIfFailed(pIcmdallpre->Reset());
                     ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                     pIcmdlistpre->SetPipelineState(pIcubePSO.Get());
                     pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                     pIcmdlistpre->RSSetScissorRects(1, &stpreScissorRect);
                     pIcmdlistpre->RSSetViewports(1, &stpreViewPort);
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                   
                     pIcmdlistpre->SetDescriptorHeaps(2, heapscube);
                      cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(), 7, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                     pIcmdlistpre->SetGraphicsRootDescriptorTable(4, cubegpuhandle);
                    // rtvhandlecp = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 30, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                     cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(), 19, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));


                     for (int i = 0;i < 6;i++) {
                         rtvhandlecp.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                         cubegpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(2, cubegpuhandle);

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(1, pIcullasamheap->GetGPUDescriptorHandleForHeapStart());
                         pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);
                         pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                         pIcmdlistpre->IASetVertexBuffers(0, 1, &cubevbv);
                         pIcmdlistpre->IASetIndexBuffer(&cubeibv);
                         pIcmdlistpre->DrawIndexedInstanced(6, 1, i * 6, 0, 0);
                     }
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));

                     pIcmdlistpre->Close();
                     cmdlists.RemoveAll();

                     cmdlists.Add(pIcmdlistpre.Get());
                     pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                     n64fence = n64FenceValue;
                     n64FenceValue++;
                     pICommandQueue->Signal(pIFence.Get(), n64fence);
                     pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                     HandleMessage->RemoveAll();
                     HandleMessage->Add(hFenceEvent);
                     ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);




                     ThrowIfFailed(pIcmdallpre->Reset());
                     ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                     pIcmdlistpre->SetPipelineState(pIcubePSO.Get());
                     pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                     pIcmdlistpre->RSSetScissorRects(1, &stpreScissorRect);
                     pIcmdlistpre->RSSetViewports(1, &stpreViewPort);
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                   
                     pIcmdlistpre->SetDescriptorHeaps(2, heapscube);
                      cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart(), 7, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                     pIcmdlistpre->SetGraphicsRootDescriptorTable(4, cubegpuhandle);
                    // rtvhandlecp = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 36, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                     cubegpuhandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIcullacbvheap->GetGPUDescriptorHandleForHeapStart() ,25, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));


                     for (int i = 0;i < 6;i++) {
                         rtvhandlecp.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                         cubegpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(2, cubegpuhandle);

                         pIcmdlistpre->SetGraphicsRootDescriptorTable(1, pIcullasamheap->GetGPUDescriptorHandleForHeapStart());
                         pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);
                         pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                         pIcmdlistpre->IASetVertexBuffers(0, 1, &cubevbv);
                         pIcmdlistpre->IASetIndexBuffer(&cubeibv);
                         pIcmdlistpre->DrawIndexedInstanced(6, 1, i * 6, 0, 0);
                     }
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(prefiltercubemap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));

                     pIcmdlistpre->Close();
                     cmdlists.RemoveAll();

                     cmdlists.Add(pIcmdlistpre.Get());
                     pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                     n64fence = n64FenceValue;
                     n64FenceValue++;
                     pICommandQueue->Signal(pIFence.Get(), n64fence);
                     pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                     HandleMessage->RemoveAll();
                     HandleMessage->Add(hFenceEvent);
                     ::MsgWaitForMultipleObjects(HandleMessage->GetCount(), HandleMessage->GetData(), TRUE, INFINITE, QS_ALLINPUT);



                //draw IBLLUT
                     ThrowIfFailed(pIcmdallpre->Reset());
                     ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), pISMPSO.Get()));
                     pIcmdlistpre->SetPipelineState(pIIBLLUTPSO.Get());
                     pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                     pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                     pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(IBLLUT.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                   
                     rtvhandlecp = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 18, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                     pIcmdlistpre->OMSetRenderTargets(1, &rtvhandlecp, FALSE, nullptr);
                     pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                     pIcmdlistpre->IASetVertexBuffers(0, 1, &cullavbv);
                     pIcmdlistpre->IASetIndexBuffer(&cullaibv);
                     pIcmdlistpre->DrawIndexedInstanced(cullai.size(), 1, 0, 0, 0);

                     pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(IBLLUT.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
                //drawSM
                pIcmdlistpre->SetPipelineState(pISMPSO.Get());
                pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                pIcmdlistpre->RSSetViewports(1,&stSMViewPort);
                CD3DX12_CPU_DESCRIPTOR_HANDLE SMdsvhandle(pIDSVHeap->GetCPUDescriptorHandleForHeapStart(), 1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV));
                pIcmdlistpre->ClearDepthStencilView(SMdsvhandle, D3D12_CLEAR_FLAG_DEPTH , 1.0f, 0, 0, nullptr);
                pIcmdlistpre->OMSetRenderTargets(0, nullptr, FALSE, &SMdsvhandle);
                XMFLOAT3 litpos = XMFLOAT3{ 500,500,50.0f };
                XMVECTOR lightpos = XMLoadFloat3(&litpos);
                XMStoreFloat3(&currpasscb.lightPos, lightpos);
                mboundingsphere.Center = XMFLOAT3{ 0,-7.5f,50 };
                XMVECTOR lighttarget = XMLoadFloat3(&mboundingsphere.Center);
                XMVECTOR lightup = XMVectorSet(0, 1.0f, 0, 0);
                XMMATRIX lightview = XMMatrixLookAtLH(lightpos, lighttarget, lightup);
                XMFLOAT3 boundingcenterlightcoord;
                XMStoreFloat3(&boundingcenterlightcoord, XMVector3TransformCoord(lighttarget, lightview));
                float l = boundingcenterlightcoord.x - mboundingsphere.Radius*2.5f;//lrtb越大，整体越小，表示整个投影平面
                float b = boundingcenterlightcoord.y - mboundingsphere.Radius * 4.0f;
                float n = boundingcenterlightcoord.z - mboundingsphere.Radius * 4.0f;
                float r = boundingcenterlightcoord.x + mboundingsphere.Radius * 2.5f;
                float t = boundingcenterlightcoord.y + mboundingsphere.Radius * 2.5f;
                float f = boundingcenterlightcoord.z + mboundingsphere.Radius * 5.0f;
             XMMATRIX projmat = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)1 / (FLOAT)1, 0.1f, 1000.0f);
                mlightnearz = n;
                mlightfarz = f;
                lightviewproj = XMMatrixMultiply(lightview,XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f));
                
                XMStoreFloat4x4(&currpasscb.S, XMMatrixTranspose( lightviewproj));
                XMMATRIX UVmat(0.5f,0.0f,0.0f,0.0f,
                    0.0f,-0.5f,0.0f,0.0f,
                    0.0f,0.0f,1.0f,0.0f,
               0.5f,0.5f,0.0f,1.0f );
                XMStoreFloat4x4(&currpasscb.uvMAT,XMMatrixTranspose( UVmat));
               
                for (int i = 3072;i < 4096;i++) {
                    randarr[i] = (rand() % 101) / 100.0f;
               
               
                }
                std::mt19937 gen((unsigned int)time(nullptr)); // 定义随机数生成器对象gen，使用time(nullptr)作为随机数生成器的种子
                std::normal_distribution<double> dis(0.0, 1.0); // 定义随机数分布器对象dis，期望为0.0，标准差为1.0的正态分布

                for (int i = 0;i < 3072;i++) {
                 
                    randarr[i] = dis(gen);

                }
                currpasscb.randnum = randarr;
               
                presrvheapdesc.NumDescriptors = 10+1+1+1+4+1+1+2+1+22+1+3+6+6+6+42+8+48+6;//最后一个是SSAOCBV ssaoobjcb viewdepthmap  (第13个开始为diff)4个flux要的diffmap RSM的objcb SSDODL的tex和sky  1个SSRcolorBobjCB 11个Hizmap的SRV和11个UAV 1个Hiz的cbv 3个RSM的map（worldpos，normal，flux） 6个LPVvoxeltex  6个clipmapUAV 6个clipmapSRV 42个UAV 8个LASTmipCBV  48个climapNoemalUAV 6个SRV
                presrvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
                presrvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
                ThrowIfFailed(pID3DDevice->CreateDescriptorHeap(&presrvheapdesc, IID_PPV_ARGS(&pIpresrvheap)));
        
                presrvheapdesc.NumDescriptors = 1;
                presrvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
                presrvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
                ThrowIfFailed(pID3DDevice->CreateDescriptorHeap(&presrvheapdesc, IID_PPV_ARGS(&pIpresamheap)));
                D3D12_SAMPLER_DESC preSamplerDesc = {};
                preSamplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
                preSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
                preSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
                preSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
                preSamplerDesc.MipLODBias = 0;
                preSamplerDesc.MaxAnisotropy = 1;
                preSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
                preSamplerDesc.MinLOD = 0.0f;
                preSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
                CD3DX12_CPU_DESCRIPTOR_HANDLE presamcpu(pIpresamheap->GetCPUDescriptorHandleForHeapStart());
                pID3DDevice->CreateSampler(&preSamplerDesc, presamcpu);
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(passconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pISMpassCB)));
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(objectconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIRSMobjCB)));
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(passconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pISSAOCB)));
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(objectconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pISSAOobjCB)));
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(objectconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pISSRobjCB)));
                for(int i=0;i<8;i++)
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(Hizmipsdata)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIHizmipsCB[i])));
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(passconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIcullapassCB)));


                for(int i=0;i<4;i++)
                ThrowIfFailed(pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(objectconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pISMobjCB[i])));
                byte* SMpass = nullptr;
                byte* RSMobj = nullptr;

                byte* SMobj[4];
                D3D12_RANGE rangesm = { 0,0 };
                pISMpassCB->Map(0, &rangesm, reinterpret_cast<void**>(&SMpass));
                pIRSMobjCB->Map(0, &rangesm, reinterpret_cast<void**>(&RSMobj));
                pISSAOCB->Map(0, &rangesm, reinterpret_cast<void**>(&SSAOmapped));
                pISSAOobjCB->Map(0, &rangesm, reinterpret_cast<void**>(&SSAOobjmapped));
                pISSRobjCB->Map(0, &rangesm, reinterpret_cast<void**>(&SSRobjmapped));
                for(int i=0;i<8;i++)
                pIHizmipsCB[i]->Map(0, &rangesm, reinterpret_cast<void**>(&Hizmipsmap[i]));
                for (int i = 0;i < 4;i++) {
                    SMobj[i] = nullptr;
                    pISMobjCB[i]->Map(0, &rangesm, reinterpret_cast<void**>(&SMobj[i]));
                }
                CD3DX12_CPU_DESCRIPTOR_HANDLE presrvheapcpu(pIpresrvheap->GetCPUDescriptorHandleForHeapStart());
                D3D12_SHADER_RESOURCE_VIEW_DESC smsrvdesc = {};
                smsrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
                smsrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                smsrvdesc.Format = SMtex1->GetDesc().Format;
                smsrvdesc.Texture2D.MostDetailedMip = 0;
                smsrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
                smsrvdesc.Texture2D.MipLevels = SMtex1->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(SMtex1.Get(), &smsrvdesc, presrvheapcpu);
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                smsrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                smsrvdesc.Format = SMtex2->GetDesc().Format;
                smsrvdesc.Texture2D.MostDetailedMip = 0;
                smsrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
                smsrvdesc.Texture2D.MipLevels = SMtex2->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(SMtex2.Get(), &smsrvdesc, presrvheapcpu);
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                smsrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
                smsrvdesc.Format = SMtex3->GetDesc().Format;
                smsrvdesc.TextureCube.MostDetailedMip = 0;
                smsrvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
                smsrvdesc.TextureCube.MipLevels = SMtex3->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(SMtex3.Get(), &smsrvdesc, presrvheapcpu);
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                D3D12_CONSTANT_BUFFER_VIEW_DESC SMcbv = {};
                SMcbv.BufferLocation = pISMpassCB->GetGPUVirtualAddress();
                SMcbv.SizeInBytes = sizeof(passconstant)+255&~255;
              

                pID3DDevice->CreateConstantBufferView(&SMcbv,presrvheapcpu);
              
            
                 presrvheapcpu=CD3DX12_CPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetCPUDescriptorHandleForHeapStart(),3,pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                for (int i = 0;i < 4;i++) {
                    presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    SMcbv.BufferLocation = pISMobjCB[i]->GetGPUVirtualAddress();
                    SMcbv.SizeInBytes = sizeof(objectconstant)+255&~255;
                    pID3DDevice->CreateConstantBufferView(&SMcbv, presrvheapcpu);
                }
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                D3D12_SHADER_RESOURCE_VIEW_DESC cullasrvdesc = {};
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Format = cullaPrecomputeEmu->GetDesc().Format;
                cullasrvdesc.Texture2D.MostDetailedMip = 0;
                cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
                cullasrvdesc.Texture2D.MipLevels = cullaPrecomputeEmu->GetDesc().MipLevels;
                cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
                pID3DDevice->CreateShaderResourceView(cullaPrecomputeEmu.Get(), &cullasrvdesc, presrvheapcpu);
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                cullasrvdesc.Format = cullaPrecomputeEmuavg->GetDesc().Format;
                cullasrvdesc.Texture2D.MipLevels = cullaPrecomputeEmuavg->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(cullaPrecomputeEmuavg.Get(), &cullasrvdesc, presrvheapcpu);
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                SMcbv.BufferLocation = pISSAOCB->GetGPUVirtualAddress();
                SMcbv.SizeInBytes = sizeof(passconstant) + 255 & ~255;

                pID3DDevice->CreateConstantBufferView(&SMcbv, presrvheapcpu);
                SMcbv.BufferLocation = pISSAOobjCB->GetGPUVirtualAddress();
                SMcbv.SizeInBytes = sizeof(objectconstant) + 255 & ~255;
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pID3DDevice->CreateConstantBufferView(&SMcbv, presrvheapcpu);

                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                cullasrvdesc.Format = headdiff->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = headdiff->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(headdiff.Get(), &cullasrvdesc, presrvheapcpu);//headdiff
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                cullasrvdesc.Format = jacketdiff->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = jacketdiff->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(jacketdiff.Get(), &cullasrvdesc, presrvheapcpu);//jacketdiff
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                cullasrvdesc.Format = pantsdiff->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = pantsdiff->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(pantsdiff.Get(), &cullasrvdesc, presrvheapcpu);//pantsdiff
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                cullasrvdesc.Format = upbodydiff->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = upbodydiff->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(upbodydiff.Get(), &cullasrvdesc, presrvheapcpu);//upbodydiff
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//第16个off
                SMcbv.BufferLocation = pIRSMobjCB->GetGPUVirtualAddress();
                SMcbv.SizeInBytes = sizeof(objectconstant) + 255 & ~255;


                pID3DDevice->CreateConstantBufferView(&SMcbv, presrvheapcpu);//RSMobjCB
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                cullasrvdesc.Format = SMtex1->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = SMtex1->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(SMtex1.Get(), &cullasrvdesc, presrvheapcpu);//SSDODLtex
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                cullasrvdesc.Format = SMtex3->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
                cullasrvdesc.Texture2D.MipLevels = SMtex3->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(SMtex3.Get(), &cullasrvdesc, presrvheapcpu);//SSDODLsky
                SMcbv.BufferLocation = pISSRobjCB->GetGPUVirtualAddress();
                SMcbv.SizeInBytes = sizeof(objectconstant) + 255 & ~255;
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//19
                pID3DDevice->CreateConstantBufferView(&SMcbv, presrvheapcpu);//SSRobjCB
             
                cullasrvdesc.Format = Hi_zMipmap->GetDesc().Format;
                //cullasrvdesc.Texture2D.PlaneSlice
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                for(int i=0;i<11;i++){
                    presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//20
                cullasrvdesc.Texture2D.MipLevels = 1;//srv包括了纹理中多少个levels
                cullasrvdesc.Texture2D.MostDetailedMip = i;//第一个（最详细的）level是多少（原纹理level从0到10）
                //cullasrvdesc.Texture2D.ResourceMinLODClamp = i;
                pID3DDevice->CreateShaderResourceView(Hi_zMipmap.Get(), &cullasrvdesc, presrvheapcpu);//HizSRV  
                }
              
                D3D12_UNORDERED_ACCESS_VIEW_DESC UAVdesc = {};
                for (int i = 0;i < 11;i++) {
                    presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    UAVdesc.Format = Hi_zMipmap->GetDesc().Format;
                    UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
                    UAVdesc.Texture2D.MipSlice = i;//输出的uav是第几层level
                    UAVdesc.Texture2D.PlaneSlice = 0;
                    
                    pID3DDevice->CreateUnorderedAccessView(Hi_zMipmap.Get(), nullptr, &UAVdesc, presrvheapcpu);//HizUAV
                }
                UAVdesc.Texture2D.MipSlice = 0;//输出的uav是第几层level
                cullasrvdesc.Texture2D.MostDetailedMip = 0;
                //SMcbv.BufferLocation = pIHizmipsCB->GetGPUVirtualAddress();
                SMcbv.SizeInBytes = sizeof(Hizmipsdata) + 255 & ~255;
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                //pID3DDevice->CreateConstantBufferView(&SMcbv, presrvheapcpu);//HizmipsCB
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//43
                cullasrvdesc.Format = RSMwposmap->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = RSMwposmap->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(RSMwposmap.Get(), &cullasrvdesc, presrvheapcpu);//RSMwpos
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//44
                cullasrvdesc.Format = RSMnormalmap->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = RSMnormalmap->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(RSMnormalmap.Get(), &cullasrvdesc, presrvheapcpu);//RSMnormal
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//45
                cullasrvdesc.Format = RSMfluxmap->GetDesc().Format;
                cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
                cullasrvdesc.Texture2D.MipLevels = RSMfluxmap->GetDesc().MipLevels;
                pID3DDevice->CreateShaderResourceView(RSMfluxmap.Get(), &cullasrvdesc, presrvheapcpu);//RSMflux
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//46
                UAVdesc.Format = LPVvoxelTex->GetDesc().Format;
                UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
                UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level
                UAVdesc.Texture3D.FirstWSlice = 0;//第一个深度切片索引
                UAVdesc.Texture3D.WSize = -1;
                
                pID3DDevice->CreateUnorderedAccessView(LPVvoxelTex.Get(), nullptr, &UAVdesc, presrvheapcpu);//LPVvoxeltex
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//47
                UAVdesc.Format = LPVvoxelTex2->GetDesc().Format;
                UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
                UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level
              

                pID3DDevice->CreateUnorderedAccessView(LPVvoxelTex2.Get(), nullptr, &UAVdesc, presrvheapcpu);//LPVvoxeltex2
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//48
                UAVdesc.Format = LPVvoxelTex3->GetDesc().Format;
                UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
                UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level
               

                pID3DDevice->CreateUnorderedAccessView(LPVvoxelTex3.Get(), nullptr, &UAVdesc, presrvheapcpu);//LPVvoxeltex3
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//49
                UAVdesc.Format = LPVvoxelTex4->GetDesc().Format;
                UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
                UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level


                pID3DDevice->CreateUnorderedAccessView(LPVvoxelTex4.Get(), nullptr, &UAVdesc, presrvheapcpu);//LPVvoxeltex4
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//50
                UAVdesc.Format = LPVvoxelTex5->GetDesc().Format;
                UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
                UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level


                pID3DDevice->CreateUnorderedAccessView(LPVvoxelTex5.Get(), nullptr, &UAVdesc, presrvheapcpu);//LPVvoxeltex5
                presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//51
                UAVdesc.Format = LPVvoxelTex6->GetDesc().Format;
                UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
                UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level


                pID3DDevice->CreateUnorderedAccessView(LPVvoxelTex6.Get(), nullptr, &UAVdesc, presrvheapcpu);//LPVvoxeltex6
                for (int i = 0;i < 6;i++) {
                    presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//52
                    UAVdesc.Format = clipMapArray[i]->GetDesc().Format;
                    pID3DDevice->CreateUnorderedAccessView(clipMapArray[i].Get(), nullptr, &UAVdesc, presrvheapcpu);//clipmapUAV
                }
                for (int i = 0;i < 6;i++) {
                    presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//58
                    cullasrvdesc.Format = clipMapArray[i]->GetDesc().Format;
                    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
                    cullasrvdesc.Texture3D.MipLevels = clipMapArray[i]->GetDesc().MipLevels;
                    cullasrvdesc.Texture3D.MostDetailedMip = 0;
                    cullasrvdesc.Texture3D.ResourceMinLODClamp = 0;
                    pID3DDevice->CreateShaderResourceView(clipMapArray[i].Get(), &cullasrvdesc, presrvheapcpu);//clipmapSRV
                }
                for (int i = 0;i < 6;i++) {
                    for (int j = 1;j < 8;j++) {
                        presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//64
                        UAVdesc.Format = clipMapArray[i]->GetDesc().Format;
                        UAVdesc.Texture3D.MipSlice = j;
                        pID3DDevice->CreateUnorderedAccessView(clipMapArray[i].Get(), nullptr, &UAVdesc, presrvheapcpu);//clipmapUAV
                    }
                }
                for (int i = 0;i < 8;i++) {
                    SMcbv.BufferLocation = pIHizmipsCB[i]->GetGPUVirtualAddress();
                    SMcbv.SizeInBytes = sizeof(Hizmipsdata) + 255 & ~255;
                    presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//106
                    pID3DDevice->CreateConstantBufferView(&SMcbv, presrvheapcpu);//SSRobjCB
                }
                for (int i = 0;i < 6;i++) {
                    for (int j = 0;j < 8;j++) {
                        presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//114
                        UAVdesc.Format = clipMapNormalArray[i]->GetDesc().Format;
                        UAVdesc.Texture3D.MipSlice = j;
                        pID3DDevice->CreateUnorderedAccessView(clipMapNormalArray[i].Get(), nullptr, &UAVdesc, presrvheapcpu);//clipmapNormalUAV
                    }
                }
                for (int i = 0;i < 6;i++) {
                    presrvheapcpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//162
                    cullasrvdesc.Format = clipMapNormalArray[i]->GetDesc().Format;
                    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
                    cullasrvdesc.Texture3D.MipLevels = clipMapNormalArray[i]->GetDesc().MipLevels;
                    cullasrvdesc.Texture3D.MostDetailedMip = 0;
                    cullasrvdesc.Texture3D.ResourceMinLODClamp = 0;
                   
                    pID3DDevice->CreateShaderResourceView(clipMapNormalArray[i].Get(), &cullasrvdesc, presrvheapcpu);//clipmapSRV
                }
                    currpasscb.randnum = randarr;
                memcpy(SMpass, &currpasscb, sizeof(passconstant));
   
                //球
                ID3D12DescriptorHeap* heapssm[] = { pIpresrvheap.Get(),pIpresamheap.Get()};
                pIcmdlistpre->SetDescriptorHeaps(2, heapssm);
                pIcmdlistpre->SetGraphicsRootDescriptorTable(1, pIpresamheap->GetGPUDescriptorHandleForHeapStart());
                CD3DX12_GPU_DESCRIPTOR_HANDLE presrvgpu(pIpresrvheap->GetGPUDescriptorHandleForHeapStart());
                pIcmdlistpre->SetGraphicsRootDescriptorTable(0, presrvgpu);
                presrvgpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistpre->SetGraphicsRootDescriptorTable(3, presrvgpu);
                presrvgpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistpre->SetGraphicsRootDescriptorTable(4, presrvgpu);
                 presrvgpu= CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(),3,pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistpre->SetGraphicsRootDescriptorTable(2, presrvgpu);
                XMMATRIX smworld = XMMatrixTranslationFromVector(XMVectorSet(0, 20.0f, 0, 0));
                objectconstant objc;
                 XMStoreFloat4x4(&objc.world,XMMatrixTranspose(smworld));
                 memcpy(SMobj[0], &objc, sizeof(objectconstant));
                 presrvgpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(5, presrvgpu);

                 pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &SMvbv[0]);
                 pIcmdlistpre->IASetIndexBuffer(&SMibv[0]);
                 pIcmdlistpre->DrawIndexedInstanced(mesh12.indices.size(), 1, 0, 0, 0);
                  smworld = XMMatrixTranslationFromVector(XMVectorSet(0, 0.0f, 0, 0));
                
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(smworld));
                 memcpy(SMobj[1], &objc, sizeof(objectconstant));
                 presrvgpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(5, presrvgpu);
                 pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &SMvbv[1]);
                 pIcmdlistpre->IASetIndexBuffer(&SMibv[1]);
                 pIcmdlistpre->DrawIndexedInstanced(indices.size(), 1, 0, 0, 0);
                 smworld = XMMatrixTranslationFromVector(XMVectorSet(0.0f, 0.0f, 0, 0));
                
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(smworld));
                 memcpy(SMobj[2], &objc, sizeof(objectconstant));
                 presrvgpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(5, presrvgpu);
                 pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &SMvbv[2]);
                 pIcmdlistpre->IASetIndexBuffer(&SMibv[2]);
                 pIcmdlistpre->DrawIndexedInstanced(planei.size(), 1, 0, 0, 0);
                 smworld = XMMatrixTranslationFromVector(XMVectorSet(20.0f, 20.0f, 0, 0));

                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(smworld));
                 memcpy(SMobj[3], &objc, sizeof(objectconstant));
                 presrvgpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(5, presrvgpu);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &SMvbv[0]);
                 pIcmdlistpre->IASetIndexBuffer(&SMibv[0]);
                 pIcmdlistpre->DrawIndexedInstanced(mesh12.indices.size(), 1, 0, 0, 0);
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIShadowMap.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ));
                 


                 //drawRSM
                 //depthmap
                 CD3DX12_CPU_DESCRIPTOR_HANDLE depthmaphandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart(), 3, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV));
                 CD3DX12_CPU_DESCRIPTOR_HANDLE RSMrtv = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 44, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
        /*         pIcmdlistpre->SetPipelineState(pISMPSO.Get());
                 pIcmdlistpre->OMSetRenderTargets(0, nullptr, FALSE, &depthmaphandle);
                 pIcmdlistpre->ClearDepthStencilView(depthmaphandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
                 pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
                 pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                 pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                 pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &RSMvbv);
                 pIcmdlistpre->IASetIndexBuffer(&RSMibv);

                 pIcmdlistpre->DrawIndexedInstanced(RSMi.size(), 1, 0, 0, 0);
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMdepthmap.Get(), D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ));*/
                 XMMATRIX rsmworld = XMMatrixTranslationFromVector(XMVectorSet(0, 0, 0.0f, 0));
                
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(rsmworld));
                 memcpy(RSMobj, &objc, sizeof(objectconstant));
                 //fluxmap
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMfluxmap.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                 pIcmdlistpre->SetPipelineState(pIRSMfluxPSO.Get());
                 pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());
               
                 ID3D12DescriptorHeap* heapsculla[] = { pIpresrvheap.Get(),pIpresamheap.Get()};
                 pIcmdlistpre->SetDescriptorHeaps(2, heapsculla);
                  depthmaphandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
                  pIcmdlistpre->ClearDepthStencilView(depthmaphandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
                  pIcmdlistpre->ClearRenderTargetView(RSMrtv, Colors::Black , 0, nullptr);

                 pIcmdlistpre->OMSetRenderTargets(1, &RSMrtv, FALSE, &depthmaphandle);
                 presrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 3, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(2, presrvgpu);
                 presrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 16, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(5, presrvgpu);
                 CD3DX12_GPU_DESCRIPTOR_HANDLE samgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(1, samgpu);
                 pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                 pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                 pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &RSMvbv);
                 pIcmdlistpre->IASetIndexBuffer(&RSMibv);

                 int istarr[5] = { 0+12,7230 * 3+12,11679 * 3+12,18258 * 3+12,22065 * 3+12 };
                 int vstarr[5] = { 0,3915,6899,11169,13474 };
                 UINT vsizearr[5] = { 3915,2984,4270,2305,274 };
                 UINT isizearr[5] = { 7230 * 3 ,4449 * 3 ,6579 * 3 ,3807 * 3 ,442 * 3 };
                 for (int i = 0;i < 4;i++) {

                     CD3DX12_GPU_DESCRIPTOR_HANDLE  srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 12+i, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                     pIcmdlistpre->SetGraphicsRootDescriptorTable(0, srvgpu);


                     pIcmdlistpre->DrawIndexedInstanced(isizearr[i], 1, istarr[i], 0, 0);//index是总体vertex的index，所以第四个参数为0;

                 }
                 pIcmdlistpre->DrawIndexedInstanced(12, 1,0, 0, 0);
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMfluxmap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
                 //normalMap
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMnormalmap.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                 pIcmdlistpre->SetPipelineState(pIRSMnormalPSO.Get());
                 pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());

               
                 pIcmdlistpre->SetDescriptorHeaps(2, heapsculla);
                 depthmaphandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
                 pIcmdlistpre->ClearDepthStencilView(depthmaphandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
                 RSMrtv = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 45, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                 pIcmdlistpre->ClearRenderTargetView(RSMrtv, Colors::Aquamarine, 0, nullptr);

                 pIcmdlistpre->OMSetRenderTargets(1, &RSMrtv, FALSE, &depthmaphandle);
                 presrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 3, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(2, presrvgpu);
                  samgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(1, samgpu);
                 pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                 pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                 pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &RSMvbv);
                 pIcmdlistpre->IASetIndexBuffer(&RSMibv);
                 pIcmdlistpre->DrawIndexedInstanced(RSMi.size(), 1,0, 0, 0);
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMnormalmap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
                 //worldPos
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMwposmap.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                 pIcmdlistpre->SetPipelineState(pIRSMworldposPSO.Get());
                 pIcmdlistpre->SetGraphicsRootSignature(pIRootSignature.Get());

              
                 pIcmdlistpre->SetDescriptorHeaps(2, heapsculla);
                 depthmaphandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
                 pIcmdlistpre->ClearDepthStencilView(depthmaphandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
                 RSMrtv = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 46, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                 pIcmdlistpre->ClearRenderTargetView(RSMrtv, Colors::Aquamarine, 0, nullptr);

                 pIcmdlistpre->OMSetRenderTargets(1, &RSMrtv, FALSE, &depthmaphandle);
                 presrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 3, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(2, presrvgpu);
                  samgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
                 pIcmdlistpre->SetGraphicsRootDescriptorTable(1, samgpu);
                 pIcmdlistpre->RSSetScissorRects(1, &stSMScissorRect);
                 pIcmdlistpre->RSSetViewports(1, &stSMViewPort);
                 pIcmdlistpre->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                 pIcmdlistpre->IASetVertexBuffers(0, 1, &RSMvbv);
                 pIcmdlistpre->IASetIndexBuffer(&RSMibv);
                 pIcmdlistpre->DrawIndexedInstanced(RSMi.size(), 1, 0, 0, 0);
                 pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(RSMwposmap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
                 pIcmdlistpre->Close();

                 
                cmdlists.RemoveAll();

                cmdlists.Add(pIcmdlistpre.Get());
              /*  for (int i = 0;i < MAX_THREAD_NUM;i++)
                    cmdlists.Add(paras[i].cmdlist);
                cmdlists.Add(newparas[0].cmdlist);*/
                pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                n64fence = n64FenceValue;
                n64FenceValue++;
                pICommandQueue->Signal(pIFence.Get(), n64fence);
                pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                HandleMessage->RemoveAll();
                HandleMessage->Add(hFenceEvent);
                nStates = 1;
          
              //  memcpy(passcbmappeddata, &currpasscb, sizeof(passconstant));
              //  //创建cbv
              //  D3D12_CONSTANT_BUFFER_VIEW_DESC cbvdesc = {};
              //  cbvdesc.BufferLocation = pIpassCB->GetGPUVirtualAddress();
              //  cbvdesc.SizeInBytes = (UINT)(sizeof(passconstant) + 255) & ~255;
              //  CD3DX12_CPU_DESCRIPTOR_HANDLE cbvcpuhandle(pISRVHeap->GetCPUDescriptorHandleForHeapStart());
              //  cbvcpuhandle.Offset(2, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //  pID3DDevice->CreateConstantBufferView(&cbvdesc, cbvcpuhandle);




              //  //draw
              //  nFrameIndex = pISwapChain3->GetCurrentBackBufferIndex();
              //  ThrowIfFailed(pICommandAllocator->Reset());
              //  ThrowIfFailed(pICommandList->Reset(pICommandAllocator.Get(), pIskyPSO.Get()));//初始化
              //  pICommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
              //  (pIARenderTargets[nFrameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
              //  pICommandList->RSSetViewports(1, &stViewPort);
              //  pICommandList->RSSetScissorRects(1, &stScissorRect);//
              //  CD3DX12_CPU_DESCRIPTOR_HANDLE stRTVHandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), nFrameIndex, nRTVDescriptorSize);

              //  pICommandList->ClearRenderTargetView(stRTVHandle, Colors::AliceBlue, 0, nullptr);
              //  pICommandList->OMSetRenderTargets(1, &stRTVHandle, FALSE, nullptr);//where

              //  pICommandList->SetGraphicsRootSignature(pIRootSignature.Get());
              //  // pICommandList->SetPipelineState(pIPipelineState.Get());//how
              //  ID3D12DescriptorHeap* heaps[] = { pISRVHeap.Get(),pISamheap.Get() };
              //  pICommandList->SetDescriptorHeaps(2, heaps);
              //  CD3DX12_GPU_DESCRIPTOR_HANDLE samgpu(pISamheap->GetGPUDescriptorHandleForHeapStart());
              //  samgpu.Offset(samplerindex, nSamplerDescriptorSize);
              //  CD3DX12_GPU_DESCRIPTOR_HANDLE heapgpuhandle(pISRVHeap->GetGPUDescriptorHandleForHeapStart());
              //  pICommandList->SetGraphicsRootDescriptorTable(0, heapgpuhandle);
              //  pICommandList->SetGraphicsRootDescriptorTable(1, samgpu);
              //  heapgpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //  pICommandList->SetGraphicsRootDescriptorTable(3, heapgpuhandle);
              //  heapgpuhandle.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //  pICommandList->SetGraphicsRootDescriptorTable(2, heapgpuhandle);
              //  pICommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

              //  //draw sky
              ////必须先画天空球，不然其他的就画不出来,why????
              //  pICommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
              //  pICommandList->IASetVertexBuffers(0, 1, &skyvbv);
              //  pICommandList->IASetIndexBuffer(&skyibv);
              //  pICommandList->DrawIndexedInstanced(mesh12.indices.size(), 1, 0, 0, 0);

              //  //draw cube
              //  pICommandList->SetPipelineState(pIPipelineState.Get());
              //  pICommandList->IASetVertexBuffers(0, 1, &stVertexBufferView);
              //  pICommandList->IASetIndexBuffer(&ibv);
              //  pICommandList->DrawIndexedInstanced(countindex, 1, 0, 0, 0);//what

              //  //draw sphere
              //  pICommandList->IASetVertexBuffers(0, 1, &spherevbv);
              //  pICommandList->IASetIndexBuffer(&sphereibv);
              //  pICommandList->DrawIndexedInstanced(mesh12.indices.size(), 1, 0, 0, 0);




              //  pICommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIARenderTargets[nFrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

              //  ThrowIfFailed(pICommandList->Close());

              //  //执行
              //  ID3D12CommandList* commandlists[] = { pICommandList.Get() };
              //  pICommandQueue->ExecuteCommandLists(_countof(commandlists), commandlists);
              //  ThrowIfFailed(pISwapChain3->Present(1, 0));
              //  // WriteConsole(g_hOutput, L"abc", 4, NULL, NULL);
              //  ThrowIfFailed(pID3DDevice->GetDeviceRemovedReason());

              //  //同步阻塞
              //  const UINT64 currentfenceval = n64FenceValue;
              //  n64FenceValue++;
              //  pICommandQueue->Signal(pIFence.Get(), currentfenceval);
              //  ThrowIfFailed(pIFence->SetEventOnCompletion(currentfenceval, hFenceEvent));
            }
                  break;

            case 1://子线程和gpu都加载完了，现在就剩下让子线程开始绘制
            {
                if (ssaoflag > 0){
                           ThrowIfFailed(pIcmdallssao->Reset());
                           ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));

                }
                ssaoflag++;
                framenum++;
                ThrowIfFailed(pIcmdallpost->Reset());
                ThrowIfFailed(pIcmdlistpost->Reset(pIcmdallpost.Get(), nullptr));
                float x = cos(theta) * sin(phi);
                float z = sin(theta) * sin(phi);
                float y = cos(phi);
                nFrameIndex = pISwapChain3->GetCurrentBackBufferIndex();
             currenttime = ::GetTickCount();
             rotationAngle += (currenttime - starttime) * 0.003f;
             float k = (currenttime - starttime) * 0.001;
             timesecond += k;
             if (timesecond >= 1.25f)
                 timesecond = 0;

             starttime = currenttime;
             XMVECTOR right = XMVector3Cross(up, XMVectorSet(x,y,z,0)) * 10.0f;
             XMVECTOR front;///////////////////////////

             if (GetAsyncKeyState('W') & 0x8000)
             {
                 WriteConsole(g_hOutput, "w", 2, NULL, NULL);
                 eyepos = eyepos + XMVectorSet(x, y, z, 0) * 1.5f;

             }
             if (GetAsyncKeyState('A') & 0x8000)
             {
                 WriteConsole(g_hOutput, "s", 2, NULL, NULL);
                 eyepos = eyepos - right * k;

             }
             if (GetAsyncKeyState('S') & 0x8000)
             {
                 WriteConsole(g_hOutput, "s", 2, NULL, NULL);
                 eyepos = eyepos - XMVectorSet(x, y, z, 0) * 1.5f;
             }
             if (GetAsyncKeyState('D') & 0x8000)
             {
                 WriteConsole(g_hOutput, "d", 2, NULL, NULL);
                 eyepos = eyepos + right * k;

             }
             if (rotationAngle >= XM_2PI)
                 rotationAngle = fmod(rotationAngle, XM_2PI);
           //   XMMATRIX rotmat = XMMatrixRotationY(rotationAngle);
             XMMATRIX rotmat =
                 XMLoadFloat4x4(&MathHelper::Identity4x4());
             XMMATRIX Viewmat = XMMatrixLookAtLH(eyepos,  eyepos+XMVectorSet(x, y, z, 0), up);
             XMMATRIX MVPmat = XMMatrixMultiply(rotmat,Viewmat );
             XMMATRIX projmat = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)1 / (FLOAT)1, 0.1f, 1000.0f);
             MVPmat = XMMatrixMultiply(MVPmat,projmat);
             XMMATRIX transMVPmat = XMMatrixTranspose(MVPmat);
             XMMATRIX World = XMMatrixTranslation(0, 0, 20);
             XMMATRIX vpmat = XMMatrixMultiply(Viewmat, projmat);
             XMStoreFloat4x4(&currpasscb.MVP,  transMVPmat);
             XMStoreFloat3(&currpasscb.eyepos, eyepos);
             XMStoreFloat4x4(&currpasscb.V, XMMatrixTranspose( Viewmat));
             XMStoreFloat4x4(&currpasscb.VP, XMMatrixTranspose( vpmat));
             XMStoreFloat4x4(&currpasscb.uvMAT, XMMatrixTranspose( smuvmat));
         /*    for (int i = 0;i < 58;i++) {
                 XMMATRIX offsetm = XMLoadFloat4x4(&mreader.offsetMatrix[i]);
                 XMStoreFloat4x4(&currpasscb.offsetmat[i], XMMatrixTranspose(offsetm));
             }*/
             currpasscb.lightdir = XMFLOAT3{ 1.0f,1.0f,.0f };
             currpasscb.AL = XMFLOAT3{ 50.5f,50.5f,50.5f };
             currpasscb.BL = XMFLOAT3{ 1.0f,1.0f,1.0f };
             XMStoreFloat4x4(&currpasscb.P, XMMatrixTranspose(projmat));
             currpasscb.randnum = randarr;
             memcpy(SSAOmapped,&currpasscb, sizeof(passconstant));
             objectconstant objc;
             XMMATRIX world = XMMatrixTranslation(0, 0, 20.0f);
             XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
             memcpy(SSAOobjmapped,&objc, sizeof(objectconstant));
             memcpy(SSRobjmapped,&objc, sizeof(objectconstant));
             projmat = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)1 / (FLOAT)1, 0.1f, 1000.0f);
                 XMMATRIX invP = XMMatrixInverse(nullptr, projmat);
                 XMMATRIX invuv = XMMatrixInverse(nullptr, smuvmat);
              vpmat = XMMatrixMultiply(Viewmat, projmat);
              XMStoreFloat4x4(&currpasscb.V, XMMatrixTranspose(Viewmat));
              XMStoreFloat4x4(&currpasscb.VP, XMMatrixTranspose(vpmat));
              XMStoreFloat4x4(&currpasscb.P, XMMatrixTranspose(projmat));
              XMStoreFloat4x4(&currpasscb.invP, XMMatrixTranspose(invP));
              XMStoreFloat4x4(&currpasscb.invuvmat, XMMatrixTranspose(invuv));
          

              D3D12_RANGE range = { 0,0 };
              for (int i = 0;i < 6;i++) {
                  for (int j = 0;j < TexSize;j++) {
                      for (int k = 0;k < TexSize;k++) {
                          for (int l = 0;l < TexSize;l++) {
                              voxelTable[i][j][k][l] = 0;
                          }
                      }
                  }
              }
              //voxeltable
              for (int i = 0;i < RSMv.size();i++) {

                  int indexAndLevel[4];
                  XMVECTOR pos = XMLoadFloat4(&RSMv[i].position);
                  getindex(pos, &indexAndLevel);
                  voxelTable[indexAndLevel[3]][indexAndLevel[0]][indexAndLevel[1]][indexAndLevel[2]] = 1;

              }


              //voxel顶点

              bool isOverlap;
              float voxelSize;
              int level = 0;
              int numvoxel = -1;
              for (int index = 0;index < 36;index++)
                  voxeli.push_back(index);
             UINT ibsize = (UINT)sizeof(std::uint16_t) * (UINT)voxeli.size();
              pID3DDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIvoxelib));
              BYTE* voxelibmap = nullptr;
              ibsize = (UINT)sizeof(std::uint16_t) * (UINT)voxeli.size();
              pIvoxelib->Map(0, &range, reinterpret_cast<void**>(&voxelibmap));
              memcpy(voxelibmap, voxeli.data(), ibsize);
              pIvoxelib->Unmap(0, nullptr);
              voxelibv.BufferLocation = pIvoxelib->GetGPUVirtualAddress();
              voxelibv.Format = DXGI_FORMAT_R16_UINT;
              voxelibv.SizeInBytes = ibsize;
              byte* voxelvbmapped[6];
              voxelInstanceData* voxelInstancedata[6];
              for (int i = 0;i < 6;i++)
                  countVoxelofLevel[i] = 0;
              for (;level < 6;level++) {
                  voxelSize = 1.0f * pow(2, level);
                  int i = 0;
                  int j = 0;
                  int k = 0;
                  voxelv.clear();
                  voxelVertex v;//左右前后上下
                  v.center = XMFLOAT3{ 0,0,0 };
                  numvoxel++;
                  v.position = XMFLOAT4{ j * voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ -1.0f,0,0 };

                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ j * voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ -1.0f,0,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ j * voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ -1.0f,0,0 };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ j * voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ -1.0f,0,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ j * voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ -1.0f,0,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ j * voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ -1.0f,0,0 };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 1.0f,0,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 1.0f,0,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 1.0f,0,0 };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 1.0f,0,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 1.0f,0,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 1.0f,0,0 };
                  voxelv.push_back(v);


                  v.position = XMFLOAT4{ (j)*voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,-1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,-1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j)*voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,-1.0f };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j)*voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,-1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,-1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,-1.0f };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j)*voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,1.0f };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j)*voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,1.0f };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j)*voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,0,1.0f };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j)*voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j)*voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,1.0f,0 };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j)*voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i + 1) * voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,1.0f,0 };
                  voxelv.push_back(v);


                  v.position = XMFLOAT4{ (j)*voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,-1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,-1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j)*voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,-1.0f,0 };
                  voxelv.push_back(v);

                  v.position = XMFLOAT4{ (j)*voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,-1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k)*voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,-1.0f,0 };
                  voxelv.push_back(v);
                  v.position = XMFLOAT4{ (j + 1) * voxelSize,(i)*voxelSize,(k + 1) * voxelSize,1.0f };
                  v.normal = XMFLOAT3{ 0,-1.0f,0 };
                  voxelv.push_back(v);
                  UINT vbsize = (UINT)sizeof(voxelVertex) * (UINT)voxelv.size();


                  pIvoxelvb[level]->Map(0, &range, reinterpret_cast<void**>(&voxelvbmapped[level]));
                  memcpy(voxelvbmapped[level], voxelv.data(), vbsize);

                  voxelvbv[level][0].BufferLocation = pIvoxelvb[level]->GetGPUVirtualAddress();
                  voxelvbv[level][0].SizeInBytes = vbsize;
                  voxelvbv[level][0].StrideInBytes = sizeof(voxelVertex);
                  pIvoxelvb[level]->Unmap(0, nullptr);

                  for (int i = 0;i < 6;i++)
                      voxelInstancedata[i] = nullptr;
                  pIvoxelInstanceBuffer[level]->Map(0, &range, reinterpret_cast<void**>(&(voxelInstancedata[level])));
                  for (int x = 0;x < TexSize;x++) {
                      for (int y = 0;y < TexSize;y++) {
                          for (int z = 0;z < TexSize;z++) {
                              if (voxelTable[level][x][y][z] == 1) {
                                  countVoxelofLevel[level]++;
                                  XMMATRIX w = XMMatrixTranslation((x - TexSize / 2) * voxelSize, (y - TexSize / 2) * voxelSize, (z - TexSize / 2) * voxelSize);
                                  XMMATRIX toEye = XMMatrixTranslation(XMVectorGetX(eyepos), XMVectorGetY(eyepos), XMVectorGetZ(eyepos));
                                  XMMATRIX wtoeye = XMMatrixMultiply(w, toEye);
                                  XMStoreFloat4x4(&((voxelInstancedata[level])[countVoxelofLevel[level]].world), XMMatrixTranspose(wtoeye));
                              }
                          }
                      }
                  }
                  vbsize = (UINT)sizeof(voxelInstanceData) * (UINT)countVoxelofLevel[level];

                  /*    int it = 0;
                      for (int x = -10;x < 10;x++) {
                          for (int y = -10;y < 10;y++) {
                              for (int z = -10;z < 10;z++) {
                                  XMMATRIX w = XMMatrixTranslation((x+0.5f)*voxelSize,(y+0.5f)*voxelSize,(z+0.5f)*voxelSize);;
                                  XMStoreFloat4x4(&((voxelInstancedata[level])[it].world), XMMatrixTranspose(w));
                                  it++;
                              }
                          }
                      }*/

                  voxelvbv[level][1].BufferLocation = pIvoxelInstanceBuffer[level]->GetGPUVirtualAddress();
                  voxelvbv[level][1].SizeInBytes = vbsize;
                  voxelvbv[level][1].StrideInBytes = sizeof(voxelInstanceData);
                  pIvoxelInstanceBuffer[level]->Unmap(0, nullptr);
              }
             //viewDepth渲染
             CD3DX12_CPU_DESCRIPTOR_HANDLE dsvhandle(pIDSVHeap->GetCPUDescriptorHandleForHeapStart(),2,pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV));
             pIcmdlistssao->SetPipelineState(pIviewDepthPSO.Get());
             pIcmdlistssao->SetGraphicsRootSignature(pIRootSignature.Get());
             pIcmdlistssao->ClearDepthStencilView(dsvhandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
             pIcmdlistssao->OMSetRenderTargets(0,nullptr , FALSE,&dsvhandle );
             pIcmdlistssao->RSSetViewports(1, &stViewPort);
             pIcmdlistssao->RSSetScissorRects(1, &stScissorRect);//
                 ID3D12DescriptorHeap* heapsssao[] = {  pIpresrvheap.Get(),pIpresamheap.Get()};
          pIcmdlistssao->SetDescriptorHeaps(2, heapsssao);
          CD3DX12_GPU_DESCRIPTOR_HANDLE ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
          pIcmdlistssao->SetGraphicsRootDescriptorTable(2, ssaogpu);
         ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
         pIcmdlistssao->SetGraphicsRootDescriptorTable(5, ssaogpu);
         ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
         ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
         pIcmdlistssao->SetGraphicsRootDescriptorTable(1, ssaogpu);
             pIcmdlistssao->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
             pIcmdlistssao->IASetVertexBuffers(0, 1, &ssaovbv);
             pIcmdlistssao->IASetIndexBuffer(&ssaoibv);
             pIcmdlistssao->DrawIndexedInstanced(mreader.mindices.size(), 1, 0, 0, 0);
             //pIcmdlistssao->IASetVertexBuffers(0, 1, &ballvbv);
             //pIcmdlistssao->IASetIndexBuffer(&ballibv);
             //pIcmdlistssao->DrawIndexedInstanced(mesh12.indices.size(), 1, 0, 0, 0);
             pIcmdlistssao->Close();
             cmdlists.RemoveAll();
             cmdlists.Add(pIcmdlistssao.Get());
             pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
             n64fence = n64FenceValue;
             n64FenceValue++;
             pICommandQueue->Signal(pIFence.Get(), n64fence);
             pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

             ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);
             ThrowIfFailed(pIcmdallssao->Reset());
             ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));

             //创建viewdepth的SRV
             CD3DX12_CPU_DESCRIPTOR_HANDLE depthmapSRV(pIpresrvheap->GetCPUDescriptorHandleForHeapStart(), 12,pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
             D3D12_SHADER_RESOURCE_VIEW_DESC depthmapsrvdesc = {};
             depthmapsrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
             depthmapsrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
             depthmapsrvdesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
             depthmapsrvdesc.Texture2D.MostDetailedMip = 0;
             depthmapsrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
             depthmapsrvdesc.Texture2D.MipLevels = SSAOdepthmap->GetDesc().MipLevels;
             pID3DDevice->CreateShaderResourceView(SSAOdepthmap.Get(), &depthmapsrvdesc, depthmapSRV);
             //SSAO渲染
             CD3DX12_CPU_DESCRIPTOR_HANDLE ssaoRTVhandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 43, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
              dsvhandle=CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
             //pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSAOmap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
             if (ssaoflag ==1) {
                 pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSAOmap.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_RENDER_TARGET));
         }
             pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSAOdepthmap.Get(),D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ));
             pIcmdlistssao->ClearRenderTargetView(ssaoRTVhandle, Colors::AliceBlue, 0, nullptr);
             pIcmdlistssao->ClearDepthStencilView(dsvhandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
              ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
             pIcmdlistssao->SetPipelineState(pISSAOPSO.Get());
             pIcmdlistssao->SetGraphicsRootSignature(pIRootSignature.Get());
             pIcmdlistssao->OMSetRenderTargets(1, &ssaoRTVhandle, FALSE, &dsvhandle);
             pIcmdlistssao->RSSetViewports(1, &stViewPort);
             pIcmdlistssao->RSSetScissorRects(1, &stScissorRect);//
             ID3D12DescriptorHeap* heapsssaos[] = {  pIpresrvheap.Get(),pIpresamheap.Get()};
             pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
             pIcmdlistssao->SetGraphicsRootDescriptorTable(2, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(5, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(6, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            pIcmdlistssao->SetGraphicsRootDescriptorTable(1, ssaogpu);
            pIcmdlistssao->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            pIcmdlistssao->IASetVertexBuffers(0, 1, &ssaovbv);
            pIcmdlistssao->IASetIndexBuffer(&ssaoibv);
            pIcmdlistssao->DrawIndexedInstanced(mreader.mindices.size(), 1, 0, 0, 0);
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSAOmap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);

            //SSDODL渲染
            ThrowIfFailed(pIcmdallssao->Reset());
            ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
             ssaoRTVhandle=CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 47, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            dsvhandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
                pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSDOdirectLightmap.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_RENDER_TARGET));
      
            pIcmdlistssao->ClearRenderTargetView(ssaoRTVhandle, Colors::Black, 0, nullptr);
            pIcmdlistssao->ClearDepthStencilView(dsvhandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetPipelineState(pISSDOdirectLPSO.Get());
            pIcmdlistssao->SetGraphicsRootSignature(pIRootSignature.Get());
            pIcmdlistssao->OMSetRenderTargets(1, &ssaoRTVhandle, FALSE, &dsvhandle);
            pIcmdlistssao->RSSetViewports(1, &stViewPort);
            pIcmdlistssao->RSSetScissorRects(1, &stScissorRect);//
            pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            pIcmdlistssao->SetGraphicsRootDescriptorTable(2, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(5, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(6, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 17, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(0, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(4, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            pIcmdlistssao->SetGraphicsRootDescriptorTable(1, ssaogpu);
            pIcmdlistssao->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            pIcmdlistssao->IASetVertexBuffers(0, 1, &RSMvbv);
            pIcmdlistssao->IASetIndexBuffer(&RSMibv);
            pIcmdlistssao->DrawIndexedInstanced(RSMi.size(), 1, 0, 0, 0);
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSDOdirectLightmap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);

            //SSDOnormalmap渲染
            ThrowIfFailed(pIcmdallssao->Reset());
            ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
            ssaoRTVhandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 48, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            dsvhandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSDOnormalmap.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_RENDER_TARGET));

            pIcmdlistssao->ClearRenderTargetView(ssaoRTVhandle, Colors::AliceBlue, 0, nullptr);
            pIcmdlistssao->ClearDepthStencilView(dsvhandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetPipelineState(pISSDOnormalPSO.Get());
            pIcmdlistssao->SetGraphicsRootSignature(pIRootSignature.Get());
            pIcmdlistssao->OMSetRenderTargets(1, &ssaoRTVhandle, FALSE, &dsvhandle);
            pIcmdlistssao->RSSetViewports(1, &stViewPort);
            pIcmdlistssao->RSSetScissorRects(1, &stScissorRect);//
            pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            pIcmdlistssao->SetGraphicsRootDescriptorTable(2, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(5, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(6, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 17, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(0, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(4, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            pIcmdlistssao->SetGraphicsRootDescriptorTable(1, ssaogpu);
            pIcmdlistssao->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            pIcmdlistssao->IASetVertexBuffers(0, 1, &RSMvbv);
            pIcmdlistssao->IASetIndexBuffer(&RSMibv);
            pIcmdlistssao->DrawIndexedInstanced(RSMi.size(), 1, 0, 0, 0);
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(SSDOnormalmap.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);

            //SSRlastframecolor渲染
            ThrowIfFailed(pIcmdallssao->Reset());
            ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
            ssaoRTVhandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 51, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            dsvhandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(colorBuffer.Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));

            pIcmdlistssao->ClearRenderTargetView(ssaoRTVhandle, Colors::Black, 0, nullptr);
            pIcmdlistssao->ClearDepthStencilView(dsvhandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetPipelineState(pISSRcolorBufferPSO.Get());
            pIcmdlistssao->SetGraphicsRootSignature(pIRootSignature.Get());
            pIcmdlistssao->OMSetRenderTargets(1, &ssaoRTVhandle, FALSE, &dsvhandle);
            pIcmdlistssao->RSSetViewports(1, &stViewPort);
            pIcmdlistssao->RSSetScissorRects(1, &stScissorRect);
            pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            pIcmdlistssao->SetGraphicsRootDescriptorTable(2, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 19, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(5, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 11, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(6, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 17, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(0, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(4, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            pIcmdlistssao->SetGraphicsRootDescriptorTable(1, ssaogpu);
            pIcmdlistssao->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            pIcmdlistssao->IASetVertexBuffers(0, 1, &RSMvbv);
            pIcmdlistssao->IASetIndexBuffer(&RSMibv);

            int istarr[5] = { 0 + 12,7230 * 3 + 12,11679 * 3 + 12,18258 * 3 + 12,22065 * 3 + 12 };
            int vstarr[5] = { 0,3915,6899,11169,13474 };
            UINT vsizearr[5] = { 3915,2984,4270,2305,274 };
            UINT isizearr[5] = { 7230 * 3 ,4449 * 3 ,6579 * 3 ,3807 * 3 ,442 * 3 };
            for (int i = 0;i < 4;i++) {

                CD3DX12_GPU_DESCRIPTOR_HANDLE  srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 12 + i, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistssao->SetGraphicsRootDescriptorTable(0, srvgpu);


                pIcmdlistssao->DrawIndexedInstanced(isizearr[i], 1, istarr[i], 0, 0);//index是总体vertex的index，所以第四个参数为0;

            }
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 17, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(0, ssaogpu);
            pIcmdlistssao->DrawIndexedInstanced(12, 1,0, 0, 0);
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(colorBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);


            //3Dclear

            ThrowIfFailed(pIcmdallssao->Reset());
            ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
            pIcmdlistssao->SetComputeRootSignature(pICSRootSignature.Get());
            pIcmdlistssao->SetPipelineState(pI3DClearPSO.Get());
            pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            for (int i = 0;i < 6;i++) {
                pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(clipMapArray[i].Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
                pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(clipMapNormalArray[i].Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));

            }     pIcmdlistssao->SetComputeRootDescriptorTable(2, ssaogpu);

            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 46, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(0, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 52, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 43, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(4, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 44, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(5, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 45, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(6, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 53, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(7, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 54, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(8, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 55, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(9, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 56, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(10, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 57, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(11, ssaogpu);
            pIcmdlistssao->Dispatch(TexSize/2, TexSize/2, TexSize/2);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114+8, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(7, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114+2*8, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(8, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114 + 3 * 8, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(9, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114 + 4 * 8, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(10, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114 + 5 * 8, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(11, ssaogpu);
            pIcmdlistssao->Dispatch(TexSize / 2, TexSize / 2, TexSize / 2);
            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);

            //voxelization
            ThrowIfFailed(pIcmdallssao->Reset());
            ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
            //for(int i=0;i<6;i++)
            //pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(clipMapArray[i].Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));

            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetPipelineState(pIVoxelizationPSO.Get());
            pIcmdlistssao->SetGraphicsRootSignature(pIRootSignature.Get());
            pIcmdlistssao->OMSetRenderTargets(0, nullptr, FALSE, nullptr);
            pIcmdlistssao->RSSetViewports(1, &stViewPort);
            pIcmdlistssao->RSSetScissorRects(1, &stScissorRect);//
            pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            pIcmdlistssao->SetGraphicsRootDescriptorTable(2, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(5, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(6, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 17, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(0, ssaogpu);
            ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(4, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 52, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetGraphicsRootDescriptorTable(23, ssaogpu);
            for (int i = 0;i < 5;i++) {
                ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistssao->SetGraphicsRootDescriptorTable(24+i, ssaogpu);
            }
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            pIcmdlistssao->SetGraphicsRootDescriptorTable(1, ssaogpu);
            pIcmdlistssao->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            pIcmdlistssao->IASetVertexBuffers(0, 1, &RSMvbv);
            pIcmdlistssao->IASetIndexBuffer(&RSMibv);
            //int istarr[5] = { 0 + 12,7230 * 3 + 12,11679 * 3 + 12,18258 * 3 + 12,22065 * 3 + 12 };
            //int vstarr[5] = { 0,3915,6899,11169,13474 };
            //UINT vsizearr[5] = { 3915,2984,4270,2305,274 };
            //UINT isizearr[5] = { 7230 * 3 ,4449 * 3 ,6579 * 3 ,3807 * 3 ,442 * 3 };
            for (int i = 0;i < 4;i++) {

                CD3DX12_GPU_DESCRIPTOR_HANDLE  srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 12 + i, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistssao->SetGraphicsRootDescriptorTable(0, srvgpu);


                pIcmdlistssao->DrawIndexedInstanced(isizearr[i], 1, istarr[i], 0, 0);//index是总体vertex的index，所以第四个参数为0;

            }
        
            for (int i = 0;i < 6;i++) {
                ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114+i*8, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistssao->SetGraphicsRootDescriptorTable(23 + i, ssaogpu);
            }
            pIcmdlistssao->SetPipelineState(pIVoxelizationNormalPSO.Get());
            pIcmdlistssao->DrawIndexedInstanced(RSMi.size(), 1, 0, 0, 0);//index是总体vertex的index，所以第四个参数为0;

            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);
            //clipmap_miplevel创建
            ThrowIfFailed(pIcmdallssao->Reset());
            ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
            pIcmdlistssao->SetComputeRootSignature(pICSRootSignature.Get());
            pIcmdlistssao->SetPipelineState(pIclip_levelPSO.Get());
            pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            pIcmdlistssao->SetComputeRootDescriptorTable(2, ssaogpu);

            for (int mip = 1;mip < 8;mip++)
            {
                Hizmipsdata md;
                md.lastMiplevel = mip - 1;
                memcpy(Hizmipsmap[mip], &md, sizeof(Hizmipsdata));
            }
            for (int level = 0;level < 6;level++) {
                ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 58+level, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistssao->SetComputeRootDescriptorTable(0, ssaogpu);
         
                for (int mip = 1;mip < 8;mip++) {
          
                    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 106+mip, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    pIcmdlistssao->SetComputeRootDescriptorTable(3, ssaogpu);
                    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 64 + level * 7+mip-1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
                    int numgroups = 128 / pow(2, level)/8;
                    pIcmdlistssao->Dispatch(numgroups, numgroups, numgroups);
                }
            }
            for (int level = 0;level < 6;level++) {
                ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 162 + level, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                pIcmdlistssao->SetComputeRootDescriptorTable(0, ssaogpu);

                for (int mip = 1;mip < 8;mip++) {

                    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 106 + mip, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    pIcmdlistssao->SetComputeRootDescriptorTable(3, ssaogpu);
                    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 114 + level * 8 + mip, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
                    int numgroups = 128 / pow(2, level) / 8;
                    pIcmdlistssao->Dispatch(numgroups, numgroups, numgroups);
                }
            }
            for (int i = 0;i < 6;i++) {
                pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(clipMapArray[i].Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));
                pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(clipMapNormalArray[i].Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));

            }
            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);

            ////Hi_zmipmap构建
            //ThrowIfFailed(pIcmdallssao->Reset());
            //ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
            //pIcmdlistssao->SetComputeRootSignature(pICSRootSignature.Get());
            //pIcmdlistssao->SetPipelineState(pIHi_zcopyPSO.Get());
            //pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            //ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
            //pIcmdlistssao->SetComputeRootDescriptorTable(2, ssaogpu);
            //pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(Hi_zMipmap.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
            //ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 12, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //pIcmdlistssao->SetComputeRootDescriptorTable(0, ssaogpu);
            //ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 31, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
            //UINT numgroups = (UINT)ceilf(iWidth  / 8.0f);
            //pIcmdlistssao->Dispatch(numgroups, numgroups, 1);
            //pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::UAV(Hi_zMipmap.Get()));
            //pIcmdlistssao->SetPipelineState(pIHi_zcomputePSO.Get());
            //for (int i = 0;i < 10;i++) {
            //    Hizmipsdata md;
            //    md.lastMiplevel =i;
            //    memcpy(Hizmipsmap, &md, sizeof(Hizmipsdata));
            //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 42, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    pIcmdlistssao->SetComputeRootDescriptorTable(3, ssaogpu);
            //
            //        ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 20+i, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //        pIcmdlistssao->SetComputeRootDescriptorTable(0, ssaogpu);
            //    
            //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 31+i+1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
            //    UINT numgroups = (UINT)ceilf(iWidth/pow(2,i+1) / 8.0f);
            //    pIcmdlistssao->Dispatch(numgroups, numgroups, 1);
            //    pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::UAV(Hi_zMipmap.Get()));
            //}
            //pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(Hi_zMipmap.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));
            //pIcmdlistssao->Close();
            //cmdlists.RemoveAll();
            //cmdlists.Add(pIcmdlistssao.Get());
            //pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            //n64fence = n64FenceValue;
            //n64FenceValue++;
            //pICommandQueue->Signal(pIFence.Get(), n64fence);
            //pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            //::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);

         



            //LPVinject
        //    ThrowIfFailed(pIcmdallssao->Reset());
        //    ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
        //    pIcmdlistssao->SetComputeRootSignature(pICSRootSignature.Get());
        //    pIcmdlistssao->SetPipelineState(pILPVinjectPSO.Get());
        //    pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
        //    pIcmdlistssao->SetComputeRootDescriptorTable(2, ssaogpu);
        ///*    pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
        //    pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex2.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));
        //    pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex3.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));*/
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 12, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //    pIcmdlistssao->SetComputeRootDescriptorTable(0, ssaogpu);
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 46, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //    pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 43, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //    pIcmdlistssao->SetComputeRootDescriptorTable(4, ssaogpu);
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 44, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //    pIcmdlistssao->SetComputeRootDescriptorTable(5, ssaogpu);
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 45, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //    pIcmdlistssao->SetComputeRootDescriptorTable(6, ssaogpu);
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 47, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //    pIcmdlistssao->SetComputeRootDescriptorTable(7, ssaogpu);
        //    ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 48, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        //    pIcmdlistssao->SetComputeRootDescriptorTable(8, ssaogpu);
        //    pIcmdlistssao->Dispatch(256, 206, 1);
        ///*    pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));
        //    pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex2.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));
        //    pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex3.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));*/
        //    pIcmdlistssao->Close();
        //    cmdlists.RemoveAll();
        //    cmdlists.Add(pIcmdlistssao.Get());
        //    pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
        //    n64fence = n64FenceValue;
        //    n64FenceValue++;
        //    pICommandQueue->Signal(pIFence.Get(), n64fence);
        //    pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

        //    ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);


          //LPVpropagation
   /*         ThrowIfFailed(pIcmdallssao->Reset());
            ThrowIfFailed(pIcmdlistssao->Reset(pIcmdallssao.Get(), nullptr));
            pIcmdlistssao->SetComputeRootSignature(pICSRootSignature.Get());
            pIcmdlistssao->SetPipelineState(pILPVpropagationPSO.Get());
            pIcmdlistssao->SetDescriptorHeaps(2, heapsssaos);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart());
            pIcmdlistssao->SetComputeRootDescriptorTable(2, ssaogpu);

            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 12, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(0, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 46, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(1, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 43, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(4, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 44, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(5, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 45, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(6, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 47, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(7, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 48, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(8, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 49, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(9, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 50, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(10, ssaogpu);
            ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 51, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            pIcmdlistssao->SetComputeRootDescriptorTable(11, ssaogpu);*/
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
     /*       pIcmdlistssao->Dispatch(10, 10, 10);
            pIcmdlistssao->Dispatch(10, 10, 10);
            pIcmdlistssao->Dispatch(10, 10, 10);*/
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);
            //pIcmdlistssao->Dispatch(10, 10, 10);

  /*          pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex2.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));
            pIcmdlistssao->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(LPVvoxelTex3.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ));
            pIcmdlistssao->Close();
            cmdlists.RemoveAll();
            cmdlists.Add(pIcmdlistssao.Get());
            pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
            n64fence = n64FenceValue;
            n64FenceValue++;
            pICommandQueue->Signal(pIFence.Get(), n64fence);
            pIFence->SetEventOnCompletion(n64fence, hFenceEvent);

            ::MsgWaitForMultipleObjects(1, &hFenceEvent, TRUE, INFINITE, QS_ALLINPUT);*/




             ThrowIfFailed(pIcmdallpre->Reset());
             ThrowIfFailed(pIcmdlistpre->Reset(pIcmdallpre.Get(), nullptr));
               pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
            (pIARenderTargets[nFrameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
               pIcmdlistpre->RSSetViewports(1, &stViewPort);
               pIcmdlistpre->RSSetScissorRects(1, &stScissorRect);//
               CD3DX12_CPU_DESCRIPTOR_HANDLE stRTVHandle=CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), nFrameIndex, nRTVDescriptorSize);
               CD3DX12_CPU_DESCRIPTOR_HANDLE lastframeRTV;
               CD3DX12_CPU_DESCRIPTOR_HANDLE stDSVHandle(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
          
     /*          if (framenum == 1) {
                   pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                   (lastframebuffer[0].Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                   lastframeRTV = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 49, nRTVDescriptorSize);
               }
               else {
                   if (framenum % 2 == 0) {
                      
                       lastframeRTV=CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 50, nRTVDescriptorSize);
                       pIcmdlistpre->ClearRenderTargetView(lastframeRTV, Colors::Red, 0, nullptr);
                       pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                       (lastframebuffer[0].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
                       pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                       (lastframebuffer[1].Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                   }
                   else {
                       
                       lastframeRTV = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 49, nRTVDescriptorSize);
                       pIcmdlistpre->ClearRenderTargetView(lastframeRTV, Colors::Blue, 0, nullptr);
                       pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                       (lastframebuffer[1].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
                       pIcmdlistpre->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                       (lastframebuffer[0].Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
                   }
               }*/
               //CD3DX12_CPU_DESCRIPTOR_HANDLE desarr[2] = { stRTVHandle,lastframeRTV };

            pIcmdlistpre->ClearRenderTargetView(stRTVHandle, Colors::AliceBlue, 0, nullptr);

            pIcmdlistpre->ClearDepthStencilView(stDSVHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
            //pIcmdlistpre->OMSetRenderTargets(2, &desarr[0], FALSE, &dsvhandle);//where

            nStates = 2;
            HandleMessage->RemoveAll();
            for (int i = 0;i < MAX_THREAD_NUM;i++)
                HandleMessage->Add(paras[i].hEventRenderOver);
            HandleMessage->Add(newparas[0].hEventRenderOver);
            for (int i = 0;i < MAX_THREAD_NUM;i++) {//每一帧都变化的数据
                paras[i].passc = currpasscb;
                paras[i].nCurrentFrameIndex = pISwapChain3->GetCurrentBackBufferIndex();
                SetEvent(paras[i].hRunEvent);
            }
            newparas[0].passc = currpasscb;
            newparas[0].nCurrentFrameIndex = pISwapChain3->GetCurrentBackBufferIndex();
            SetEvent(newparas[0].hRunEvent);
         
            }
            break;
            case 2:{
                //draw示例小球
                //CD3DX12_CPU_DESCRIPTOR_HANDLE stRTVHandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), nFrameIndex, nRTVDescriptorSize);
                //CD3DX12_CPU_DESCRIPTOR_HANDLE DSVhandle(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
                //pIcmdlistpost->SetGraphicsRootSignature(pIRootSignature.Get());
                //pIcmdlistpost->OMSetRenderTargets(1, &stRTVHandle, FALSE, &DSVhandle);//where
    
                //pIcmdlistpost->SetPipelineState(pImultiInstancePSO.Get());
  
                //pIcmdlistpost->RSSetViewports(1, &stViewPort);
                //pIcmdlistpost->RSSetScissorRects(1, &stScissorRect);//
                //ID3D12DescriptorHeap* heapsssao[] = { pIpresrvheap.Get(),pIpresamheap.Get() };
                //pIcmdlistpost->SetDescriptorHeaps(2, heapsssao);

                //CD3DX12_GPU_DESCRIPTOR_HANDLE  ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                //pIcmdlistpost->SetGraphicsRootDescriptorTable(2, ssaogpu);
                //ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
                //pIcmdlistpost->SetGraphicsRootDescriptorTable(1, ssaogpu);
                //ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 46, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                //pIcmdlistpost->SetGraphicsRootDescriptorTable(13, ssaogpu);
                //ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 47, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                //pIcmdlistpost->SetGraphicsRootDescriptorTable(14, ssaogpu);
                //ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 48, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                //pIcmdlistpost->SetGraphicsRootDescriptorTable(15, ssaogpu);
                //pIcmdlistpost->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                //pIcmdlistpost->IASetVertexBuffers(0, 2, multivbv);
                //pIcmdlistpost->IASetIndexBuffer(&multiibv[0]);
                //pIcmdlistpost->DrawIndexedInstanced(mesh12.indices.size(), 1000, 0, 0, 0);

                      //drawvoxel

              //  CD3DX12_CPU_DESCRIPTOR_HANDLE stRTVHandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), nFrameIndex, nRTVDescriptorSize);
              //  CD3DX12_CPU_DESCRIPTOR_HANDLE DSVhandle(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
              //  pIcmdlistpost->SetGraphicsRootSignature(pIRootSignature.Get());
              //  pIcmdlistpost->OMSetRenderTargets(1, &stRTVHandle, FALSE, &DSVhandle);//where

              //  pIcmdlistpost->SetPipelineState(pIvoxelvisualizePSO.Get());

              //  pIcmdlistpost->RSSetViewports(1, &stViewPort);
              //  pIcmdlistpost->RSSetScissorRects(1, &stScissorRect);//
              //  ID3D12DescriptorHeap* heapsssao[] = { pIpresrvheap.Get(),pIpresamheap.Get() };
              //  pIcmdlistpost->SetDescriptorHeaps(2, heapsssao);

              //CD3DX12_GPU_DESCRIPTOR_HANDLE  ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 10, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //pIcmdlistpost->SetGraphicsRootDescriptorTable(2, ssaogpu);
              //  ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresamheap->GetGPUDescriptorHandleForHeapStart());
              //  pIcmdlistpost->SetGraphicsRootDescriptorTable(1, ssaogpu);
              //  ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 46, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //  pIcmdlistpost->SetGraphicsRootDescriptorTable(13, ssaogpu);
              //  ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 47, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //  pIcmdlistpost->SetGraphicsRootDescriptorTable(14, ssaogpu);
              //  ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 48, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //  pIcmdlistpost->SetGraphicsRootDescriptorTable(15, ssaogpu);
              //  ssaogpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pIpresrvheap->GetGPUDescriptorHandleForHeapStart(), 51, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //  for (int i = 0;i < 6;i++) {
              //      ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //      pIcmdlistpost->SetGraphicsRootDescriptorTable(23 + i, ssaogpu);
              //  }
              //  for (int i = 0;i < 6;i++) {
              //      ssaogpu.Offset(1, pID3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              //      pIcmdlistpost->SetGraphicsRootDescriptorTable(29 + i, ssaogpu);
              //  }
              //  pIcmdlistpost->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
              //  pIcmdlistpost->IASetVertexBuffers(0, 1, &voxelvbv);
              //  pIcmdlistpost->IASetIndexBuffer(&voxelibv);
              //  pIcmdlistpost->DrawIndexedInstanced(voxeli.size(), 1, 0, 0, 0);
        

                pIcmdlistpost->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                (lastframebuffer[0].Get(), D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COPY_DEST));
                
                pIcmdlistpost->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                (pIARenderTargets[nFrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_COPY_SOURCE));
                pIcmdlistpost->CopyResource(lastframebuffer[0].Get(), pIARenderTargets[nFrameIndex].Get());
                pIcmdlistpost->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                (lastframebuffer[0].Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));
                pIcmdlistpost->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                (colorBuffer.Get(), D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET));
                pIcmdlistpost->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition
                (pIARenderTargets[nFrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

                pIcmdlistpre->Close();
                pIcmdlistpost->Close();
                cmdlists.RemoveAll();
                cmdlists.Add(pIcmdlistpre.Get());
                for (int i = 0;i < MAX_THREAD_NUM;i++) {
                    cmdlists.Add(paras[i].cmdlist);
                }
                cmdlists.Add(newparas[0].cmdlist);
                cmdlists.Add(pIcmdlistpost.Get());
                pICommandQueue->ExecuteCommandLists(cmdlists.GetCount(), cmdlists.GetData());
                ThrowIfFailed(pISwapChain3->Present(1, 0));
                n64fence = n64FenceValue;
                n64FenceValue++;
                pICommandQueue->Signal(pIFence.Get(), n64fence);
                pIFence->SetEventOnCompletion(n64fence, hFenceEvent);
                nStates = 1;
                HandleMessage->RemoveAll();
                HandleMessage->Add(hFenceEvent);
                
            } break;
            default:
                break;
            }
        }
       
           
           
    }
    }
    }
    
    catch (DxException& e)
    {//发生了COM异常

        WriteConsole(g_hOutput, e.ToString().c_str(), e.ToString().size(), NULL, NULL);
        while (1);
    }
    return 0;

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYUP:
    {
        if (VK_SPACE == (wParam & 0xFF)) {
            samplerindex++;
            WriteConsole(g_hOutput, L"1", 2, NULL, NULL);
            if (samplerindex == samplercount)
                samplerindex = 0;
        }

    }break;
    case WM_LBUTTONDOWN:
  
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN: {
        OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

    }break;
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
       
        
    case WM_MOUSEMOVE: {
        OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    }break;
      
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
UINT __stdcall threadfunc(void* ppara) {
    threadparas* para = reinterpret_cast<threadparas*>(ppara);
    ComPtr<ID3D12Resource>				pITexture;
    ComPtr<ID3D12Resource>				pITexturehead;
    ComPtr<ID3D12Resource>				pITexturejacket;
    ComPtr<ID3D12Resource>				pITexturepants;
    ComPtr<ID3D12Resource>				pITextureupbody;


    ComPtr<ID3D12Resource>				pITexturenmap;
    ComPtr<ID3D12Resource>				pITexturenmaphead;
    ComPtr<ID3D12Resource>				pITexturenmapjacket;
    ComPtr<ID3D12Resource>				pITexturenmappants;
    ComPtr<ID3D12Resource>				pITexturenmapupbody;

    ComPtr<ID3D12Resource>				pITextureUpload;
    ComPtr<ID3D12Resource>				pITextureUploadhead;
    ComPtr<ID3D12Resource>				pITextureUploadjacket;
    ComPtr<ID3D12Resource>				pITextureUploadpants;
    ComPtr<ID3D12Resource>				pITextureUploadupbody;

    ComPtr<ID3D12Resource>				pITexturenmapUpload;
    ComPtr<ID3D12Resource>				pITexturenmapUploadhead;
    ComPtr<ID3D12Resource>				pITexturenmapUploadjacket;
    ComPtr<ID3D12Resource>				pITexturenmapUploadpants;
    ComPtr<ID3D12Resource>				pITexturenmapUploadupbody;

    ComPtr<ID3D12Resource>				pITexturecube;
    ComPtr<ID3D12Resource>				pITexturecubeUpload;
    ComPtr<ID3D12Resource>				pIVB[5];
    ComPtr<ID3D12Resource>				pIIB[5];
    ComPtr<ID3D12Resource>			    pICBWVP;
    ComPtr<ID3D12Resource>			    pIobjCB;
    ComPtr<ID3D12Resource>			    pImatsCB;
    ComPtr<ID3D12DescriptorHeap>		pISRVCBVHp;
    ComPtr<ID3D12DescriptorHeap>		pISampleHp;
    D3D12_VERTEX_BUFFER_VIEW			stVBV[5] = {};
    D3D12_INDEX_BUFFER_VIEW				stIBV[5] = {};
    std::vector<XMFLOAT4X4>               finaltrans;
    UINT8* mapib = nullptr;UINT8* mapvb = nullptr;
    UINT vbsize;
    UINT ibsize;
    //加载纹理
    try {
       ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, para->pszDDSFile, pITexture, pITextureUpload));

       ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\head_diff.dds", pITexturehead, pITextureUploadhead));
       ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\jacket_diff.dds", pITexturejacket, pITextureUploadjacket));
       ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\pants_diff.dds", pITexturepants, pITextureUploadpants));
       ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\upBody_diff.dds", pITextureupbody, pITextureUploadupbody));


        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\default_nmap.dds", pITexturenmap, pITexturenmapUpload));
        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\head_norm.dds", pITexturenmaphead, pITexturenmapUploadhead));
        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\jacket_norm.dds", pITexturenmapjacket, pITexturenmapUploadjacket));
        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\pants_norm.dds", pITexturenmappants, pITexturenmapUploadpants));
        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\upbody_norm.dds", pITexturenmapupbody, pITexturenmapUploadupbody));



        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\sunsetcube1024.dds", pITexturecube, pITexturecubeUpload));
        
    }
    catch (DxException& e) {
        WriteConsole(g_hOutput, e.ToString().c_str(), e.ToString().size(), NULL, NULL);
        while (1);
    }
   
    //创建描述符堆
    D3D12_DESCRIPTOR_HEAP_DESC srvheapdesc = {};
    srvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvheapdesc.NumDescriptors = 55;
    srvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    para->device->CreateDescriptorHeap(&srvheapdesc, IID_PPV_ARGS(&pISRVCBVHp));
    D3D12_DESCRIPTOR_HEAP_DESC samheapdesc = {};
    samheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
    samheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    samheapdesc.NumDescriptors = 1;
    para->device->CreateDescriptorHeap(&samheapdesc, IID_PPV_ARGS(&pISampleHp));
    //采样器
    D3D12_SAMPLER_DESC stSamplerDesc = {};
    stSamplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
    stSamplerDesc.MipLODBias = 0;
    stSamplerDesc.MaxAnisotropy = 1;
    stSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    stSamplerDesc.MinLOD = 0.0f;
    stSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
    CD3DX12_CPU_DESCRIPTOR_HANDLE samcpu(pISampleHp->GetCPUDescriptorHandleForHeapStart());
    para->device->CreateSampler(&stSamplerDesc, samcpu);
    UINT vsizearr[5] = { 3915,2984,4270,2305,274 };
    UINT isizearr[5] = { 7230*3 ,4449*3 ,6579*3 ,3807*3 ,442*3  };
    //加载顶点数据
    if (para->nIndex == 6) {
     /*   for (int i = 0;i < para->mvertices.size();i++) {
            para->mvertices[i].position.x *= 100;
            para->mvertices[i].position.y *= 100;
            para->mvertices[i].position.z *= 100;
        }*/
     
    
             vbsize = (UINT)sizeof(modelVertex) * para->mvertices.size();
             ibsize = (UINT)sizeof(std::uint16_t) * para->indices.size();
            para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIVB[0]));
            para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIIB[0]));
          
            D3D12_RANGE range = { 0,0 };
            pIVB[0]->Map(0, &range, reinterpret_cast<void**>(&mapvb));
            pIIB[0]->Map(0, &range, reinterpret_cast<void**>(&mapib));

            memcpy(mapvb, para->mvertices.data(), vbsize);
            memcpy(mapib, para->indices.data(), ibsize);
            pIVB[0]->Unmap(0, nullptr);

            pIIB[0]->Unmap(0, nullptr);
            stVBV[0].BufferLocation = pIVB[0]->GetGPUVirtualAddress();
            stVBV[0].SizeInBytes = vbsize;
            stVBV[0].StrideInBytes = sizeof(modelVertex);
            stIBV[0].Format = DXGI_FORMAT_R16_UINT;
            stIBV[0].SizeInBytes = ibsize;
            stIBV[0].BufferLocation = pIIB[0]->GetGPUVirtualAddress();
        
    }

    if(para->nIndex!=8&&para->nIndex!=6){
         vbsize = (UINT)sizeof(Vertex) * (UINT)para->vertices.size();
         ibsize = (UINT)sizeof(std::uint16_t) * (UINT)para->indices.size();
        para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIVB[0]));
        para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIIB[0]));
        
        D3D12_RANGE range = { 0,0 };
        pIVB[0]->Map(0, &range, reinterpret_cast<void**>(&mapvb));
        pIIB[0]->Map(0, &range, reinterpret_cast<void**>(&mapib));

        memcpy(mapvb, para->vertices.data(), vbsize);
        memcpy(mapib, para->indices.data(), ibsize);
        pIVB[0]->Unmap(0, nullptr);
        pIIB[0]->Unmap(0, nullptr);
        stVBV[0].BufferLocation = pIVB[0]->GetGPUVirtualAddress();
        stVBV[0].SizeInBytes = vbsize;
        stVBV[0].StrideInBytes = sizeof(Vertex);
        stIBV[0].Format = DXGI_FORMAT_R16_UINT;
        stIBV[0].SizeInBytes = ibsize;
        stIBV[0].BufferLocation = pIIB[0]->GetGPUVirtualAddress();
    }
    para->cmdlist->Close();
    ::SetEvent(para->hEventRenderOver);
    ::MsgWaitForMultipleObjects(1, &para->hRunEvent, FALSE, INFINITE, QS_ALLPOSTMESSAGE);




    D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc = {};
     srvdesc.Format = pITexture->GetDesc().Format;
     para->passc.md = para->md;
     para->passc.r0 = para->r0;
     para->passc.m = para->m;
     

    CD3DX12_CPU_DESCRIPTOR_HANDLE srvheapcpu(pISRVCBVHp->GetCPUDescriptorHandleForHeapStart());
    srvdesc.Format = pITexture->GetDesc().Format;
    if (para->nIndex == 0)
    {
        srvdesc.TextureCube.MostDetailedMip = 0;
        srvdesc.TextureCube.MipLevels = pITexture->GetDesc().MipLevels;
        srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    }
    else {
        srvdesc.Texture2D.MostDetailedMip = 0;
        srvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
        srvdesc.Texture2D.MipLevels = pITexture->GetDesc().MipLevels;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;

    }

   
    srvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(pITexture.Get(), &srvdesc, srvheapcpu);//纹理
    //cbv描述符
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(passconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pICBWVP));
    byte* mapped = nullptr;
    pICBWVP->Map(0, nullptr, reinterpret_cast<void**>(&mapped));
    para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(objectconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIobjCB));
    byte* objcbmapped = nullptr;
    pIobjCB->Map(0, nullptr, reinterpret_cast<void**>(&objcbmapped));
    para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(modelmat)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pImatsCB));
    byte* modelmatmapped = nullptr;
    pImatsCB->Map(0, nullptr, reinterpret_cast<void**>(&modelmatmapped));

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvdesc = {};
    cbvdesc.BufferLocation = pICBWVP->GetGPUVirtualAddress();
    cbvdesc.SizeInBytes = sizeof(passconstant) + 255 & ~255;
    para->device->CreateConstantBufferView(&cbvdesc, srvheapcpu);//就差mamcpy cbv了//passcb
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Texture2D.MostDetailedMip = 0;
    srvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    srvdesc.Texture2D.MipLevels = pITexturenmap->GetDesc().MipLevels;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Format = pITexturenmap->GetDesc().Format;
    para->device->CreateShaderResourceView(pITexturenmap.Get(), &srvdesc, srvheapcpu);//nmap
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    if (para->nIndex == 1) {
        srvdesc.Format = para->prefilterCube->GetDesc().Format;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        srvdesc.TextureCube.MipLevels = para->prefilterCube->GetDesc().MipLevels;
        srvdesc.TextureCube.MostDetailedMip = 0;
        srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
        para->device->CreateShaderResourceView(para->prefilterCube, &srvdesc, srvheapcpu);
    }
    else if (para->nIndex == 2||para->nIndex==6) {
        srvdesc.Format = para->prefilterCube1->GetDesc().Format;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        srvdesc.TextureCube.MipLevels = para->prefilterCube1->GetDesc().MipLevels;
        srvdesc.TextureCube.MostDetailedMip = 0;
        srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
        para->device->CreateShaderResourceView(para->prefilterCube1, &srvdesc, srvheapcpu);
    }
    else if (para->nIndex == 4) {
        srvdesc.Format = para->prefilterCube2->GetDesc().Format;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        srvdesc.TextureCube.MipLevels = para->prefilterCube2->GetDesc().MipLevels;
        srvdesc.TextureCube.MostDetailedMip = 0;
        srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
        para->device->CreateShaderResourceView(para->prefilterCube2, &srvdesc, srvheapcpu);
    }
    else if (para->nIndex == 5) {
        srvdesc.Format = para->prefilterCube3->GetDesc().Format;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        srvdesc.TextureCube.MipLevels = para->prefilterCube3->GetDesc().MipLevels;
        srvdesc.TextureCube.MostDetailedMip = 0;
        srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
        para->device->CreateShaderResourceView(para->prefilterCube3, &srvdesc, srvheapcpu);
    }
    else {
        srvdesc.Format = para->prefilterCube4->GetDesc().Format;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
        srvdesc.TextureCube.MipLevels = para->prefilterCube4->GetDesc().MipLevels;
        srvdesc.TextureCube.MostDetailedMip = 0;
        srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
        para->device->CreateShaderResourceView(para->prefilterCube, &srvdesc, srvheapcpu);
    }
                                                                                                    //texcube
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    D3D12_CONSTANT_BUFFER_VIEW_DESC objcbvdesc = {};
    objcbvdesc.BufferLocation = pIobjCB->GetGPUVirtualAddress();
    objcbvdesc.SizeInBytes = sizeof(objectconstant) + 255 & ~255;
    para->device->CreateConstantBufferView(&objcbvdesc, srvheapcpu);//就差mamcpy cbv了//objcb
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Texture2D.MipLevels = para->SM->GetDesc().MipLevels;
    srvdesc.Texture2D.MostDetailedMip = 0;
    srvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    para->device->CreateShaderResourceView(para->SM, &srvdesc, srvheapcpu);//smap
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITexturehead->GetDesc().Format;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Texture2D.MipLevels = pITexturehead->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITexturehead.Get(), &srvdesc, srvheapcpu);//headdiff
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITexturejacket->GetDesc().Format;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Texture2D.MipLevels = pITexturejacket->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITexturejacket.Get(), &srvdesc, srvheapcpu);//jacketdiff
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITexturepants->GetDesc().Format;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Texture2D.MipLevels = pITexturepants->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITexturepants.Get(), &srvdesc, srvheapcpu);//pantsdiff
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITextureupbody->GetDesc().Format;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Texture2D.MipLevels = pITextureupbody->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITextureupbody.Get(), &srvdesc, srvheapcpu);//upbodydiff
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITexturenmaphead->GetDesc().Format;
    srvdesc.Texture2D.MipLevels = pITexturenmaphead->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITexturenmaphead.Get(), &srvdesc, srvheapcpu);//headnmap
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITexturenmapjacket->GetDesc().Format;
    srvdesc.Texture2D.MipLevels = pITexturenmapjacket->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITexturenmapjacket.Get(), &srvdesc, srvheapcpu);//jacketnmap
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITexturenmappants->GetDesc().Format;
    srvdesc.Texture2D.MipLevels = pITexturenmappants->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITexturenmappants.Get(), &srvdesc, srvheapcpu);//pantsnmap
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = pITexturenmapupbody->GetDesc().Format;
    srvdesc.Texture2D.MipLevels = pITexturenmapupbody->GetDesc().MipLevels;
    para->device->CreateShaderResourceView(pITexturenmapupbody.Get(), &srvdesc, srvheapcpu);//upbodynmap
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    D3D12_CONSTANT_BUFFER_VIEW_DESC modelcbvdesc = {};
    modelcbvdesc.BufferLocation = pImatsCB->GetGPUVirtualAddress();
    modelcbvdesc.SizeInBytes = (sizeof(modelmat)) + 255 & ~255;
    para->device->CreateConstantBufferView(&modelcbvdesc, srvheapcpu);//final matsCB
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    D3D12_SHADER_RESOURCE_VIEW_DESC cullasrvdesc = {};
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->cullaPrecompute->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->cullaPrecompute->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->cullaPrecompute, &cullasrvdesc, srvheapcpu);//cullaSRV
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->cullaPrecomputeavg->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->cullaPrecomputeavg->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->cullaPrecomputeavg, &cullasrvdesc, srvheapcpu);//cullaavgSRV
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->IBLLUT->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->IBLLUT->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->IBLLUT, &cullasrvdesc, srvheapcpu);//LUT
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//第十八个offset
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->SSAOmap->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->SSAOmap->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->SSAOmap, &cullasrvdesc, srvheapcpu);//SSAO
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->RSMfluxmap->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->RSMfluxmap->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->RSMfluxmap, &cullasrvdesc, srvheapcpu);//RSMflux
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->RSMnormalmap->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->RSMnormalmap->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->RSMnormalmap, &cullasrvdesc, srvheapcpu);//RSMnormal
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->RSMwposmap->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->RSMwposmap->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->RSMwposmap, &cullasrvdesc, srvheapcpu);//RSMwpos
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->SSDODLmap->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->SSDODLmap->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->SSDODLmap, &cullasrvdesc, srvheapcpu);//SSDODL
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->viewdepthmap->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->viewdepthmap, &cullasrvdesc, srvheapcpu);//viewdepthmap
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//24
    cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    cullasrvdesc.Format = para->SSDOnormalmap->GetDesc().Format;
    cullasrvdesc.Texture2D.MostDetailedMip = 0;
    cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    cullasrvdesc.Texture2D.MipLevels = para->SSDOnormalmap->GetDesc().MipLevels;
    cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(para->SSDOnormalmap, &cullasrvdesc, srvheapcpu);//SSDOnormal
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//25
        cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        cullasrvdesc.Format = para->lastframe[0]->GetDesc().Format;
        cullasrvdesc.Texture2D.MostDetailedMip = 0;
        cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
        cullasrvdesc.Texture2D.MipLevels = para->lastframe[0]->GetDesc().MipLevels;
        cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        para->device->CreateShaderResourceView(para->lastframe[0], &cullasrvdesc, srvheapcpu);//lastframeSRV

        srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//26
        cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        cullasrvdesc.Format = para->lastframe[1]->GetDesc().Format;
        cullasrvdesc.Texture2D.MostDetailedMip = 0;
        cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
        cullasrvdesc.Texture2D.MipLevels = para->lastframe[1]->GetDesc().MipLevels;
        cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        para->device->CreateShaderResourceView(para->lastframe[1], &cullasrvdesc, srvheapcpu);//lastframeSRV
        srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//27
        cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        cullasrvdesc.Format = para->Hizmap->GetDesc().Format;
        cullasrvdesc.Texture2D.MostDetailedMip = 0;
        cullasrvdesc.Texture2D.ResourceMinLODClamp = 0.0f;//可以访问的最小层级
        cullasrvdesc.Texture2D.MipLevels = para->Hizmap->GetDesc().MipLevels;
        cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        para->device->CreateShaderResourceView(para->Hizmap, &cullasrvdesc, srvheapcpu);//Hizmap
        srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//28
        cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
        cullasrvdesc.Format = para->LPVvoxel->GetDesc().Format;
        cullasrvdesc.Texture3D.MipLevels = para->LPVvoxel->GetDesc().MipLevels;
        cullasrvdesc.Texture3D.MostDetailedMip = 0;
        cullasrvdesc.Texture3D.ResourceMinLODClamp = 0;
        cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        para->device->CreateShaderResourceView(para->LPVvoxel, &cullasrvdesc, srvheapcpu);//voxel1
        srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//29
        cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
        cullasrvdesc.Format = para->LPVvoxel2->GetDesc().Format;
        cullasrvdesc.Texture3D.MipLevels = para->LPVvoxel2->GetDesc().MipLevels;
        cullasrvdesc.Texture3D.MostDetailedMip = 0;
        cullasrvdesc.Texture3D.ResourceMinLODClamp = 0;
        cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        para->device->CreateShaderResourceView(para->LPVvoxel2, &cullasrvdesc, srvheapcpu);//voxel2
        srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//30
        cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
        cullasrvdesc.Format = para->LPVvoxel3->GetDesc().Format;
        cullasrvdesc.Texture3D.MipLevels = para->LPVvoxel3->GetDesc().MipLevels;
        cullasrvdesc.Texture3D.MostDetailedMip = 0;
        cullasrvdesc.Texture3D.ResourceMinLODClamp = 0;
        cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        para->device->CreateShaderResourceView(para->LPVvoxel3, &cullasrvdesc, srvheapcpu);//voxel3
        D3D12_UNORDERED_ACCESS_VIEW_DESC UAVdesc = {};
        for (int i = 0;i < 6;i++) {
            srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//31
            UAVdesc.Format = para->clipmap[i]->GetDesc().Format;
            UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
            UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level
            UAVdesc.Texture3D.FirstWSlice = 0;//第一个深度切片索引
            UAVdesc.Texture3D.WSize = -1;
            para->device->CreateUnorderedAccessView(para->clipmap[i], nullptr, &UAVdesc, srvheapcpu);
        }
        for (int i = 0;i < 6;i++) {
            srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//37
            cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
            cullasrvdesc.Format = para->clipmap[i]->GetDesc().Format;
            cullasrvdesc.Texture3D.MipLevels = para->clipmap[i]->GetDesc().MipLevels;
            cullasrvdesc.Texture3D.MostDetailedMip = 0;
            cullasrvdesc.Texture3D.ResourceMinLODClamp = 0;
            cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            para->device->CreateShaderResourceView(para->clipmap[i], &cullasrvdesc, srvheapcpu);//clipmapSRV
        }
        for (int i = 0;i < 6;i++) {
            srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//43
            UAVdesc.Format = para->clipmapNormal[i]->GetDesc().Format;
            UAVdesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE3D;
            UAVdesc.Texture3D.MipSlice = 0;//输出的uav是第几层level
            UAVdesc.Texture3D.FirstWSlice = 0;//第一个深度切片索引
            UAVdesc.Texture3D.WSize = -1;
            para->device->CreateUnorderedAccessView(para->clipmapNormal[i], nullptr, &UAVdesc, srvheapcpu);
        }
        for (int i = 0;i < 6;i++) {
            srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));//49
            cullasrvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
            cullasrvdesc.Format = para->clipmapNormal[i]->GetDesc().Format;
            cullasrvdesc.Texture3D.MipLevels = para->clipmapNormal[i]->GetDesc().MipLevels;
            cullasrvdesc.Texture3D.MostDetailedMip = 0;
            cullasrvdesc.Texture3D.ResourceMinLODClamp = 0;
            cullasrvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            para->device->CreateShaderResourceView(para->clipmapNormal[i], &cullasrvdesc, srvheapcpu);//clipmapNormalSRV
        }
    SetEvent(para->hEventRenderOver);
    
    DWORD dwRet = 0;
    BOOL  bQuit = FALSE;
    MSG   msg = {};
    while (!bQuit) {
        dwRet = ::MsgWaitForMultipleObjects(1, &para->hRunEvent, FALSE, INFINITE, QS_ALLPOSTMESSAGE);
        switch (dwRet - WAIT_OBJECT_0) {
        case 0:
        {
            int nu = 0;
            if (para->nIndex == 8) {
                vbsize = (UINT)sizeof(voxelVertex) * (para->voxelvertices)->size();
                ibsize = (UINT)sizeof(std::uint16_t) * (para->voxelindices)->size();
                para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIVB[0]));
                para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIIB[0]));

                D3D12_RANGE range = { 0,0 };
                pIVB[0]->Map(0, &range, reinterpret_cast<void**>(&mapvb));
                pIIB[0]->Map(0, &range, reinterpret_cast<void**>(&mapib));

                memcpy(mapvb, para->voxelvertices->data(), vbsize);
                memcpy(mapib, para->voxelindices->data(), ibsize);
                stVBV[0].BufferLocation = pIVB[0]->GetGPUVirtualAddress();
                stVBV[0].SizeInBytes = vbsize;
                stVBV[0].StrideInBytes = sizeof(voxelVertex);
                stIBV[0].Format = DXGI_FORMAT_R16_UINT;
                stIBV[0].SizeInBytes = ibsize;
                stIBV[0].BufferLocation = pIIB[0]->GetGPUVirtualAddress();

                pIVB[0]->Unmap(0, nullptr);

                pIIB[0]->Unmap(0, nullptr);
            }
            if (para->nIndex == 6)
            {
                nu = 1;
            }
            if (para->nIndex == 1) {
                XMFLOAT3 f3 = { 0,20.0f,0 };
                XMVECTOR v3 = XMLoadFloat3(&f3);
                XMMATRIX world = XMMatrixTranslationFromVector(v3);
                XMMATRIX worldinvT = MathHelper::InverseTranspose(world);
                XMStoreFloat4x4(&para->passc.WinvT, XMMatrixTranspose(worldinvT));
                XMStoreFloat4x4(&para->passc.W, XMMatrixTranspose(world));
                
                XMStoreFloat4x4(&para->passc.MVP, XMMatrixTranspose(XMMatrixMultiply(world, XMMatrixTranspose(XMLoadFloat4x4(&para->passc.MVP)))));
            }
            //每个子线程必须的初始化
            para->cmdalloc->Reset();
            para->cmdlist->Reset(para->cmdalloc, para->PSO);
            objectconstant objc;
            modelmat mmats;
            for (int i = 0;i < 58;i++) {
                mmats.finalmats[i] = MathHelper::Identity4x4();
            }
            std::vector<XMMATRIX> finalmats;
            finalmats.resize(58);
            if (para->nIndex == 6) {//model
                para->passc.r0 = XMFLOAT3(0.5f, 0.5f, 0.5f);
                para->passc.m = 0.4f;
                std::vector<XMMATRIX>toroot;
                toroot.resize(58);
                toroot[0] = animationclips[0].boneAnimations[0].interpolation(timesecond);
                for (int i = 1;i < 58;i++) {
                    int parentindex;
                    XMMATRIX parenttoroot;
                  //if (i == 0) {
                  //      XMMATRIX toparent = animationclips[0].boneAnimations[i].interpolation(timesecond);
                  //   /*   parentindex = bonefamily[i];
                  //     parenttoroot = XMLoadFloat4x4(&MathHelper::Identity4x4());*/
                  //      toroot[i] = toparent;
                  //  }
              
                        XMMATRIX toparent = animationclips[0].boneAnimations[i].interpolation(timesecond);
                        parentindex = bonefamily[i];
                         parenttoroot = toroot[parentindex];
                        toroot[i] = XMMatrixMultiply(toparent, parenttoroot);
                                    
                }
                for (int i = 0;i < 58;i++) {

                    XMMATRIX finalmatrix = XMMatrixMultiply((XMLoadFloat4x4(& offsetMatrix[i])),toroot[i]);
                    finalmats[i] =XMMatrixTranspose(finalmatrix);
                }
                XMMATRIX world = XMMatrixTranslation(0, 0, 20.0f);
                XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
                XMFLOAT4X4 final4x4[58];

                for (int i = 0;i < 58;i++) {
                  
                    XMStoreFloat4x4(&final4x4[i], finalmats[i]);

               }
                for (int i = 0;i < 58;i++) {
             /*       mmats.finalmats[i] = final4x4[i];
                 */
                }
                memcpy(modelmatmapped, &mmats, sizeof(modelmat));
            }

            else {
                objc.world = para->passc.W;
                para->passc.r0 = XMFLOAT3(0.5f, 0.5f, 0.5f);
            }
         
             if (para->nIndex == 1) {
                 XMMATRIX world = XMMatrixTranslation(0.0f, 20.0f, 0);
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
                 para->passc.r0 = XMFLOAT3(0.4f, 0.4f, 0.4f);
                 para->passc.m = 0.2f;
             }
             if (para->nIndex == 2) {
                 XMMATRIX world = XMMatrixTranslation(20.0f, 20.0f, 0);
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
                 para->passc.r0 = XMFLOAT3(0.4f, 0.4f, 0.4f);
                 para->passc.m = 0.4f;
             }
             if (para->nIndex == 4) {
                 XMMATRIX world = XMMatrixTranslation(40.0f, 20.0f, 0);
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
                 para->passc.r0 = XMFLOAT3(0.4f, 0.4f, 0.4f);
                 para->passc.m = 0.6f;
             }
             if (para->nIndex == 5) {
                 XMMATRIX world = XMMatrixTranslation(60.0f, 20.0f, 0);
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
                 para->passc.r0 = XMFLOAT3(0.4f, 0.4f, 0.4f);
                 para->passc.m = 0.8f;
             }
             if (para->nIndex == 7) {
                 XMMATRIX world = XMMatrixTranslation(0, 0, 20.0f);
                 XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
                 para->passc.r0 = XMFLOAT3(0.4f, 0.4f, 0.4f);
                 para->passc.m = 0.8f;
             }
             memcpy(mapped, &para->passc, sizeof(passconstant));

            XMMATRIX worldmat = XMLoadFloat4x4(&para->passc.W);
            XMStoreFloat4x4(&objc.invTworld,XMMatrixTranspose( MathHelper::InverseTranspose(worldmat)));
          
            memcpy(objcbmapped, &objc, sizeof(objectconstant));
            CD3DX12_CPU_DESCRIPTOR_HANDLE lastframeRTV;
         /*   if (framenum == 1) {
                lastframeRTV = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 49, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            }
            else {
                if (framenum % 2 == 0) {
                    lastframeRTV = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 50, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                }
                else {
                    lastframeRTV = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), 49, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
                }
            }*/
      
            CD3DX12_CPU_DESCRIPTOR_HANDLE rtvhandle(pIRTVHeap->GetCPUDescriptorHandleForHeapStart(), para->nCurrentFrameIndex, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            CD3DX12_CPU_DESCRIPTOR_HANDLE dsvhandle(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
          /*  D3D12_CPU_DESCRIPTOR_HANDLE desarr[2];
            desarr[0] = rtvhandle;
            desarr[1] = lastframeRTV;
            para->cmdlist->OMSetRenderTargets(2, desarr, FALSE, &dsvhandle);
            desarr[1] = rtvhandle;
            desarr[0] = lastframeRTV;*/
            para->cmdlist->OMSetRenderTargets(1, &rtvhandle, FALSE, &dsvhandle);
            para->cmdlist->RSSetScissorRects(1, &stScissorRect);
            para->cmdlist->RSSetViewports(1, &stViewPort);
            //draw
         
            if (para->nIndex == 6) {
               
                para->cmdlist->SetPipelineState(para->PSO);
                para->cmdlist->SetGraphicsRootSignature(para->rs);
              
                ID3D12DescriptorHeap* heaps[] = { pISRVCBVHp.Get(),pISampleHp.Get() };
                para->cmdlist->SetDescriptorHeaps(_countof(heaps), heaps);
              
                    CD3DX12_GPU_DESCRIPTOR_HANDLE srvgpu(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart());
                    para->cmdlist->SetGraphicsRootDescriptorTable(0, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(2, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(3, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(4, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(5, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    //para->cmdlist->SetGraphicsRootDescriptorTable(6, srvgpu);
                    srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 10 + 4, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(7, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(8, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(9, srvgpu);//srv堆中间缺一个Favg但是跟签名有（10）;
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                  
                    para->cmdlist->SetGraphicsRootDescriptorTable(11, srvgpu);
                    srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 18, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(12, srvgpu);
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(13, srvgpu);//flux
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(14, srvgpu);//normal
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(15, srvgpu);//wpos
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(16, srvgpu);//SSDODL
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(6, srvgpu);//viewdepth
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(17, srvgpu);
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(18, srvgpu);//lastframe
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(19, srvgpu);//hiz
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(20, srvgpu);//LPVvoxel
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(21, srvgpu);//LPVvoxel
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(22, srvgpu);//LPVvoxel
                        for (int i = 0;i < 6;i++) {
                            srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                            para->cmdlist->SetGraphicsRootDescriptorTable(23+i, srvgpu);//clipmapUAV
                    }
                        for (int i = 0;i < 6;i++) {
                            srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                            para->cmdlist->SetGraphicsRootDescriptorTable(29 + i, srvgpu);//clipmapSRV
                        }
                        srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 48, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        for (int i = 0;i < 6;i++) {
                            srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                            para->cmdlist->SetGraphicsRootDescriptorTable(35 + i, srvgpu);//clipmapNormalSRV
                        }
                    para->cmdlist->SetGraphicsRootDescriptorTable(1, pISampleHp->GetGPUDescriptorHandleForHeapStart());
                    para->cmdlist->IASetVertexBuffers(0, 1, &stVBV[0]);
                    para->cmdlist->IASetIndexBuffer(&stIBV[0]);
                    para->cmdlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                    int istarr[5] = { 0,7230 * 3,11679 * 3,18258 * 3,22065 * 3 };
                    int vstarr[5] = { 0,3915,6899,11169,13474 };
                    for (int i = 0;i < 5;i++) {
                       
                        srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(),6+i,para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(0, srvgpu);
                        if(i==4)
                            srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 10 + 3, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        else
                            srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 10 + i, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(3, srvgpu);
                  
                     
                            para->cmdlist->DrawIndexedInstanced(isizearr[i], 1, istarr[i], 0, 0);//index是总体vertex的index，所以第四个参数为0;
                        
                    }

            }
            else {
                para->cmdlist->SetPipelineState(para->PSO);
                para->cmdlist->SetGraphicsRootSignature(para->rs);
                CD3DX12_GPU_DESCRIPTOR_HANDLE srvgpu(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart());
                ID3D12DescriptorHeap* heaps[] = { pISRVCBVHp.Get(),pISampleHp.Get() };
                para->cmdlist->SetDescriptorHeaps(_countof(heaps), heaps);
                para->cmdlist->SetGraphicsRootDescriptorTable(0, srvgpu);
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(2, srvgpu);
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(3, srvgpu);
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(4, srvgpu);
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(5, srvgpu);
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                //para->cmdlist->SetGraphicsRootDescriptorTable(6, srvgpu);
                srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 10 + 4+1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(8, srvgpu);
                srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 10 + 4 + 2, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(9, srvgpu);

                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
              
                para->cmdlist->SetGraphicsRootDescriptorTable(11, srvgpu);
                srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 18, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(12, srvgpu);
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(13, srvgpu);//flux
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(14, srvgpu);//normal
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(15, srvgpu);//wpos
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(16, srvgpu);//SSDODL
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(6, srvgpu);//viewdepth
                srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                para->cmdlist->SetGraphicsRootDescriptorTable(17, srvgpu);

                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(18, srvgpu);//lastframe
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(19, srvgpu);//hiz
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(20, srvgpu);//LPVvoxel
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(21, srvgpu);//LPVvoxel
                    srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    para->cmdlist->SetGraphicsRootDescriptorTable(22, srvgpu);//LPVvoxel
                    //srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 42, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    for (int i = 0;i < 6;i++) {
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(23 + i, srvgpu);//clipmapUAV
                    }
                    for (int i = 0;i < 6;i++) {
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(29 + i, srvgpu);//clipmapSRV
                    }
                    srvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 48, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                    for (int i = 0;i < 6;i++) {
                        srvgpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
                        para->cmdlist->SetGraphicsRootDescriptorTable(35 + i, srvgpu);//clipmapNormalSRV
                    }

                para->cmdlist->SetGraphicsRootDescriptorTable(1, pISampleHp->GetGPUDescriptorHandleForHeapStart());

                if(para->nIndex==7)
                    para->cmdlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
                else if (para->nIndex == 8)
                {
                    para->cmdlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                    //int size = para->voxelindices->size();
                    //int sizediv4 = size / 81;
                    //for (int i = 0;i < 81;i++) {
                    //    para->cmdlist->DrawIndexedInstanced(sizediv4, 1, sizediv4*i, 0, 0);
                    //
                    for (int i = 0;i < 6;i++) {
                        para->cmdlist->IASetVertexBuffers(0, 2, (*(para->voxelvbv))[i]);//数组指针取*是数组首地址，后面加偏移还是地址(这个偏移是在二维数组层面的偏移，到编译器换成一维数组的偏移)，所以还得加一个*
                        para->cmdlist->IASetIndexBuffer((para->voxelibv));
                        para->cmdlist->DrawIndexedInstanced(36, countVoxelofLevel[i], 0, 0, 0);
                    }
                }
                else {
                    para->cmdlist->IASetVertexBuffers(0, 1, &stVBV[0]);
                    para->cmdlist->IASetIndexBuffer(&stIBV[0]);
                    para->cmdlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                    para->cmdlist->DrawIndexedInstanced(para->indices.size(), 1, 0, 0, 0);
                }
                //para->cmdlist->OMSetRenderTargets(1, &lastframeRTV, FALSE, &dsvhandle);
                //para->cmdlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                //para->cmdlist->DrawIndexedInstanced(para->indices.size(), 1, 0, 0, 0);
             
            }
            /*int lastFrameindex = (para->nIndex - 1 >= 0) ? (para->nIndex - 1) : 2;*/
            //para->cmdlist->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(para->FrameArr[lastFrameindex], D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET));
            //para->cmdlist->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(para->FrameArr[para->nIndex], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
            para->cmdlist->Close();
            //delete para->cmdlist;
            //delete para->cmdalloc;
            
            SetEvent(para->hEventRenderOver);
        }
        break;
        }
    }
    return 0;
}
UINT __stdcall threadfuncnew(void* ppara) {
    threadparasnew* para = reinterpret_cast<threadparasnew*>(ppara);
    ComPtr<ID3D12Resource>				newpITexture;
    ComPtr<ID3D12Resource>				newpITexturenmap;
    ComPtr<ID3D12Resource>				newpITextureUpload;
    ComPtr<ID3D12Resource>				newpITexturenmapUpload;
    ComPtr<ID3D12Resource>				newpITexturecube;
    ComPtr<ID3D12Resource>				newpITexturecubeUpload;
    ComPtr<ID3D12Resource>				pIVB[4];
    ComPtr<ID3D12Resource>				pIIB[4];
    ComPtr<ID3D12Resource>			    pICBWVP;
    int                                 numritem = 4;
    ComPtr<ID3D12Resource>			    pIobjCB[4*6+1];
    ComPtr<ID3D12Resource>			    pICBS[6];
    ComPtr<ID3D12DescriptorHeap>		pISRVCBVHp;
    ComPtr<ID3D12DescriptorHeap>		pISampleHp;
    ComPtr<ID3D12DescriptorHeap>        pIdsvHeap;
    ComPtr<ID3D12Resource>              pIDSVbuf;
    D3D12_VERTEX_BUFFER_VIEW			stVBV[4] = {};
    D3D12_INDEX_BUFFER_VIEW				stIBV[4] = {};
    UINT width=512;
    UINT height = 512;
    objectconstant objc;
    ComPtr<ID3D12Resource>              spheretexcube;
    byte* mappedcb[6];
    byte* objcbmapped[6 * 4 + 1];
    D3D12_VIEWPORT mviewport = { 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
    D3D12_RECT							mscissorrect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
    try {
        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, para->pszDDSFile, newpITexture, newpITextureUpload));
        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\bricks2_nmap.dds", newpITexturenmap, newpITexturenmapUpload));
        ThrowIfFailed(CreateDDSTextureFromFile12(para->device, para->cmdlist, L"Texture\\sunsetcube1024.dds", newpITexturecube, newpITexturecubeUpload));

    }
    catch (DxException& e) {
        WriteConsole(g_hOutput, e.ToString().c_str(), e.ToString().size(), NULL, NULL);
        while (1);
    }
    D3D12_RESOURCE_DESC spherecubetext = {};
    spherecubetext.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    spherecubetext.Alignment = 0;
    spherecubetext.Width = width;
    spherecubetext.Height = height;
    spherecubetext.DepthOrArraySize = 6;
    spherecubetext.MipLevels = 1;
    spherecubetext.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    spherecubetext.SampleDesc.Count = 1;
    spherecubetext.SampleDesc.Quality = 0;
    spherecubetext.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    spherecubetext.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
    ThrowIfFailed(para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &spherecubetext,D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&spheretexcube)));
    //创建描述符堆
    D3D12_DESCRIPTOR_HEAP_DESC srvheapdesc = {};
    srvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvheapdesc.NumDescriptors = 38;
    srvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    para->device->CreateDescriptorHeap(&srvheapdesc, IID_PPV_ARGS(&pISRVCBVHp));
    D3D12_DESCRIPTOR_HEAP_DESC samheapdesc = {};
    samheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
    samheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    samheapdesc.NumDescriptors = 1;
    para->device->CreateDescriptorHeap(&samheapdesc, IID_PPV_ARGS(&pISampleHp));
    D3D12_DESCRIPTOR_HEAP_DESC dsvheapdesc = {};
    dsvheapdesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    dsvheapdesc.NumDescriptors = 1;
    dsvheapdesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    para->device->CreateDescriptorHeap(&dsvheapdesc, IID_PPV_ARGS(&pIdsvHeap));
    //采样器
    D3D12_SAMPLER_DESC stSamplerDesc = {};
    stSamplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
    stSamplerDesc.MipLODBias = 0;
    stSamplerDesc.MaxAnisotropy = 1;
    stSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    stSamplerDesc.MinLOD = 0.0f;
    stSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
    
    CD3DX12_CPU_DESCRIPTOR_HANDLE samcpu(pISampleHp->GetCPUDescriptorHandleForHeapStart());
    para->device->CreateSampler(&stSamplerDesc, samcpu);
    //加载顶点数据
    for (int i = 0;i < numritem;i++) {
        UINT vbsize = (UINT)sizeof(Vertex) * (UINT)para->vertices[i].size();
        UINT ibsize = (UINT)sizeof(std::uint16_t) * (UINT)para->indices[i].size();
        para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(vbsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIVB[i]));
        para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(ibsize), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIIB[i]));
        UINT8* mapib = nullptr;UINT8* mapvb = nullptr;
        D3D12_RANGE range = { 0,0 };
        pIVB[i]->Map(0, &range, reinterpret_cast<void**>(&mapvb));
        pIIB[i]->Map(0, &range, reinterpret_cast<void**>(&mapib));

        memcpy(mapvb, para->vertices[i].data(), vbsize);
        memcpy(mapib, para->indices[i].data(), ibsize);
        pIVB[i]->Unmap(0, nullptr);
        pIIB[i]->Unmap(0, nullptr);
        stVBV[i].BufferLocation = pIVB[i]->GetGPUVirtualAddress();
        stVBV[i].SizeInBytes = vbsize;
        stVBV[i].StrideInBytes = sizeof(Vertex);
        stIBV[i].Format = DXGI_FORMAT_R16_UINT;
        stIBV[i].SizeInBytes = ibsize;
        stIBV[i].BufferLocation = pIIB[i]->GetGPUVirtualAddress();
    }
    //dsv
    D3D12_RESOURCE_DESC dsdesc = {};
    dsdesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    dsdesc.Alignment = 0;
    dsdesc.Width = width;
    dsdesc.Height = height;
    dsdesc.DepthOrArraySize = 1;
    dsdesc.MipLevels = 1;
    dsdesc.Format = DXGI_FORMAT_D32_FLOAT;
    dsdesc.SampleDesc.Count = 1;
    dsdesc.SampleDesc.Quality = 0;
    dsdesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    dsdesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
    D3D12_CLEAR_VALUE dsclear = {};
    dsclear.Format = DXGI_FORMAT_D32_FLOAT;
    dsclear.DepthStencil.Depth = 1.0f;
    dsclear.DepthStencil.Stencil = 0;
    ThrowIfFailed(para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT), D3D12_HEAP_FLAG_NONE, &dsdesc, D3D12_RESOURCE_STATE_COMMON, &dsclear, IID_PPV_ARGS(&pIDSVbuf)));
    para->cmdlist->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pIDSVbuf.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
    CD3DX12_CPU_DESCRIPTOR_HANDLE dsvhandle(pIdsvHeap->GetCPUDescriptorHandleForHeapStart());
    para->device->CreateDepthStencilView(pIDSVbuf.Get(), nullptr, dsvhandle);
    para->cmdlist->Close();
    ::SetEvent(para->hEventRenderOver);
    ::MsgWaitForMultipleObjects(1, &para->hRunEvent, FALSE, INFINITE, QS_ALLPOSTMESSAGE);


    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvhandle(para->rtvheap->GetCPUDescriptorHandleForHeapStart(),2* para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
  
    for (int i = 0;i < 6;i++) {
        rtvhandle.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
        D3D12_RENDER_TARGET_VIEW_DESC cubertvdesc = {};
        cubertvdesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
        cubertvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        cubertvdesc.Texture2DArray.MipSlice = 0;
        cubertvdesc.Texture2DArray.PlaneSlice = 0;
        cubertvdesc.Texture2DArray.FirstArraySlice = i;
        cubertvdesc.Texture2DArray.ArraySize = 1;
        para->device->CreateRenderTargetView(spheretexcube.Get(), &cubertvdesc, rtvhandle);
       
    }
    D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc = {};
    srvdesc.Format = newpITexture->GetDesc().Format;
    para->passc.md = para->md;
    para->passc.r0 = para->r0;
    para->passc.m = para->m;
    XMStoreFloat3(&para->passc.lightPos, lightposition);
    XMStoreFloat4x4(&para->passc.S, lightviewproj);
    XMStoreFloat4x4(&para->passc.uvMAT, smuvmat);

    CD3DX12_CPU_DESCRIPTOR_HANDLE srvheapcpu(pISRVCBVHp->GetCPUDescriptorHandleForHeapStart());
    srvdesc.Format = newpITexture->GetDesc().Format;
        srvdesc.Texture2D.MostDetailedMip = 0;
        srvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
        srvdesc.Texture2D.MipLevels = newpITexture->GetDesc().MipLevels;
        srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    para->device->CreateShaderResourceView(newpITexture.Get(), &srvdesc, srvheapcpu);//纹理
    //cbv描述符
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(passconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pICBWVP));
    byte* mapped = nullptr;
    pICBWVP->Map(0, nullptr, reinterpret_cast<void**>(&mapped));
    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvdesc = {};
    cbvdesc.BufferLocation = pICBWVP->GetGPUVirtualAddress();
    cbvdesc.SizeInBytes = sizeof(passconstant) + 255 & ~255;
    para->device->CreateConstantBufferView(&cbvdesc, srvheapcpu);//就差mamcpy cbv了//球体本身的cbv
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Texture2D.MostDetailedMip = 0;
    srvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    srvdesc.Texture2D.MipLevels = newpITexturenmap->GetDesc().MipLevels;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Format = newpITexturenmap->GetDesc().Format;
    para->device->CreateShaderResourceView(newpITexturenmap.Get(), &srvdesc, srvheapcpu);//法线贴图
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = newpITexturecube->GetDesc().Format;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    srvdesc.TextureCube.MipLevels = newpITexturecube->GetDesc().MipLevels;
    srvdesc.TextureCube.MostDetailedMip = 0;
    srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
    para->device->CreateShaderResourceView(newpITexturecube.Get(), &srvdesc, srvheapcpu);//天空
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = spheretexcube->GetDesc().Format;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    srvdesc.TextureCube.MipLevels = spheretexcube->GetDesc().MipLevels;
    srvdesc.TextureCube.MostDetailedMip = 0;
    srvdesc.TextureCube.ResourceMinLODClamp = 0.0f;
    para->device->CreateShaderResourceView(spheretexcube.Get(), &srvdesc, srvheapcpu);//rt立方体
    
    for (int i = 0;i < 25;i++) {
        para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(objectconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pIobjCB[i]));
    }
    for (int i = 0;i < 6 * 4+1 ;i++) {
        srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
         objcbmapped[i] = nullptr;
        pIobjCB[i]->Map(0, nullptr, reinterpret_cast<void**>(&objcbmapped[i]));
        D3D12_CONSTANT_BUFFER_VIEW_DESC objcbvdesc = {};
        objcbvdesc.BufferLocation = pIobjCB[i]->GetGPUVirtualAddress();
        objcbvdesc.SizeInBytes = sizeof(objectconstant) + 255 & ~255;
        para->device->CreateConstantBufferView(&objcbvdesc, srvheapcpu);
    }
    for (int i = 0;i < 6;i++) {
        srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        para->device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(passconstant)), D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pICBS[i]));
        mappedcb[i] = nullptr;
        pICBS[i]->Map(0, nullptr, reinterpret_cast<void**>(&mappedcb[i]));
        cbvdesc.BufferLocation = pICBS[i]->GetGPUVirtualAddress();
        para->device->CreateConstantBufferView(&cbvdesc, srvheapcpu);
    }
    srvheapcpu.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    srvdesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvdesc.Texture2D.MipLevels = para->SM->GetDesc().MipLevels;
    srvdesc.Texture2D.MostDetailedMip = 0;
    srvdesc.Texture2D.ResourceMinLODClamp = 0.0f;
    para->device->CreateShaderResourceView(para->SM, &srvdesc, srvheapcpu);
    SetEvent(para->hEventRenderOver);
    DWORD dwRet = 0;
    BOOL  bQuit = FALSE;
    MSG   msg = {};
    while (!bQuit) {
        dwRet = ::MsgWaitForMultipleObjects(1, &para->hRunEvent, FALSE, INFINITE, QS_ALLPOSTMESSAGE);
        switch (dwRet - WAIT_OBJECT_0) {
        case 0:
        {
        
   
         /*
            XMVECTOR targetvec[6] = {
              XMVector4Normalize( XMVectorSet(1.0f,0,0,0)),
                XMVector4Normalize(XMVectorSet(-1.0f,0,0,0)),
                XMVector4Normalize(XMVectorSet(0,1.0f,0,0)),
                 XMVector4Normalize(XMVectorSet(0,-1.0f,0,0)),
                XMVector4Normalize(XMVectorSet(0,0,1.0f,0)),
                XMVector4Normalize(XMVectorSet(0,0,-1.0f,0))
            };
            XMVECTOR upvec[6] = {
                XMVectorSet(0,1.0f,0,0),
                XMVectorSet(0,1.0f,0,0),
                XMVectorSet(0,0,-1.0f,0),
                XMVectorSet(0,0,1.0f,0),
                XMVectorSet(0,1.0f,0,0),
                XMVectorSet(0,1.0f,0,0)
            };
            for (int i = 0;i < 6;i++) {
                passconstant pass;
                pass.eyepos = XMFLOAT3(15.0f, 15.0f, 0);
                XMVECTOR eyeposv = XMVectorSet(15.0f, 15.0f, 0, 0);
                pass.P = para->passc.P;
                XMMATRIX passview = XMMatrixLookToLH(eyeposv, targetvec[i], upvec[i]);
                XMStoreFloat4x4(&pass.V,XMMatrixTranspose( passview));
                XMMATRIX passproj= XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)width / (FLOAT)height, 0.1f, 1000.0f);
                XMStoreFloat4x4(&pass.VP,XMMatrixTranspose( XMMatrixMultiply(passview, passproj)));
              XMStoreFloat3(&pass.lightPos, lightposition);
              XMStoreFloat4x4(&pass.S, lightviewproj);
              XMStoreFloat4x4(&pass.uvMAT, smuvmat);
                memcpy(mappedcb[i],&pass, sizeof(passconstant));
            }
            memcpy(mapped, &para->passc, sizeof(passconstant));*/

         /*   para->cmdalloc->Reset();
            para->cmdlist->Reset(para->cmdalloc, para->skyPSO);
            para->cmdlist->RSSetScissorRects(1, &mscissorrect);
            para->cmdlist->RSSetViewports(1, &mviewport);
            para->cmdlist->SetGraphicsRootSignature(para->rs);
            para->cmdlist->ResourceBarrier(1,&CD3DX12_RESOURCE_BARRIER::Transition(spheretexcube.Get(),D3D12_RESOURCE_STATE_GENERIC_READ,D3D12_RESOURCE_STATE_RENDER_TARGET));
            ID3D12DescriptorHeap* cheaps[] = { pISRVCBVHp.Get(),pISampleHp.Get() };
            para->cmdlist->SetDescriptorHeaps(2, cheaps);
            CD3DX12_CPU_DESCRIPTOR_HANDLE currrtvhandle(para->rtvheap->GetCPUDescriptorHandleForHeapStart(),2* para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));*/
            //for (int i = 0;i < 6;i++) {
            //   
            //    currrtvhandle.Offset(1, para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
            //  
            //    para->cmdlist->SetPipelineState(para->skyPSO);
            //   
            //    CD3DX12_GPU_DESCRIPTOR_HANDLE currsrvgpu(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(),3*para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    CD3DX12_CPU_DESCRIPTOR_HANDLE currdsvcpu(pIdsvHeap->GetCPUDescriptorHandleForHeapStart());
            //    
            //    para->cmdlist->ClearRenderTargetView(currrtvhandle, Colors::AliceBlue, 0, nullptr);
            //    para->cmdlist->ClearDepthStencilView(currdsvcpu, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
            //    para->cmdlist->OMSetRenderTargets(1, &currrtvhandle, FALSE, &currdsvcpu);
            //    
            //    para->cmdlist->SetGraphicsRootDescriptorTable(0, currsrvgpu);
            //    para->cmdlist->SetGraphicsRootDescriptorTable(1, pISampleHp->GetGPUDescriptorHandleForHeapStart());
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(),(30+i)*para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    para->cmdlist->SetGraphicsRootDescriptorTable(2, currsrvgpu);
            //    XMMATRIX w = XMMatrixTranslationFromVector(XMVectorSet(20.0f, 20.0f, 0, 0));
            //    XMStoreFloat4x4(&objc.world, XMMatrixTranspose( w));//镜面空间每个物体的世界矩阵
            //    
            //    XMStoreFloat4x4(&objc.invTworld, XMMatrixTranspose(MathHelper::InverseTranspose(w)));
            //    memcpy(objcbmapped[i*4+1], &objc, sizeof(objectconstant));
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), (6+(i*4)) * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    para->cmdlist->SetGraphicsRootDescriptorTable(5, currsrvgpu);
            //    para->cmdlist->IASetVertexBuffers(0, 1, &stVBV[0]);
            //    para->cmdlist->IASetIndexBuffer(&stIBV[0]);
            //    para->cmdlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            //    para->cmdlist->DrawIndexedInstanced(para->indices[0].size(), 1, 0, 0, 0);//天空
            //    para->cmdlist->SetPipelineState(para->PSO);
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart());
            //    para->cmdlist->SetGraphicsRootDescriptorTable(0, currsrvgpu);
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(),2*para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    para->cmdlist->SetGraphicsRootDescriptorTable(3, currsrvgpu);
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 3 * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    para->cmdlist->SetGraphicsRootDescriptorTable(4, currsrvgpu); 
            //    XMMATRIX world = XMMatrixTranslationFromVector(XMVectorSet(0, 10.0f, 0, 0));
            //   
            //    XMStoreFloat4x4(&objc.invTworld, XMMatrixTranspose(MathHelper::InverseTranspose(world)));
            //    XMStoreFloat4x4(&objc.world,XMMatrixTranspose( world));
            //    memcpy(objcbmapped[i*4+2], &objc, sizeof(objectconstant));
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), (7+(i*4)) * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    para->cmdlist->SetGraphicsRootDescriptorTable(5, currsrvgpu);
            //    para->cmdlist->IASetVertexBuffers(0, 1, &stVBV[1]);
            //    para->cmdlist->IASetIndexBuffer(&stIBV[1]);
            //    para->cmdlist->DrawIndexedInstanced(para->indices[1].size(), 1, 0, 0, 0);
            //     world = XMMatrixTranslationFromVector(XMVectorSet(0, 0, 0, 0));
            //     XMStoreFloat4x4(&objc.invTworld, XMMatrixTranspose(MathHelper::InverseTranspose(world)));
            //    XMStoreFloat4x4(&objc.world,XMMatrixTranspose( world));
            //    memcpy(objcbmapped[i*4+3], &objc, sizeof(objectconstant));
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), (8 + (i * 4)) * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    para->cmdlist->SetGraphicsRootDescriptorTable(5, currsrvgpu);
            //    para->cmdlist->IASetVertexBuffers(0, 1, &stVBV[2]);
            //    para->cmdlist->IASetIndexBuffer(&stIBV[2]);
            //    para->cmdlist->DrawIndexedInstanced(para->indices[2].size(), 1, 0, 0, 0);
            //    world = XMMatrixTranslationFromVector(XMVectorSet(0, 0, 0, 0));
            //    XMStoreFloat4x4(&objc.invTworld, XMMatrixTranspose(MathHelper::InverseTranspose(world)));
            //    XMStoreFloat4x4(&objc.world, XMMatrixTranspose(world));
            //    memcpy(objcbmapped[i * 4 + 4], &objc, sizeof(objectconstant));
            //    currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), (9 + (i * 4)) * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
            //    para->cmdlist->SetGraphicsRootDescriptorTable(5, currsrvgpu);
            //    para->cmdlist->IASetVertexBuffers(0, 1, &stVBV[3]);
            //    para->cmdlist->IASetIndexBuffer(&stIBV[3]);
            //    para->cmdlist->DrawIndexedInstanced(para->indices[3].size(), 1, 0, 0, 0);
            //}
         //   para->cmdlist->RSSetScissorRects(1, &stScissorRect);
         //   para->cmdlist->RSSetViewports(1, &stViewPort);
         //   /*ID3D12DescriptorHeap* cheaps[] = { pISRVCBVHp.Get(),pISampleHp.Get() };
         //   para->cmdlist->SetDescriptorHeaps(2, cheaps);*/
         ////   para->cmdlist->SetPipelineState(para->PSO);
         //   para->cmdlist->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(spheretexcube.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ));
         //    currrtvhandle=CD3DX12_CPU_DESCRIPTOR_HANDLE(para->rtvheap->GetCPUDescriptorHandleForHeapStart(), para->nCurrentFrameIndex * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
         //    CD3DX12_CPU_DESCRIPTOR_HANDLE currdsvhandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(pIDSVHeap->GetCPUDescriptorHandleForHeapStart());
         //   CD3DX12_GPU_DESCRIPTOR_HANDLE currsrvgpu;
         //   para->cmdlist->OMSetRenderTargets(1, &currrtvhandle, FALSE, &currdsvhandle);
         //   currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(),  para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
         //   para->cmdlist->SetGraphicsRootDescriptorTable(2, currsrvgpu);
         //  
         //   currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart());
         //   para->cmdlist->SetGraphicsRootDescriptorTable(0, currsrvgpu);
         //   currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 4*para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
         //   para->cmdlist->SetGraphicsRootDescriptorTable(4, currsrvgpu);
         //   XMMATRIX world =XMMatrixTranspose( XMMatrixTranslationFromVector(XMVectorSet(20.0f, 20.0f, 0, 0)));
         // 
         //   XMStoreFloat4x4(&objc.invTworld, XMMatrixTranspose(MathHelper::InverseTranspose(world)));
         //   XMStoreFloat4x4(&objc.world, world);
         //   memcpy(objcbmapped[0], &objc, sizeof(objectconstant));
         //  // memcpy(&mapped, &para->passc, sizeof(passconstant));
         //   currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 5 * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
         //   para->cmdlist->SetGraphicsRootDescriptorTable(5, currsrvgpu);
         //   currsrvgpu = CD3DX12_GPU_DESCRIPTOR_HANDLE(pISRVCBVHp->GetGPUDescriptorHandleForHeapStart(), 36 * para->device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
         //   para->cmdlist->SetGraphicsRootDescriptorTable(6, currsrvgpu);
         //   para->cmdlist->IASetVertexBuffers(0, 1, &stVBV[1]);
         //   para->cmdlist->IASetIndexBuffer(&stIBV[1]);
         //   para->cmdlist->DrawIndexedInstanced(para->indices[1].size(), 1, 0, 0, 0);
         //   para->cmdlist->Close();
            SetEvent(para->hEventRenderOver);
        }
        break;
        }
    }
    return 0;
}