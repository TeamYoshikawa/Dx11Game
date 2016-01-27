#include "RockManager.h"
#include <iostream>

using namespace aetherClass;
using namespace n_Rock;


bool RockManager::Initialize(ViewCamera* camera){

	m_cnt = 0;

	m_rockTexture = std::make_shared<Texture>();
	m_rockTexture->Load("ModelData/textures/seafloor.dds");

	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("goal.png");


	m_switch = std::make_shared<Cube>();
	if (!m_switch->Initialize()){
		return false;
	}
	m_switch->SetCamera(camera);
	

	m_Rock = std::make_shared<Sphere>(10,10,10);
	if (!m_Rock->Initialize()){
		return false;
	}

	m_Rock->SetCamera(camera);
	m_Rock->SetTexture(m_rockTexture.get());

	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());

	m_Rock->GetTransform()._translation = Vector3(2900.0f, -320.0f, 2100.0f);
	m_Rock->GetTransform()._scale= Vector3(10.0f, 10.0f, 10.0f);

	m_switch->GetTransform()._translation = Vector3(2440.0f, 100.0f, 910.0f);
	m_switch->GetTransform()._scale = Vector3(7.0f, 11.0f, 7.0f);

	m_updater = std::make_shared<RockUpdater>();
	m_render = std::make_shared<RockRender>();

	m_isButton = false;
	m_rockEvent = eEvent::eCheckingInput;
	return true;
}

void RockManager::Update(){
	
	if (m_rockEvent == eEvent::eCheckingInput)
	{
		m_isButton = GameController::GetPointer()->IsKeyDown(DIK_X) ? true : false;
		if (m_isButton){
			m_rockEvent = eEvent::eStart;
	}
		if (m_cnt > 1000){
			m_rockEvent = eEvent::eStart;
		}
	}
	else
	{
		m_updater->Update(m_Rock.get(), m_isButton);
	}
	m_cnt++;
	
}

void RockManager::Shutdown(){
	m_Rock->Finalize();
	
}

void RockManager::Render(std::shared_ptr<ShaderBase>shader){


	m_render->Render(m_Rock.get(), shader);
	
	m_render->Render(m_switch.get(), shader);
}

std::shared_ptr<aetherClass::ModelBase> RockManager::Get(){

	return m_Rock;
}