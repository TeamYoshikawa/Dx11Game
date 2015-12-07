#ifndef _COLORSHADER_H
#define _COLORSHADER_H

#include "ShaderBase.h"
namespace DxShader{
	class  ColorShader :
		public ShaderBase
	{

	
	public:
		ColorShader();
		ColorShader(const ColorShader&);
		~ColorShader();

	private:

		bool InitializeShader(ID3D11Device*, HWND, std::wstring, std::wstring)override;
		void ShutdownShader()override;

		bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX)override;

		void RenderShader(ID3D11DeviceContext*, int)override;
	};


}

#endif