#ifndef _TEXTURESHADER_H
#define _TEXTURESHADER_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
namespace Shader{

	class TextureShader
	{
		private:
			struct MatrixBufferType
			{
				MatrixBufferType(){
					SecureZeroMemory(&_world, sizeof(_world));
					SecureZeroMemory(&_view, sizeof(_view));
					SecureZeroMemory(&_projection, sizeof(_projection));
				}
				MatrixBufferType(MatrixBufferType&) = default;
				~MatrixBufferType() = default;

				D3DXMATRIX _world, _view, _projection;
			};

		public:
			TextureShader();
			TextureShader(TextureShader&);
			~TextureShader();
			bool Initialize(ID3D11Device*, HWND,std::wstring vs,std::wstring ps);
			void Shutdown();
			bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
			ID3D11InputLayout* GetInputLayout();
		private:
			bool InitializeShader(ID3D11Device*, HWND, std::wstring, std::wstring);
			void ShutdownShader();
			void OutputShaderErrorMessage(ID3D10Blob*, HWND, std::wstring);

			bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
			void RenderShader(ID3D11DeviceContext*, int);

		private:
			ID3D11VertexShader* m_vertexShader;
			ID3D11PixelShader* m_pixelShader;
			ID3D11InputLayout* m_layout;
			ID3D11Buffer* m_matrixBuffer;

			ID3D11SamplerState* m_samplerState;
	};	
}

#endif