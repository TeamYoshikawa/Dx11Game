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
	m_light->Translation() = m_lightpropaty[0].m_changeLightTranslationArray;
	m_lightID = 0;
	m_light->Translation() = m_camera->Translation();
	m_camera->Translation() = Vector3(575, -442, 447);
	m_light->Translation()._y -= 100;

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
	m_cubed->GetTransform()._scale = 10;
	m_cubed->GetTransform()._translation = m_camera->Translation();
	Material material;
	material._ambient._color = Color(1, 0, 0,1);
	material._diffuse._color = Color(1, 0, 0, 1);
	material._specular._color = Color(1, 0, 0, 1);
	material._specularPower = 4;// _color = Color(1, 0, 0, 1);
	m_cubed->GetMaterial() = material;
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
			m_light->Translation()._x += 10;
		}
		if (GameController::GetKey().IsKeyDown(DIK_LEFT))
		{
			m_light->Translation()._x -= 10;
		}
		if (GameController::GetKey().IsKeyDown(DIK_UP))
		{
			m_light->Translation()._z -= 10;
		}
		if (GameController::GetKey().IsKeyDown(DIK_DOWN))
		{
			m_light->Translation()._z += 10;
		}
		m_cubed->GetTransform()._translation = m_light->Translation();
		/*
		std::cout << "X : " << m_cubed->GetTransform()._translation._x << 
			" Y : " << m_cubed->GetTransform()._translation._y
			<< " Z : " << m_cubed->GetTransform()._translation._z << std::endl;
			*/
}

void LightManager::ChangeLight(int id)
{
	m_light->Translation() = m_lightpropaty[m_lightID].m_changeLightTranslationArray;
}

std::shared_ptr<Light> LightManager::GetLight(){
	return m_light;
}

