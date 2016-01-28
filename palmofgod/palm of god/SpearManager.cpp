#include"SpearManager.h"
#include<iostream>
#include"PixelShader.h"

using namespace aetherClass;
using namespace n_Spear;


std::shared_ptr<PixelShader>m_shader;
bool SpearManager::Initialize(ViewCamera *camera)
{

	m_shader = std::make_shared<PixelShader>();
	ShaderDesc materialDesc;
	materialDesc._vertex._entryName = "vs_main";
	materialDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";

	materialDesc._pixel._entryName = "ps_main";
	materialDesc._pixel._srcFile = L"Shader/BasicColor.ps";
	m_shader->Initialize(materialDesc, ShaderType::eVertex | ShaderType::ePixel);
	


	m_camera = camera;

	m_spearTexture = std::make_shared<Texture>();
	m_spearTexture->Load("ModelData/Textures/tex.png");
	for (int i = 0; i < 3; i++){
		
		m_spear[i] = std::make_shared<Cube>();
		m_spear[i]->Initialize();
		if (!m_spear[i]->Initialize()){
			return false;
		}
		m_spear[i]->SetCamera(camera);
		m_spear[i]->SetTexture(m_spearTexture.get());
		
		m_spear[i]->GetTransform()._scale = Vector3(15.0f, 105.5f, 20.0f);
	}
	
	m_spear[0]->GetTransform()._translation = Vector3(8622.0f, 1000.0f, 1352.0f);
	m_spear[1]->GetTransform()._translation = Vector3(8722.0f, 1000.0f, 1352.0f);
	m_spear[2]->GetTransform()._translation = Vector3(8822.0f, 1000.0f, 1352.0f);

	m_spearRender = std::make_shared<SpearRender>();

	m_spearUpdater = std::make_shared<SpearUpdater>();
	
	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("ModelData/Textures/button.jpg");
	m_switch = std::make_shared<Sphere>(2,10,10);
	m_switch->Initialize();
	if (!m_switch->Initialize()){
		return false;
	}
	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());
	m_switch->GetColor() = Color(1.0, 1.0, 0.0, 1.0);
	m_switch->GetTransform()._translation = Vector3(8775.0f, -120.0f, 434.0f);
	

	m_switchType = false;

	return true;
}

void SpearManager::Render(const std::shared_ptr<aetherClass::ShaderBase>shader)
{	

	for (int i = 0; i < 3; i++){
		m_spearRender->Renderring(m_spear[i].get(), shader);
	}
	m_spearRender->Renderring(m_switch.get(), shader);
	m_switch->Render(m_shader.get());
	m_switchType = GameController::GetPointer()->IsLeftButtonTrigger() ? true : false;
}

void SpearManager::Update()
{
	GameController::GetPointer()->Frame();
	rayDirection = GameController::GetPointer()->GetMouseDirection(*m_camera, 800, 600);
	
	
		m_switchType = GameController::GetPointer()->IsLeftButtonTrigger() ? true : false;
		if (m_switchType){
			m_switchType != m_switchType;
		}
		else{
			m_switchType = false;
		}
	

	for (int i = 0; i < 3; i++){
		m_spearUpdater->Updating(m_spear[i].get(), m_switchType);
	}
	
}



void SpearManager::Shutdown()
{
	for (int i = 0; i < 3; i++){
		m_spear[i].get()->Finalize();
	}
	m_switch.get()->Finalize();
}

std::shared_ptr<ModelBase>SpearManager::Get()
{
	return m_spear[0],m_spear[1],m_spear[2];
}