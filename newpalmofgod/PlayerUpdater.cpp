#include "PlayerUpdater.h"
#include <memory>
#include <ModelBase.h>
#include <FbxModel.h>
#include <MathUtility.h>
#include <iostream>
#include<Physics.h>
#include<GameController.h>

using namespace aetherClass;
using namespace aetherFunction;
PlayerUpdater::PlayerUpdater(){}
PlayerUpdater::PlayerUpdater(PlayerUpdater& other){}


PlayerUpdater::~PlayerUpdater(){

	Destroy();

}

void PlayerUpdater::Initialize(){
	m_damageCounter = 0;
	m_daedCounter = 0;
	m_damageFlg = 0;
	m_playerSound = std::make_shared<GameSound>();
	m_playerSound->Load("Sound/Player/chain03.wav");
	m_playerSound->SetValume(-4000);

	m_damegeSound = std::make_shared<GameSound>();
	m_damegeSound->Load("Sound/Player/damage03.wav");
	m_damegeSound->SetValume(+3000);
	return;
}

void PlayerUpdater::Destroy(){

	return;
}

// �Q�b�^�[
PlayerBase::PlayerStatus& PlayerUpdater::SendStatus(){
	return SendShareStatus();
}

// �Z�b�^�[
void PlayerUpdater::SendStatus(PlayerBase::PlayerStatus&){

	return;
}

void PlayerUpdater::Updating(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera){

	// �ړ��̏���
	Move(playerObject,camera);
	return;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){

	// TODO: �����������𒲂ׂ���������L��
	if (!CollideBoxOBB(*player, *other)){

		return false;
	}
	if (SendStatus()._muteki == true)return false;
	std::cout << "����������";
	m_damegeSound->PlayToOneTime();
	SendStatus()._life -= 1;
	SendStatus()._muteki = true;
	m_damageFlg = true;
	SendStatus()._moveState = PlayerBase::ePlayerMoveState::eDamage;
	return true;

}

// �����Ă�Ƃ��̏���
void PlayerUpdater::Move(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera){

	if (GameController::GetKey().IsKeyDown(DIK_RIGHT)){
		camera->Rotation()._y -= 2.0f;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_LEFT)){
		camera->Rotation()._y += 2.0f;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_UP)){
		camera->Rotation()._x -= 2.0f;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_DOWN)){
		camera->Rotation()._x += 2.0f;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_W)){
		camera->Translation()._x += 10.0f;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_S)){
		camera->Translation()._x -= 10.0f;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_D)){
		camera->Translation()._z += 10.0f;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_A)){
		camera->Translation()._z -= 10.0f;
		m_playerSound->PlayToOneTime();
	}

	// ���f���ƘA��
	playerObject->GetTransform()._translation._x = camera->Translation()._x - 10;
	playerObject->GetTransform()._translation._z = camera->Translation()._z;

}


bool PlayerUpdater::IsDamage(){
	return m_damageFlg;
}