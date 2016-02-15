#include "TrapManager.h"
#include <iostream>

using namespace aetherClass;


bool TrapManager::Initialize(ViewCamera* camera){

	std::cout << "TrapManager Init"<<std::endl;

	m_rock = std::make_shared<RockManager>();
	

	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("goal.png");

	m_playerTexture = std::make_shared<Texture>();
	m_playerTexture->Load("Load.png");

	m_switch = std::make_shared<Cube>();
	if (!m_switch->Initialize()){
		return false;
	}

	m_player = std::make_shared<Cube>();
	if (!m_player->Initialize()){
		return false;
	}

	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());

	m_player->SetCamera(camera);
	m_player->SetTexture(m_playerTexture.get());
	
	m_switch->GetTransform()._translation = Vector3(2800.0f, 100.0f, 630.0f);
	m_switch->GetTransform()._scale = Vector3(260.0f, 180.0f, 180.0f);
	
	m_player->GetTransform()._translation = Vector3(2300.0f, 100.0f, 630.0f);
	m_player->GetTransform()._scale = Vector3(100.0f, 100.0f, 100.0f);

	return true;
}

void TrapManager::Update(){



	if (GameController::GetKey().IsKeyDown(DIK_A)){
		
		m_player->GetTransform()._translation._x -= 1.0f;
	}

	if (GameController::GetKey().IsKeyDown(DIK_D)){
	
		m_player->GetTransform()._translation._x += 1.0f;
	}

	if (aetherFunction::CollideBoxOBB(*m_player, *m_switch)){
		m_rock->Update();
	}
	
}

void TrapManager::Render(std::shared_ptr<ShaderBase>shader){
	//m_switch->Render(shader.get());

	m_player->Render(shader.get());
	
}