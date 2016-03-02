#include"SpearManager.h"
#include"PlayerManager.h"
#include<iostream>


using namespace aetherClass;
using namespace n_Spear;



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
		
		m_spear[i]->property._transform._scale = Vector3(15.0f, 100.0f, 15.0f);
		m_spear[i]->property._transform._rotation = Vector3(90.0f, 0.0f, 0.0f);

	}
	
	m_spear[0]->property._transform._translation = Vector3(8622.0f, 100.0f, 3212.0f);
	m_spear[1]->property._transform._translation = Vector3(8692.0f, 100.0f, 3212.0f);
	m_spear[2]->property._transform._translation = Vector3(8762.0f, 100.0f, 3212.0f);

	m_spearRender = std::make_shared<SpearRender>();

	m_spearUpdater = std::make_shared<SpearUpdater>();
	
	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("ModelData/Textures/button.jpg");
	m_switch = std::make_shared<Cube>();
	m_switch->Initialize();
	if (!m_switch->Initialize()){
		return false;
	}
	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());
	m_switch->property._transform._translation = Vector3(8722.0f, -80.0f, 954.0f);
	m_switch->property._transform._scale = Vector3(250.0f, 200.0f, 50.0f);

	m_spearEvent = eSpearEvent::eChecking;
	return true;
}

void SpearManager::Render(const std::shared_ptr<aetherClass::ShaderBase>shader)
{	

	for (int i = 0; i < 3; i++){
		m_spearRender->Renderring(m_spear[i].get(), shader);
	}
	//m_spearRender->Renderring(m_switch.get(), shader);
	//m_switch->Render(shader.get());

}

void SpearManager::Update()
{
	/*GameController::GetMouse().Frame();
	rayDirection = GameController::GetMouse().GetDirection(); *///GetMouseDirection(*m_camera, 800, 600);
	
	spear_flag = m_spearUpdater->FlagGet();

	if (m_spearEvent == eSpearEvent::eChecking){
	
			m_spearEvent = eSpearEvent::eStart;
			m_spearUpdater->FlagOn();
			
	}
	else{
		for (int i = 0; i < 3; i++){
			m_spearUpdater->Updating(m_spear[i].get());
		}
	}
	if (spear_flag == SET){
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
	return m_spear[0], m_spear[1], m_spear[2];
}

std::shared_ptr<aetherClass::ModelBase> SpearManager::S_Get(){

	return m_switch;
}

bool SpearManager::HitMesh(std::shared_ptr<ModelBase>& player, std::shared_ptr<ModelBase>& other){

	if (!m_spearUpdater->HittingProcessor(player, other))
	{
		return false;
	}

	return true;
}

int SpearManager::FlagGet()
{
	return m_spearUpdater->FlagGet();
}