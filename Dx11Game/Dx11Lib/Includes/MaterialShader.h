#ifndef _MATERIALSHADER_H
#define _MATERIALSHADER_H
#include "ShaderBase.h"

namespace DxShader{
	class MaterialShader :
		public ShaderBase
	{
		public:
			MaterialShader();
			MaterialShader(MaterialShader&);
			~MaterialShader();
			ID3D11InputLayout* GetInputLayout();
		private:
			bool InitializeShader(ID3D11Device*, HWND, std::wstring, std::wstring)override;
			void ShutdownShader()override;
			void RenderShader(ID3D11DeviceContext*, int)override;

			bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX)override;

		private:
			ID3D11SamplerState* m_samplerState;
			ID3D11Buffer* m_materialShaderBuffer;
	};

}

#endif