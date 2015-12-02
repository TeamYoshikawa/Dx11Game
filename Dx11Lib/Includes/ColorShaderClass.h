#ifndef _COLORSHADERCLASS_H
#define _COLORSHADERCLASS_H

#include "ShaderBase.h"
namespace DxShader{
	class ColorShaderClass :
		public ShaderBase
	{

	
	public:
		ColorShaderClass();
		ColorShaderClass(const ColorShaderClass&);
		~ColorShaderClass();

	private:

		bool InitializeShader(ID3D11Device*, HWND, std::wstring, std::wstring)override;
		void ShutdownShader()override;

		bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX)override;

		void RenderShader(ID3D11DeviceContext*, int)override;
	};


}

#endif