#pragma once
#include "ShaderBase.h"
#include"Texture.h"
#include"Vector4.h"
#include"Light.h"
namespace DxShader{
	class LightShader :
		public ShaderBase
	{
	private:
		struct LightBuffer{
			DxMath::Vector4 _light;
		};
		
		ID3D11Buffer* m_lightBuffer;
		ID3D11SamplerState* m_samplerState;

		DxLight::Light* m_light;
	public:
		LightShader();
		LightShader(const LightShader&);
		~LightShader();

		void SetLight(DxLight::Light*);
		bool InitializeShader(ID3D11Device*, HWND, std::wstring, std::wstring)override;
		void ShutdownShader()override;

		bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*)override;

		void RenderShader(ID3D11DeviceContext*, int)override;
	};

}