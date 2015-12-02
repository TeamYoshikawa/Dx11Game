#ifndef _SHADERBASE_H
#define _SHADERBASE_H
#include <D3D11.h>
#include <d3dx10math.h>
#include <D3DX11async.h>
#include <fstream>
namespace DxShader{

	class ShaderBase
	{
	
		public:
			ShaderBase();
			ShaderBase(ShaderBase&);
			~ShaderBase();
			bool Initialize(ID3D11Device*, HWND, std::wstring vs, std::wstring ps);
			void Shutdown();
			bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
			bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);
		protected:
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

		protected:
			void OutputShaderErrorMessage(ID3D10Blob*, HWND, std::wstring);

		protected:
			ID3D11VertexShader* m_vertexShader;
			ID3D11PixelShader* m_pixelShader;
			ID3D11InputLayout* m_layout;
			ID3D11Buffer* m_matrixBuffer;

		private:
			
			virtual bool InitializeShader(ID3D11Device*, HWND, std::wstring, std::wstring) = 0;
			virtual void ShutdownShader() = 0;
			virtual void RenderShader(ID3D11DeviceContext*, int) = 0;

			virtual bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX){ return true; }
			virtual bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*){ return true; }
	};

}

#endif