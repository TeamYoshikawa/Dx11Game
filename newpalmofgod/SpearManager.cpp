#include"SpearManager.h"
#include<iostream>
#include"PixelShader.h"

using namespace aetherClass;
using namespace n_Spear;


std::shared_ptr<PixelShader>m_shader;
bool SpearManager::Initialize(ViewCamera *camera)
{
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
		
		m_spear[i]->GetTransform()._scale = Vector3(15.0f, 100.0f, 15.0f);
		m_spear[i]->GetTransform()._rotation = Vector3(90.0f, 0.0f, 0.0f);

	}
	
	m_spear[0]->GetTransform()._translation = Vector3(8622.0f, 100.0f, 2212.0f);
	m_spear[1]->GetTransform()._translation = Vector3(8722.0f, 100.0f, 2212.0f);
	m_spear[2]->GetTransform()._translation = Vector3(8822.0f, 100.0f, 2212.0f);

	m_spearRender = std::make_shared<SpearRender>();

	m_spearUpdater = std::make_shared<SpearUpdater>();
	
	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("ModelData/Textures/cocoa.jpg");
	m_switch = std::make_shared<Cube>();
	m_switch->Initialize();
	if (!m_switch->Initialize()){
		return false;
	}
	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());
	m_switch->GetTransform()._translation = Vector3(8722.0f, -80.0f, 634.0f);
	m_switch->GetTransform()._scale = Vector3(10.0f, 10.0f, 10.0f);

	m_a = std::make_shared<Texture>();
	m_a->Load("ModelData/Textures/button.jpg");

	m_aaa = std::make_shared<Cube>();
	m_aaa->Initialize();
	m_aaa->SetCamera(camera);
	m_aaa->SetTexture(m_a.get());
	m_aaa->GetTransform()._translation = Vector3(8722.0f, -80.0f, 434.0f);
	m_aaa->GetTransform()._scale = Vector3(100.0f, 100.0f, 50.0f);

	m_spearEvent = eSpearEvent::eChecking;
	return true;
}

void SpearManager::Render(const std::shared_ptr<aetherClass::ShaderBase>shader)
{	

	for (int i = 0; i < 3; i++){
		m_spearRender->Renderring(m_spear[i].get(), shader);
	}
	m_spearRender->Renderring(m_switch.get(), shader);
	m_switch->Render(shader.get());
	//m_aaa->Render(shader.get());
}

void SpearManager::Update()
{
	/*GameController::GetMouse().Frame();
	rayDirection = GameController::GetMouse().GetDirection(); *///GetMouseDirection(*m_camera, 800, 600);
	
	if (GameController::GetKey().IsKeyDown(DIK_DOWN)){
		m_switch->GetTransform()._translation._z-= 1.0f;
	}

	if (m_spearEvent == eSpearEvent::eChecking){
		if (aetherFunction::CollideBoxOBB(*m_switch, *m_aaa)){
			m_spearEvent = eSpearEvent::eStart;
			m_spearUpdater->FlagOn();
			std::cout << "hit" << std::endl;
		}
	}
	else{
		for (int i = 0; i < 3; i++){
			m_spearUpdater->Updating(m_spear[i].get());
		}
	}
	if (s_flag == SET){
		m_spearEvent = eSpearEvent::eChecking;
		m_spearUpdater->FlagOff();
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
	return m_spear[1];
}

int SpearManager::FlagGet()
{
	return m_spearUpdater->FlagGet();
}