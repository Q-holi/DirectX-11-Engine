#pragma once
#include"..\\ErrorLogger.h"
#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

using namespace std;

class VertexShader
{
public :
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, wstring shaderpath);
	ID3D11VertexShader* GetShader(); 
	ID3D10Blob* GetBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer = nullptr;

};

