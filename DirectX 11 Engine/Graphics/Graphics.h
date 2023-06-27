#pragma once
#include "AdapterReader.h"

using namespace std;

class Graphics
{
public: 
	bool Initialize(HWND hwnd, int width, int height);
private:
	bool InitializeDirectX(HWND hwnd, int width, int height);

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	//--Microsoft::WRL::ComPtr¿Ã∂ı?
	//--https://dlemrcnd.tistory.com/48
	//--https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=websearch&logNo=221166428102
};

