#include "SoumatouManager.h"
#include "Texture.h"
#include "PixelShader.h"
#include <iostream>
#include <GameController.h>

using namespace aetherClass;
SoumatouManager::SoumatouManager()
{
}


SoumatouManager::~SoumatouManager()
{
}

bool SoumatouManager::Initialize(){

	damage_flag = false;

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


	m_sound = std::make_shared<GameSound>();
	m_sound->Load("Sound/soumatou.wav");
	m_sound->SetValume(-1000);
	


	m_soumaTexture = std::make_shared<Texture>();

	bool hoge;


	m_soumaTexture->Load("Texture/soumatou.png");/*âÊëúÇÃì«Ç›çûÇ›*/

	m_soumatou = std::make_shared<Rectangle2D>();
	m_soumatou->Initialize();
	m_soumatou->property._transform._translation = Vector3(0.0f, 0.0f, 0.0f);
	m_soumatou->property._color = Color(0.8f, 0.6f, 0.4f, 0.6f);
	m_soumatou->property._transform._scale._x = 800;
	m_soumatou->property._transform._scale._y = 600;
	m_soumatou->SetTexture(m_soumaTexture.get());


	m_damage = std::make_shared<Rectangle2D>();
	m_damage->Initialize();
	m_damage->property._transform._translation = Vector3(0.0f, 0.0f, 0.0f);
	m_damage->property._color = Color(1.0f, 0.0f, 0.0f, 0.6f);
	m_damage->property._transform._scale._x = 800;
	m_damage->property._transform._scale._y = 600;
	m_damage->SetTexture(m_soumaTexture.get());
	
	m_countDown = 150;
	m_pressCount = 0;
	m_eEvent == eEvent::eNomal;
	
	return true;
}

void SoumatouManager::Update(){

	if (GameController::GetKey().IsKeyDown(DIK_SPACE)){
		m_sound->PlayToOneTime();
		flag = true;
	}
	
	if (flag==true){
		m_countDown--;
	}
	if (m_countDown < 0){
		m_pressCount += 1;
		m_countDown = 150;
		flag = false;
	}


}

void SoumatouManager::DamageFlagTrue(){
	damage_flag = true;
}

void SoumatouManager::DamageFlagFalse(){
	damage_flag = false;
}

int SoumatouManager::SoumatouGet(){
	return m_pressCount;
}
void SoumatouManager::SoumatouSet(int Set){
	m_pressCount=Set;
}

int SoumatouManager::DamageGet(){
	return m_damageCount;
}

void SoumatouManager::DamageSet(int damage){
	m_damageCount = damage;
}

void SoumatouManager::Render(){
	
	if (damage_flag){
		//std::cout << "hiromu";
		m_damage->Render(m_pixelShader.get());
	}
	
	if (flag == true){
		m_soumatou->Render(m_pixelShader.get());
	}

}