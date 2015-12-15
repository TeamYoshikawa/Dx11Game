#ifndef _TEXTURESHADER_H
#define _TEXTURESHADER_H

#include "ShaderBase.h"
namespace DxShader{

	class TextureShader :
		public ShaderBase
	{

		public:
			TextureShader();
			TextureShader(TextureShader&);
			~TextureShader();

			ID3D11InputLayout* GetInputLayout();
		private:
			bool InitializeShader(ID3D11Device*, HWND, std::wstring, std::wstring)override;
			void ShutdownShader()override;

			bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*)override;
			void RenderShader(ID3D11DeviceContext*, int)override;

		private:
			ID3D11SamplerState* m_samplerState;
	};	
}

#endif