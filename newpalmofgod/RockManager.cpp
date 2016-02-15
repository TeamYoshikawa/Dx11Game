#include "RockManager.h"
#include <iostream>

using namespace aetherClass;
using namespace n_Rock;


bool RockManager::Initialize(ViewCamera* camera){

	m_cnt = 0;

	m_rockTexture = std::make_shared<Texture>();
	m_rockTexture->Load("ModelData/textures/seafloor.dds");

	for (i = 0; i < r_max; i++){
		m_Rock[i] = std::make_shared<Sphere>(10, 10);
		if (!m_Rock[i]->Initialize()){
			return false;
		}
	}

	for (i = 0; i < r_max; i++){
		m_Rock[i]->SetCamera(camera);
		m_Rock[i]->SetTexture(m_rockTexture.get());
	}

	m_Rock[0]->GetTransform()._translation = Vector3(2900.0f, -320.0f, 2100.0f);
	m_Rock[0]->GetTransform()._scale= Vector3(100.0f, 100.0f, 100.0f);

	m_Rock[1]->GetTransform()._translation = Vector3(2530.0f, -320.0f, 2200.0f);
	m_Rock[1]->GetTransform()._scale = Vector3(10.0f, 10.0f, 10.0f);
	
	m_updater = std::make_shared<RockUpdater>();
	m_render = std::make_shared<RockRender>();

	m_isButton = false;
	m_rockEvent = eEvent::eCheckingInput;
	return true;
}

void RockManager::Update(){
	
	m_updater->Update(m_Rock[0].get());

}

void RockManager::Render(std::shared_ptr<ShaderBase>shader){

	for (i = 0; i < r_max; i++){
		m_render->Render(m_Rock[i].get(), shader);
	}
}

std::shared_ptr<aetherClass::ModelBase> RockManager::Get(){

	return m_Rock[0];
}



bool RockManager::GetIsPushButton(){
	return m_isButton;
}