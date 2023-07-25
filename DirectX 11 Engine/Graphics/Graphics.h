#pragma once
#include "AdapterReader.h"
#include "Shaders.h"

using namespace std;

class Graphics
{
public: 
	bool Initialize(HWND hwnd, int width, int height);
	void RenderFrame();
private:
	bool InitializeDirectX(HWND hwnd, int width, int height);
	bool InitializeShaders();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	//--Microsoft::WRL::ComPtr¿Ã∂ı?
	//--https://dlemrcnd.tistory.com/48
	//--https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=websearch&logNo=221166428102
	
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	VertexShader vertexshader;
};

