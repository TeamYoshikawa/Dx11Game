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
	return;
}

void PlayerUpdater::Destroy(){

	return;
}

// ゲッター
PlayerBase::PlayerStatus& PlayerUpdater::SendStatus(){
	return SendShareStatus();
}

// セッター
void PlayerUpdater::SendStatus(PlayerBase::PlayerStatus&){
	
	return;
}

void PlayerUpdater::Updating(const std::shared_ptr<FbxModel>& playerObject){

	// 移動の処理
	Move(playerObject);
	return;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){
	
	// TODO: 当たったかを調べる条件式を記載
	if (!CollideBoxOBB(*player, *other)){
		
		return false;
	}
	if (SendStatus()._muteki == true)return false;
	std::cout << "当たったよ";
	SendStatus()._life -= 1;
	SendStatus()._muteki = true;
	m_damageFlg = true;
	SendStatus()._moveState = PlayerBase::ePlayerMoveState::eDamage;
		return true;

}

// 動いてるときの処理
void PlayerUpdater::Move(const std::shared_ptr<FbxModel>& playerObject){

	if (GameController::GetKey().IsKeyDown(DIK_RIGHT)){
		playerObject->GetTransform()._translation._x += 10.0f;
	}
	if (GameController::GetKey().IsKeyDown(DIK_LEFT)){
		playerObject->GetTransform()._translation._x -= 10.0f;
	}
	if (GameController::GetKey().IsKeyDown(DIK_UP)){
		playerObject->GetTransform()._translation._z -= 10.0f;
	}
	if (GameController::GetKey().IsKeyDown(DIK_DOWN)){
		playerObject->GetTransform()._translation._z += 10.0f;
	}
}


bool PlayerUpdater::IsDamage(){
	return m_damageFlg;
}