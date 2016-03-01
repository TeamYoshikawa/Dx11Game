#include "SoumatouManager.h"
#include "Texture.h"
#include "PixelShader.h"
#include <iostream>

using namespace aetherClass;
SoumatouManager::SoumatouManager()
{
}


SoumatouManager::~SoumatouManager()
{
}

bool SoumatouManager::Initialize(){

	ShaderDesc textureDesc;
	textureDesc._pixel._srcFile = L"Shader/Transparent.ps";
	textureDesc._pixel._entryName = "ps_main";

	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	textureDesc._vertex._entryName = "vs_main";

	m_pixelShader = std::make_shared<PixelShader>();
	m_pixelShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	/*textureDesc._pixel._srcFile = L"Shader/ColorTexture.ps";
	m_colorShader = std::make_shared<PixelShader>();
	m_colorShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);*/


	m_soumaTexture = std::make_shared<Texture>();

	bool hoge;


	hoge=m_soumaTexture->Load("Texture/soumatou.png");	/*‰æ‘œ‚Ì“Ç‚İ‚İ*/

	
	m_soumatou = std::make_shared<Rectangle2D>();
	m_soumatou->Initialize();
	m_soumatou->property._transform._translation = Vector3(0.0f, 0.0f, 0.0f);
	m_soumatou->property._color = Color(0.0f, 0.0f, 1.0f, 1.0f);
	m_soumatou->property._transform._scale._x = 800;
	m_soumatou->property._transform._scale._y = 600;
	m_soumatou->SetTexture(m_soumaTexture.get());
	
	return true;
}

void SoumatouManager::Render(){
	std::cout << "hiroki";
	m_soumatou->Render(m_pixelShader.get());
	//m_soumatou->Render(m_colorShader.get());

}