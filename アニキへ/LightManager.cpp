#include "LightManager.h"
#include"Cube.h"
#include <iostream>

using namespace aetherClass;

LightManager::LightPropaty LightManager::m_lightpropaty[] = 
{
	{ Vector3(575, -442, 447) },
};

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}


std::shared_ptr<aetherClass::Cube>m_cubed;
void LightManager::Initialize()
{
	m_camera = std::make_shared<ViewCamera>();
	// Light‚Ì‰Šú‰»
	m_light = std::make_shared<Light>();
	m_light->property._translation = m_lightpropaty[0].m_changeLightTranslationArray;
	m_lightID = 0;
	m_light->property._translation = m_camera->property._translation;
	m_camera->property._translation = Vector3(575, -442, 447);
	m_light->property._translation._y -= 100;

	// MaterialShader‚Ì‰Šú‰»
	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._vertex._srcFile = L"Shader/MaterialVS.hlsl";
	desc._pixel._entryName = "ps_main";
	desc._pixel._srcFile = L"Shader/MaterialPS.hlsl";
	m_materialShader = std::make_shared<MaterialShader>();
	m_materialShader->Initialize(desc,ShaderType::eVertex|ShaderType::ePixel);
	m_materialShader->SetLight(m_light.get());
	m_materialShader->SetCamera(m_camera.get());

	m_cubed = std::make_shared<Cube>();
	m_cubed->Initialize();
	m_cubed->SetCamera(m_camera.get());
	m_cubed->property._transform._scale = 10;
	m_cubed->property._transform._translation = m_camera->property._translation;
	Material material;
	material._ambient._color = Color(1, 0, 1,1);
	material._diffuse._color = Color(1, 0, 1, 1);
	material._specular._color = Color(1, 0, 0, 1);
	material._specularPower = 4;// _color = Color(1, 0, 0, 1);
	m_cubed->property._material = material;
}

void LightManager::Render()
{
	m_camera->Render();
//	m_light->Translation() = m_lightpropaty[m_lightID].m_changeLightTranslationArray;
//	m_cubed->Render(m_materialShader.get());
	
}

void LightManager::Update()
{

		if (GameController::GetKey().IsKeyDown(DIK_RIGHT))
		{
			m_light->property._translation._x += 10;
		}
		if (GameController::GetKey().IsKeyDown(DIK_LEFT))
		{
			m_light->property._translation._x -= 10;
		}
		if (GameController::GetKey().IsKeyDown(DIK_UP))
		{
			m_light->property._translation._z -= 10;
		}
		if (GameController::GetKey().IsKeyDown(DIK_DOWN))
		{
			m_light->property._translation._z += 10;
		}
		m_cubed->property._transform._translation = m_light->property._translation;
		/*
		std::cout << "X : " << m_cubed->property._transform._translation._x << 
			" Y : " << m_cubed->property._transform._translation._y
			<< " Z : " << m_cubed->property._transform._translation._z << std::endl;
			*/
}

void LightManager::ChangeLight(int id)
{
	m_light->property._translation = m_lightpropaty[m_lightID].m_changeLightTranslationArray;
}

std::shared_ptr<Light> LightManager::GetLight(){
	return m_light;
}

