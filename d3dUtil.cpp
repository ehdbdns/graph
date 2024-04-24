
#include "d3dUtil.h"
#include <comdef.h>
#include <fstream>

using Microsoft::WRL::ComPtr;

DxException::DxException(HRESULT hr, const std::wstring& functionName, const std::wstring& filename, int lineNumber) :
    ErrorCode(hr),
    FunctionName(functionName),
    Filename(filename),
    LineNumber(lineNumber)
{
}

bool d3dUtil::IsKeyDown(int vkeyCode)
{
    return (GetAsyncKeyState(vkeyCode) & 0x8000) != 0;
}

ComPtr<ID3DBlob> d3dUtil::LoadBinary(const std::wstring& filename)
{
    std::ifstream fin(filename, std::ios::binary);

    fin.seekg(0, std::ios_base::end);
    std::ifstream::pos_type size = (int)fin.tellg();
    fin.seekg(0, std::ios_base::beg);

    ComPtr<ID3DBlob> blob;
    ThrowIfFailed(D3DCreateBlob(size, blob.GetAddressOf()));

    fin.read((char*)blob->GetBufferPointer(), size);
    fin.close();

    return blob;
}

Microsoft::WRL::ComPtr<ID3D12Resource> d3dUtil::CreateDefaultBuffer(
    ID3D12Device* device,
    ID3D12GraphicsCommandList* cmdList,
    const void* initData,
    UINT64 byteSize,
    Microsoft::WRL::ComPtr<ID3D12Resource>& uploadBuffer)
{
    ComPtr<ID3D12Resource> defaultBuffer;

    // Create the actual default buffer resource.
    ThrowIfFailed(device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(byteSize),
		D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        IID_PPV_ARGS(defaultBuffer.GetAddressOf())));

    // In order to copy CPU memory data into our default buffer, we need to create
    // an intermediate upload heap. 
    ThrowIfFailed(device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(byteSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(uploadBuffer.GetAddressOf())));


    // Describe the data we want to copy into the default buffer.
    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = initData;
    subResourceData.RowPitch = byteSize;
    subResourceData.SlicePitch = subResourceData.RowPitch;

    // Schedule to copy the data to the default buffer resource.  At a high level, the helper function UpdateSubresources
    // will copy the CPU memory into the intermediate upload heap.  Then, using ID3D12CommandList::CopySubresourceRegion,
    // the intermediate upload heap data will be copied to mBuffer.
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(), 
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
    UpdateSubresources<1>(cmdList, defaultBuffer.Get(), uploadBuffer.Get(), 0, 0, 1, &subResourceData);
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));

    // Note: uploadBuffer has to be kept alive after the above function calls because
    // the command list has not been executed yet that performs the actual copy.
    // The caller can Release the uploadBuffer after it knows the copy has been executed.


    return defaultBuffer;
}

ComPtr<ID3DBlob> d3dUtil::CompileShader(
	const std::wstring& filename,
	const D3D_SHADER_MACRO* defines,
	const std::string& entrypoint,
	const std::string& target)
{
	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = S_OK;

	ComPtr<ID3DBlob> byteCode = nullptr;
	ComPtr<ID3DBlob> errors;
	hr = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &errors);

	if(errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());

	ThrowIfFailed(hr);
    
	return byteCode;
}

std::wstring DxException::ToString()const
{
    // Get the string description of the error code.
    _com_error err(ErrorCode);
    std::wstring msg = err.ErrorMessage();

    return FunctionName + L" failed in " + Filename + L"; line " + std::to_wstring(LineNumber) + L"; error: " + msg;
}


int comparex(const void* a, const void* b)
{
    BVHtriangle first = *(BVHtriangle*)a;
    BVHtriangle second = *(BVHtriangle*)b;
    if (first.gravity.x < second.gravity.x)
        return -1;
    else
        return 1;
}
int comparey(const void* a, const void* b)
{
    BVHtriangle first = *(BVHtriangle*)a;
    BVHtriangle second = *(BVHtriangle*)b;
    if (first.gravity.y < second.gravity.y)
        return -1;
    else
        return 1;
}
int comparez(const void* a, const void* b)
{
    BVHtriangle first = *(BVHtriangle*)a;
    BVHtriangle second = *(BVHtriangle*)b;
    if (first.gravity.z < second.gravity.z)
        return -1;
    else
        return 1;
}

void BuildBoundingBox(BoundingBox& box, BVHtriangle* triangles, int faceCount) {
    XMFLOAT3 f3min = { +MathHelper::Infinity,+MathHelper::Infinity ,+MathHelper::Infinity };
    XMFLOAT3 f3max = { -MathHelper::Infinity,-MathHelper::Infinity ,-MathHelper::Infinity };
    XMVECTOR v3min = XMLoadFloat3(&f3min);
    XMVECTOR v3max = XMLoadFloat3(&f3max);
    for (int i = 0;i < faceCount;i++) {
        XMVECTOR p1 = XMLoadFloat3(&triangles[i].pos[0]);
        XMVECTOR p2 = XMLoadFloat3(&triangles[i].pos[1]);
        XMVECTOR p3 = XMLoadFloat3(&triangles[i].pos[2]);
        XMVECTOR mi = XMVectorMin(p1, p2);
        mi = XMVectorMin(p1, p3);
        v3min = XMVectorMin(v3min, mi);
        XMVECTOR ma = XMVectorMax(p1, p2);
        ma = XMVectorMax(p1, p3);
        v3max = XMVectorMax(v3max, ma);
    }
    XMStoreFloat3(&box.Center, 0.5f * (v3min + v3max));
    XMStoreFloat3(&box.Extents, 0.5f * (v3max - v3min));
}
BVHtree::BVHtree(std::vector<BVHtriangle>triangles) {
    head = new BVHnode(triangles, triangles.size());
    recurrence(head, 1);
}
void BVHtree::recurrence(BVHnode* node, int divtype) {
    if (!node->divide(divtype % 3))
        return;
    nodenum += 2;
    recurrence(node->left, divtype + 1);
    recurrence(node->right, divtype + 1);
}
BVHnode::BVHnode(std::vector<BVHtriangle> triList, int facecount) {
    faceCount = facecount;
    triangles = triList;

    for (int i = 0;i < faceCount;i++) {
        XMVECTOR v1 = XMLoadFloat3(&triangles[i].pos[0]);
        XMVECTOR v2 = XMLoadFloat3(&triangles[i].pos[1]);
        XMVECTOR v3 = XMLoadFloat3(&triangles[i].pos[2]);
        XMStoreFloat3(&triangles[i].gravity, (v1 + v2 + v3) / 3.0f);
    }
    BuildBoundingBox(box, triangles.data(), faceCount);
}
bool BVHnode::divide(int divType) {
    if (faceCount < 5)
        return false;
    if (divType == 0)
        qsort(triangles.data(), faceCount, sizeof(BVHtriangle), comparex);
    else if (divType == 1)
        qsort(triangles.data(), faceCount, sizeof(BVHtriangle), comparey);
    else
        qsort(triangles.data(), faceCount, sizeof(BVHtriangle), comparez);
    int centerIndex = faceCount / 2;
    std::vector<BVHtriangle>leftTri;
    std::vector<BVHtriangle>rightTri;
    leftTri.assign(&triangles[0], &triangles[centerIndex]);
    rightTri.assign(&triangles[centerIndex + 1], &triangles[faceCount-1]);
    left = new BVHnode(leftTri, leftTri.size());
    right = new BVHnode(rightTri, rightTri.size());
    return true;
}
void BVHtree:: rayIntersect(XMVECTOR rayOrigin, XMVECTOR rayDirection,BVHnode*node,float*tmin) {
   //tmin为最后要返回的最小距离
    float t = 0;//与包围盒的距离
    if (node->box.Intersects(rayOrigin, rayDirection,t)) {
        if (node->left == nullptr) {
            for (int i = 0;i < node->faceCount;i++) {
                XMVECTOR v0 = XMLoadFloat3(&node->triangles[i].pos[0]);
                XMVECTOR v1 = XMLoadFloat3(&node->triangles[i].pos[1]);
                XMVECTOR v2 = XMLoadFloat3(&node->triangles[i].pos[2]);
                float tm = 0;//与遍历到的三角形的距离
                if (TriangleTests::Intersects(rayOrigin, rayDirection, v0, v1, v2, tm)) {
                    if (tm < *tmin) {
                        *tmin = tm;
                      
                    }
                }
            }
        }
        
        else
        {
            rayIntersect(rayOrigin, rayDirection, node->left,&(*tmin));
            rayIntersect(rayOrigin, rayDirection, node->right,&(*tmin));
        }
     
    }
}