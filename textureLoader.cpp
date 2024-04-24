#include"textureLoader.h"
#include<string.h>
extern HANDLE g_hOutput;
bool textureLoader::GetTargetPixelFormat(const GUID* pSourceFormat, GUID* pTargetFormat) {
	*pTargetFormat = *pSourceFormat;
	for (size_t i = 0; i < _countof(g_WICConvert); ++i)
	{
		if (InlineIsEqualGUID(g_WICConvert[i].source, *pSourceFormat))
		{
			*pTargetFormat = g_WICConvert[i].target;
			return true;
		}
	}
	return false;

}
DXGI_FORMAT textureLoader::GetDXGIFormatFromPixelFormat(const GUID* pPixelFormat) {
	for (size_t i = 0; i < _countof(g_WICFormats); ++i)
	{
		if (InlineIsEqualGUID(g_WICFormats[i].wic, *pPixelFormat))
		{
			return g_WICFormats[i].format;
		}
	}
	return DXGI_FORMAT_UNKNOWN;
}
void textureLoader::LoadTextureFromFile(ID3D12Device4*device,ID3D12GraphicsCommandList*cmdlist, ID3D12CommandQueue* cmdQueue, WCHAR* filename, ID3D12Resource**texdefault,ID3D12Resource**texupload){
	// 16、使用WIC创建并加载一个2D纹理
//使用纯COM方式创建WIC类厂对象，也是调用WIC第一步要做的事情
	ThrowIfFailed(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory)));

	//使用WIC类厂对象接口加载纹理图片，并得到一个WIC解码器对象接口，图片信息就在这个接口代表的对象中了
	std::wstring file = filename;

	ThrowIfFailed(pIWICFactory->CreateDecoderFromFilename(
		file.c_str(),              // 文件名
		NULL,                            // 不指定解码器，使用默认
		GENERIC_READ,                    // 访问权限
		WICDecodeMetadataCacheOnDemand,  // 若需要就缓冲数据 
		&pIWICDecoder                    // 解码器对象
	));

	// 获取第一帧图片(因为GIF等格式文件可能会有多帧图片，其他的格式一般只有一帧图片)
	// 实际解析出来的往往是位图格式数据
	ThrowIfFailed(pIWICDecoder->GetFrame(0, &pIWICFrame));

	WICPixelFormatGUID wpf = {};
	//获取WIC图片格式
	ThrowIfFailed(pIWICFrame->GetPixelFormat(&wpf));
	GUID tgFormat = {};

	//通过第一道转换之后获取DXGI的等价格式
	if (GetTargetPixelFormat(&wpf, &tgFormat))
	{
		stTextureFormat = GetDXGIFormatFromPixelFormat(&tgFormat);
	}
	if (DXGI_FORMAT_UNKNOWN == stTextureFormat)
	{// 不支持的图片格式 目前退出了事 
		 // 一般 在实际的引擎当中都会提供纹理格式转换工具，
		 // 图片都需要提前转换好，所以不会出现不支持的现象
			ThrowIfFailed(S_FALSE);
	}
	assert(stTextureFormat != DXGI_FORMAT_UNKNOWN);
	// 定义一个位图格式的图片数据对象接口
	ComPtr<IWICBitmapSource>pIBMP;

	if (!InlineIsEqualGUID(wpf, tgFormat))
	{// 这个判断很重要，如果原WIC格式不是直接能转换为DXGI格式的图片时
	 // 我们需要做的就是转换图片格式为能够直接对应DXGI格式的形式
	 //创建图片格式转换器
		ComPtr<IWICFormatConverter> pIConverter;
		ThrowIfFailed(pIWICFactory->CreateFormatConverter(&pIConverter));

		//初始化一个图片转换器，实际也就是将图片数据进行了格式转换
		ThrowIfFailed(pIConverter->Initialize(
			pIWICFrame.Get(),                // 输入原图片数据
			tgFormat,						 // 指定待转换的目标格式
			WICBitmapDitherTypeNone,         // 指定位图是否有调色板，现代都是真彩位图，不用调色板，所以为None
			NULL,                            // 指定调色板指针
			0.f,                             // 指定Alpha阀值
			WICBitmapPaletteTypeCustom       // 调色板类型，实际没有使用，所以指定为Custom
		));
		// 调用QueryInterface方法获得对象的位图数据源接口
		ThrowIfFailed(pIConverter.As(&pIBMP));
	}
	else
	{
		//图片数据格式不需要转换，直接获取其位图数据源接口
		ThrowIfFailed(pIWICFrame.As(&pIBMP));
	}
	//获得图片大小（单位：像素）
	ThrowIfFailed(pIBMP->GetSize(&nTextureW, &nTextureH));
	assert(nTextureH != 0);
	assert(nTextureW != 0);
	//获取图片像素的位大小的BPP（Bits Per Pixel）信息，用以计算图片行数据的真实大小（单位：字节）
	ComPtr<IWICComponentInfo> pIWICmntinfo;
	ThrowIfFailed(pIWICFactory->CreateComponentInfo(tgFormat, pIWICmntinfo.GetAddressOf()));

	WICComponentType type;
	ThrowIfFailed(pIWICmntinfo->GetComponentType(&type));

	if (type != WICPixelFormat)
	{
		ThrowIfFailed(S_FALSE);
	}

	ComPtr<IWICPixelFormatInfo> pIWICPixelinfo;
	ThrowIfFailed(pIWICmntinfo.As(&pIWICPixelinfo));

	// 到这里终于可以得到BPP了，这也是我看的比较吐血的地方，为了BPP居然饶了这么多环节
	ThrowIfFailed(pIWICPixelinfo->GetBitsPerPixel(&nBPP));

	// 计算图片实际的行大小（单位：字节），这里使用了一个上取整除法即（A+B-1）/B ，
	// 这曾经被传说是微软的面试题,希望你已经对它了如指掌
	UINT nPicRowPitch = (uint64_t(nTextureW) * uint64_t(nBPP) + 7u) / 8u;
	//创建定位默认堆


	D3D12_HEAP_DESC stdefaultheapdesc = {};
	//为堆指定纹理图片至少2倍大小的空间，这里没有详细去计算了，只是指定了一个足够大的空间，够放纹理就行
	//实际应用中也是要综合考虑分配堆的大小，以便可以重用堆
	stdefaultheapdesc.SizeInBytes = GRS_UPPER(2 * nPicRowPitch * nTextureH, D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT);
	//指定堆的对齐方式，这里使用了默认的64K边界对齐，因为我们暂时不需要MSAA支持
	stdefaultheapdesc.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
	stdefaultheapdesc.Properties.Type = D3D12_HEAP_TYPE_DEFAULT;		//默认堆类型
	stdefaultheapdesc.Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	stdefaultheapdesc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	//拒绝渲染目标纹理、拒绝深度蜡板纹理，实际就只是用来摆放普通纹理
	stdefaultheapdesc.Flags = D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES | D3D12_HEAP_FLAG_DENY_BUFFERS;

	ThrowIfFailed(device->CreateHeap(&stdefaultheapdesc, IID_PPV_ARGS(&pIDefaultHeap)));


	//创建定位默认堆资源
	assert(stTextureFormat != NULL);
	D3D12_RESOURCE_DESC stTextureDesc = {};
	stTextureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	stTextureDesc.MipLevels = 1;
	stTextureDesc.Format = stTextureFormat; //DXGI_FORMAT_R8G8B8A8_UNORM;
	stTextureDesc.Width = nTextureW;
	stTextureDesc.Height = nTextureH;
	stTextureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	stTextureDesc.DepthOrArraySize = 1;
	stTextureDesc.SampleDesc.Count = 1;
	stTextureDesc.SampleDesc.Quality = 0;
	ThrowIfFailed(device->CreatePlacedResource(
		pIDefaultHeap.Get()
		, 0
		, &stTextureDesc			//可以使用CD3DX12_RESOURCE_DESC::Tex2D来简化结构体的初始化
		, D3D12_RESOURCE_STATE_COPY_DEST
		, nullptr
		, IID_PPV_ARGS(texdefault)));


	const UINT64 n64UploadBufferSize = GetRequiredIntermediateSize(*texdefault, 0, 1);
	//创建定位上传堆
	D3D12_HEAP_DESC stUploadheapdesc = {};
	stUploadheapdesc.SizeInBytes = GRS_UPPER(2 * n64UploadBufferSize, D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT);
	stUploadheapdesc.Alignment = 0;
	stUploadheapdesc.Properties.Type = D3D12_HEAP_TYPE_UPLOAD;
	stUploadheapdesc.Properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	stUploadheapdesc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	stUploadheapdesc.Flags = D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS;
	ThrowIfFailed(device->CreateHeap(&stUploadheapdesc, IID_PPV_ARGS(&pIUploadHeap)));

	//创建定位上传堆资源

	ThrowIfFailed(device->CreatePlacedResource(
		pIUploadHeap.Get()
		,0,
		&CD3DX12_RESOURCE_DESC::Buffer(n64UploadBufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(texupload)));



	
	void*accept= ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, n64UploadBufferSize);
	if (nullptr == accept)
	{
		throw (HRESULT_FROM_WIN32(GetLastError()));
	}
	//从图片中读取出数据
	ThrowIfFailed(pIBMP->CopyPixels(nullptr
		, nPicRowPitch
		, static_cast<UINT>(nPicRowPitch * nTextureH)   //注意这里才是图片数据真实的大小，这个值通常小于缓冲的大小
		, reinterpret_cast<BYTE*>(accept)));

	//获取默认堆的信息

	UINT64 n64RequiredSize = 0u;
	UINT   nNumSubresources = 1u;  //我们只有一副图片，即子资源个数为1
	D3D12_PLACED_SUBRESOURCE_FOOTPRINT stTxtLayouts = {};
	UINT64 n64TextureRowSizes = 0u;
	UINT   nTextureRowNum = 0u;

	D3D12_RESOURCE_DESC stDestDesc = (*texdefault)->GetDesc();

	device->GetCopyableFootprints(&stDestDesc
		, 0
		, nNumSubresources
		, 0
		, &stTxtLayouts
		, &nTextureRowNum
		, &n64TextureRowSizes
		, &n64RequiredSize);

	byte* mappeddata;
	(*texupload)->Map(0, NULL, reinterpret_cast<void**>(&mappeddata));//mappeddata和accept虽然都是一维数组，但accept数据是连续的，把图片每个信息都依次写入，
																   //但mappeddata要与defaultbuf的格式保持一致，即一张大于原始图片的二维表，但图片放在二维表的左上角或左上角加偏移，所以转化为一维数组不是连续的
	byte* srcslice =reinterpret_cast<byte*>(accept);
	byte* destslice = reinterpret_cast<byte*>(mappeddata) + stTxtLayouts.Offset;
	for (int i = 0;i < nTextureH;i++) {
		memcpy(destslice + i * static_cast<size_t>(stTxtLayouts.Footprint.RowPitch), srcslice + static_cast<size_t>(i * nPicRowPitch), nPicRowPitch);
	}
	(*texupload)->Unmap(0,NULL);

	::HeapFree(::GetProcessHeap(), 0, accept);
	
	//调用命令队列将数据copy进defaultbuf

	CD3DX12_TEXTURE_COPY_LOCATION Dst(*texdefault, 0);
	CD3DX12_TEXTURE_COPY_LOCATION Src(*texupload, stTxtLayouts);
	cmdlist->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);
	cmdlist->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(*texdefault, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));


	

}
