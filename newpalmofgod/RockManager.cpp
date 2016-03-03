#include "RockManager.h"
#include "PlayerManager.h"
#include <iostream>

using namespace aetherClass;
using namespace n_Rock;


bool RockManager::Initialize(ViewCamera* camera){

	m_rockTexture = std::make_shared<Texture>();
	m_rockTexture->Load("ModelData/textures/seafloor.dds");

	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("goal.png");

	for (i = 0; i < r_max; i++){
		m_Rock[i] = std::make_shared<Sphere>(10, 10);
		if (!m_Rock[i]->Initialize()){
			return false;
		}
	}

	m_switch = std::make_shared<Cube>();
	if (!m_switch->Initialize()){
		return false;
	}


	for (i = 0; i < r_max; i++){
		m_Rock[i]->SetCamera(camera);
		m_Rock[i]->SetTexture(m_rockTexture.get());
	}

	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());

	
	m_Rock[0]->property._transform._translation = Vector3(2900.0f, -380.0f, 2180.0f);
	m_Rock[0]->property._transform._scale = Vector3(160.0f, 160.0f, 160.0f);

	m_Rock[1]->property._transform._translation = Vector3(2530.0f, -320.0f, 2200.0f);
	m_Rock[1]->property._transform._scale = Vector3(10.0f, 10.0f, 10.0f);

	m_switch->property._transform._translation = Vector3(4500.0f, 140.0f, 2200.0f);
	m_switch->property._transform._scale = Vector3(260.0f, 20.0f, 180.0f);

	m_updater = std::make_shared<RockUpdater>();
	m_render = std::make_shared<RockRender>();

	m_rockEvent = eEvent::eChecking;
	return true;
}

void RockManager::Update(){

	rock_flag = m_updater->FlagGet();

	if (m_rockEvent == eEvent::eChecking)
	{
			m_updater->FlagON();
			m_rockEvent = eEvent::eStart;
	}
	else
	{
		m_updater->Update(m_Rock[0].get());
	}

	if (rock_flag == SET){
		m_rockEvent = eEvent::eChecking;
		m_updater->FlagOFF();
	}

}

void RockManager::Render(std::shared_ptr<ShaderBase>shader){

	for (i = 0; i < r_max; i++){
		m_render->Render(m_Rock[i].get(), shader);
	}

	m_switch->Render(shader.get());
	
}

std::shared_ptr<aetherClass::ModelBase> RockManager::Get(){

	return m_Rock[0];
}

std::shared_ptr<aetherClass::ModelBase> RockManager::Switch_Get(){

	return m_switch;
}


bool RockManager::HitMesh(std::shared_ptr<ModelBase>& player, std::shared_ptr<ModelBase>& other){

	if (!m_updater->HittingProcessor(player, other))
	{
		return false;
	}

	return true;
}


