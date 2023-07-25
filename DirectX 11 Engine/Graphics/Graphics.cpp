#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	if (!InitializeDirectX(hwnd, width, height))
		return false;

	if (!InitializeShaders())
		return false;

	return true;
}

void Graphics::RenderFrame()
{
	float bgcolor[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
	this->swapchain->Present(1, NULL);
}

bool Graphics::InitializeDirectX(HWND hwnd, int width, int height)
{
	vector<AdapterData> adapters = AdapterReader::GetAdapters();

	//-- DXGI를 발견 하지 못했을 경우
	if (adapters.size() < 1)
	{
		ErrorLogger::Log("No DXGI Adapters found.");
		return false;
	}

	//--▼▼▼https://learn.microsoft.com/ko-kr/windows/win32/direct3d9/what-is-a-swap-chain
	//--SWAP_CHAIN 설정 방법 MS Dev
	//DESC : descripsion (설명서)
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = width;//--가로 (값을 넣어도 상관없음, 값대로 버퍼가 만들어짐.)
	scd.BufferDesc.Height = height;//--세로 (버퍼의 크기를 지정한다는것)

	scd.BufferDesc.RefreshRate.Numerator = 60;//--RefreshRate : 화면 갱신률(프레임) //분자
	scd.BufferDesc.RefreshRate.Denominator = 1;//--분모

	//--▼▼▼https://learn.microsoft.com/ko-kr/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format
	//--(float a = 0.0f~1.0f 로 0~255 가 정규화 되어있다고 생각하면된다)UNORM : Unsigned Normalize (정규화)
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//--https://learn.microsoft.com/ko-kr/previous-versions/windows/desktop/legacy/bb173067(v=vs.85)
	//이 값은 몰라도된다. (기본값을쓰겠다)
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//SCANLINE : 한줄 찍는것.

	//--https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173066(v=vs.85)
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1; //--MSAA(Multi Sampling Anti Aliasing)쓸꺼냐 ? 1, 0 이면 안쓴다는 옵션.
	scd.SampleDesc.Quality = 0;//--이미지중에 하나를 추출하는것을 SampleDesc 라고한다.
	//이미지중에 하나를 추출하는것을 SampleDesc 라고한다.
	/*
		픽셀이 적으면 계단현상이 나오는데 이것을 Aliasing이라고한다.
		그래서 그 계단현상을 없애려는 것이 Anti Aliasing이라고 한다.
		밑에 AA는 Anti Aliasing이다.
		SSAA//Super Sampling Anti Aliasing
		- 4배씩 늘리고 보정을 한 후 다시 줄인다. 그래서 선명하게 만든다.
		단점 : 비용이 너무 쎄다. 그래서 잘 안쓴다.

		MSAA//Multi Sampling Anti Aliasing (쓰레드에서 많이 쓰는 기법이다)
		- Anti Aliasing이 일어나는건 결국 테두리이다. 그래서 테두리를 잡고 보정을한다.
		단점 : 이것도 비용이 쎄다. 사용자가 이 기능을 킬 수 있게 옵션을 넣어 줄 수 있다.
	*/
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//--출력용 버퍼로 쓰겠다고 지정하는것.
	scd.BufferCount = 1;
	scd.OutputWindow = hwnd;//--여기다가 띄울 window창의 핸들을넣는다.
	scd.Windowed = TRUE;//--창모드쓸꺼냐 TRUE -> 창모드.(단 전체화면쓸꺼면 따로 옵션줘야함)
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//--스왑체인의 기본 정보.
	//--▲▲▲ https://learn.microsoft.com/en-us/previous-versions/windows/desktop/bb322816(v=vs.85)

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//--▲▲▲ https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_chain_flag

	HRESULT hr;
	//--https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdeviceandswapchain
	hr = D3D11CreateDeviceAndSwapChain(	adapters[0].pAdapter, //--IDXGI Adapter
										D3D_DRIVER_TYPE_UNKNOWN,//-- 드라이버 타임
										NULL, //--FOR SOFTWARE DRIVER TYPE
										NULL, //--디바이스 플래그
										NULL, //--피처레벨 배열
										0, //-- 피처레벨 카운트
										D3D11_SDK_VERSION,//--SDK 버전
										&scd, //-- 스왑체인 생성 구조체
										this->swapchain.GetAddressOf(), //-- 생성된 스왑체인 객체
										this->device.GetAddressOf(), //-- 생성된 디바이스 객체
										NULL, //-- 생성된 피처레벨 정보
										this->deviceContext.GetAddressOf()); //-- 생성된 디바이스 컨텍스트 객체

	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create device and swapchain. ");
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = this->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hr)) //If error occurred
	{
		ErrorLogger::Log(hr, "GetBuffer Failed.");
		return false;
	}

	hr = this->device->CreateRenderTargetView(backBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());
	if (FAILED(hr)) //If error occurred
	{
		ErrorLogger::Log(hr, "Failed to create render target view.");
		return false;
	}

	this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), NULL);
	//--▲▲▲ https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-omsetrendertargets
	//--랜더링 대상 수, 랜더타겟뷰의 포인터, 깊이 버퍼의 포인터
	return true;
}

bool Graphics::InitializeShaders()
{
	wstring shaderfolder;
#pragma region DetermineShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef  _DEBUG //--Debug Mode
#ifdef _WIN64 //--x64
		shaderfolder = L"x64\\Debug";
#else //--x86 (Win32)
		shaderfolder = L"Debug\\";
#endif
#else //--Release Mode
#ifdef _WIN64 //--x64
		shaderfolder = L"x64\\Release\\";
#else	//--x86 (Win32)
		shaderfolder = L"Release\\";
#endif // _WIN64 //--x64


#endif // DEBUG
	}

		if (!vertexshader.Initialize(this->device, L"x64\\Debug\\VertexShader.cso"))
			return false;

		//--▼▼▼ https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ns-d3d11-d3d11_input_element_desc
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0  },
		};
		//--DXGI_FORMAT_R32G32B32_FLOAT 
		//--▲▲▲ https://learn.microsoft.com/ko-kr/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format

		UINT numElements = ARRAYSIZE(layout);

		HRESULT hr = this->device->CreateInputLayout(layout, numElements, this->vertexshader.GetBuffer()->GetBufferPointer(), this->vertexshader.GetBuffer()->GetBufferSize(), this->inputLayout.GetAddressOf());
		if (FAILED(hr))
		{
			ErrorLogger::Log(hr, "Failed to create input layout.");
			return false;
		}
		return true;
	}