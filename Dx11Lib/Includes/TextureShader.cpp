#include "TextureShader.h"
#define DX_RELEASE(x) {x->Release(); x = nullptr;}

namespace Shader{
	TextureShader::TextureShader(){
		m_vertexShader = nullptr;
		m_pixelShader = nullptr;
		m_matrixBuffer = nullptr;
		m_samplerState = nullptr;
		m_layout = nullptr;
	}
	TextureShader::TextureShader(TextureShader& other){}

	TextureShader::~TextureShader()
	{
	}

	bool TextureShader::Initialize(ID3D11Device* device, HWND hWnd,std::wstring vs,std::wstring ps){

		bool result;

		// Intialize the vertex and pixel shaders
		result = InitializeShader(device, hWnd, vs, ps);
		if (!result)
		{
			return false;
		}

		return true;
	}
	
	void TextureShader::Shutdown(){
		// Shutdown the vertex and pixel shaders as well as the related objects
		ShutdownShader();
		return;
	}

	bool TextureShader::Render(ID3D11DeviceContext* deviceContext, int indexCount,
		D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture){
		bool result = true;
		// Set the shader paramaters that it will use for rendering
		result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture);
		if (!result)
		{
			return false;
		}

		// Now render the prepared buffers with the shader
		RenderShader(deviceContext, indexCount);
		
		return true;
	}

	bool TextureShader::InitializeShader(ID3D11Device* device, HWND hWnd,
		std::wstring vsFileName, std::wstring psFileName){
		HRESULT result;
		ID3D10Blob* errorMessage;
		ID3D10Blob* vertexShaderBuffer;
		ID3D10Blob* pixelShaderBuffer;
		D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
		unsigned int numElements;
		D3D11_BUFFER_DESC matrixBufferDesc;
		D3D11_SAMPLER_DESC samplerDesc;

		errorMessage = nullptr;
		vertexShaderBuffer = nullptr;
		pixelShaderBuffer = nullptr;

		result = D3DX11CompileFromFile(vsFileName.c_str(), NULL, NULL, "main", "vs_5_0",
			D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);

		

		if (FAILED(result))
		{ 
			if (errorMessage)
			{
				OutputShaderErrorMessage(errorMessage, hWnd, vsFileName);
			}
			else
			{
				MessageBox(hWnd, vsFileName.c_str(), L"Missing Shader File", MB_OK);
			}
			return false;
		}

	

		result = D3DX11CompileFromFile(psFileName.c_str(), NULL, NULL, "main", "ps_5_0",
			D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);

		if (FAILED(result))
		{
			
			if (errorMessage)
			{
				OutputShaderErrorMessage(errorMessage, hWnd, psFileName);
			}
			else
			{
				MessageBox(hWnd, psFileName.c_str(), L"Missing Shader File", MB_OK);
			}
			return false;
		}


		result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
		if (FAILED(result))
		{
			
			return false;
		}

		result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
		if (FAILED(result))
		{
			
			return false;
		}

		polygonLayout[0].SemanticName = "POSITION";
		polygonLayout[0].SemanticIndex = 0;
		polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[0].InputSlot = 0;
		polygonLayout[0].AlignedByteOffset = 0;
		polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[0].InstanceDataStepRate = 0;

		polygonLayout[1].SemanticName = "TEXCOORD";
		polygonLayout[1].SemanticIndex = 0;
		polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		polygonLayout[1].InputSlot = 0;
		polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[1].InstanceDataStepRate = 0;

		numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

		result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),&m_layout);
		if (FAILED(result))
		{
			return false;
		}
		DX_RELEASE(vertexShaderBuffer);
		DX_RELEASE(pixelShaderBuffer);

		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;

		result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
		if (FAILED(result))
		{
			return false;
		}

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		result = device->CreateSamplerState(&samplerDesc, &m_samplerState);
		if (FAILED(result))
		{
			return false;
		}
		return true;
	}

	void TextureShader::ShutdownShader(){
		if (m_samplerState)
		{
			DX_RELEASE(m_samplerState);
		}

		if (m_matrixBuffer)
		{
			DX_RELEASE(m_matrixBuffer);
		}

		if (m_layout)
		{
			DX_RELEASE(m_layout);
		}

		if (m_pixelShader)
		{
			DX_RELEASE(m_pixelShader);
		}

		if (m_vertexShader)
		{
			DX_RELEASE(m_vertexShader);
		}
		return;
	}

	void TextureShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hWnd, std::wstring shaderFileName){
		char* compileErrors;
		unsigned long bufferSize;
		std::ofstream fout;

		compileErrors = (char*)(errorMessage->GetBufferPointer());

		bufferSize = errorMessage->GetBufferSize();

		fout.open("shader-error.txt");

		for (int i = 0; i < bufferSize; i++)
		{
			fout << compileErrors[i];
		}

		fout.close();

		DX_RELEASE(errorMessage);

		MessageBox(hWnd, L"Error compiling shader. Check shader-error.txt for message",shaderFileName.c_str(), MB_OK);

		return;
	}

	bool TextureShader::SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
		D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture){
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		MatrixBufferType* matrixDataPtr;
		unsigned int bufferNumber;

		D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
		D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
		D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

		result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			return false;
		}
		
		matrixDataPtr = (MatrixBufferType*)mappedResource.pData;

		matrixDataPtr->_world = worldMatrix;
		matrixDataPtr->_view = viewMatrix;
		matrixDataPtr->_projection = projectionMatrix;

		deviceContext->Unmap(m_matrixBuffer, 0);

		bufferNumber = 0;

		deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

		deviceContext->PSSetShaderResources(0, 1, &texture);

		return true;
	}

	void TextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount){

		deviceContext->IASetInputLayout(m_layout);

		deviceContext->VSSetShader(m_vertexShader, NULL, 0);
		deviceContext->PSSetShader(m_pixelShader, NULL, 0);

		deviceContext->PSSetSamplers(0, 1, &m_samplerState);
		deviceContext->DrawIndexed(indexCount, 0, 0);

		return;
	}

	ID3D11InputLayout* TextureShader::GetInputLayout(){
		return m_layout;
	}
}
