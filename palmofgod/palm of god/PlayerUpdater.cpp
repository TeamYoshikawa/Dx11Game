#include "PlayerUpdater.h"
#include <memory>
#include <ModelBase.h>
#include <FbxModel.h>
#include <MathUtility.h>
#include <iostream>
#include<Physics.h>

using namespace aetherClass;
using namespace aetherFunction;
PlayerUpdater::PlayerUpdater(){}
PlayerUpdater::PlayerUpdater(PlayerUpdater& other){}


PlayerUpdater::~PlayerUpdater(){

	Destroy();

}


void PlayerUpdater::Initialize(){
	m_damageCounter = 0;
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
	Stand(playerObject);
	Fall(playerObject);
	Damage(playerObject);
	return;
}

// 指定されたオブジェクトに向かって追いかける
void PlayerUpdater::FaceTheObject(const std::shared_ptr<FbxModel>& player, const std::shared_ptr<ModelBase>& object){
	SendStatus()._nextMoveDirection = object->GetTransform()._translation- player->GetTransform()._translation;

	float rad = atan2(SendStatus()._nextMoveDirection._x, SendStatus()._nextMoveDirection._z);
	float rotationY = rad / kAetherPI * 180;

	player->GetTransform()._rotation._y = rotationY;
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
	// 現在の状態がMoveじゃないなら何もしない
	if (SendStatus()._moveState != PlayerBase::ePlayerMoveState::eMove)
	{
		return;
	}

	playerObject->GetTransform()._translation += SendStatus()._nextMoveDirection / 150;
}

// 立ち止まるときの処理
void PlayerUpdater::Stand(const std::shared_ptr<FbxModel>& playerObject){
	if (SendStatus()._moveState != PlayerBase::ePlayerMoveState::eStatnd)
	{
		return;
	}
}

// 落ちる時の処理
void PlayerUpdater::Fall(const std::shared_ptr<FbxModel>& playerObject){
	if (SendStatus()._moveState != PlayerBase::ePlayerMoveState::eMove)
	{
		return;
	}
}



void PlayerUpdater::Damage(const std::shared_ptr<aetherClass::FbxModel>& playerObject){
	if (SendStatus()._moveState != PlayerBase::ePlayerMoveState::eDamage)
	{
		return;
	}
	
	m_damageCounter += 1;
	// ある一定数まったら活動再開
	if (m_damageCounter > kDamageWaitTime)
	{
		m_damageCounter = 0;
		SendStatus()._moveState = PlayerBase::ePlayerMoveState::eMove;
		SendStatus()._muteki = false;
		m_damageFlg = false;
	}
	return;
}

bool PlayerUpdater::IsDamage(){
	return m_damageFlg;
}