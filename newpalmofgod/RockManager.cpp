#include "RockManager.h"
#include <iostream>

using namespace aetherClass;
using namespace n_Rock;


bool RockManager::Initialize(ViewCamera* camera){

	m_rockTexture = std::make_shared<Texture>();
	m_rockTexture->Load("ModelData/textures/seafloor.dds");

	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("goal.png");

	m_hplayerTexture = std::make_shared<Texture>();
	m_hplayerTexture->Load("Load.png");


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

	m_hplayer = std::make_shared<Cube>();
	if (!m_hplayer->Initialize()){
		return false;
	}

	for (i = 0; i < r_max; i++){
		m_Rock[i]->SetCamera(camera);
		m_Rock[i]->SetTexture(m_rockTexture.get());
	}
	
	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());

	m_hplayer->SetCamera(camera);
	m_hplayer->SetTexture(m_hplayerTexture.get());


	m_Rock[0]->GetTransform()._translation = Vector3(2900.0f, -320.0f, 2100.0f);
	m_Rock[0]->GetTransform()._scale= Vector3(100.0f, 100.0f, 100.0f);

	m_Rock[1]->GetTransform()._translation = Vector3(2530.0f, -320.0f, 2200.0f);
	m_Rock[1]->GetTransform()._scale = Vector3(10.0f, 10.0f, 10.0f);
	
	m_switch->GetTransform()._translation = Vector3(2800.0f, 100.0f, 630.0f);
	m_switch->GetTransform()._scale = Vector3(260.0f, 180.0f, 180.0f);

	m_hplayer->GetTransform()._translation = Vector3(2300.0f, 100.0f, 630.0f);
	m_hplayer->GetTransform()._scale = Vector3(100.0f, 100.0f, 100.0f);

	m_updater = std::make_shared<RockUpdater>();
	m_render = std::make_shared<RockRender>();

	m_rockEvent = eEvent::eChecking;
	return true;
}

void RockManager::Update(){

	if (GameController::GetKey().IsKeyDown(DIK_A)){

		m_hplayer->GetTransform()._translation._x -= 1.0f;
	}

	if (GameController::GetKey().IsKeyDown(DIK_D)){

		m_hplayer->GetTransform()._translation._x += 1.0f;
	}

	if (m_rockEvent == eEvent::eChecking)
	{
		if (aetherFunction::CollideBoxOBB(*m_hplayer, *m_switch)){
			m_rockEvent = eEvent::eStart;
		}
	}
	else
	{
		m_updater->Update(m_Rock[0].get());
	}
}

void RockManager::Render(std::shared_ptr<ShaderBase>shader){

	for (i = 0; i < r_max; i++){
		m_render->Render(m_Rock[i].get(), shader);
	}

	m_switch->Render(shader.get());
	m_hplayer->Render(shader.get());
}


std::shared_ptr<aetherClass::ModelBase> RockManager::Get(){

	return m_Rock[0];
}



