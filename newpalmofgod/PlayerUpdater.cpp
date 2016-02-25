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

// ゲッター
PlayerBase::PlayerStatus& PlayerUpdater::SendStatus(){
	return SendShareStatus();
}

// セッター
void PlayerUpdater::SendStatus(PlayerBase::PlayerStatus&){

	return;
}

void PlayerUpdater::Updating(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera){

	// 移動の処理
	Move(playerObject,camera);
	return;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){

	// TODO: 当たったかを調べる条件式を記載
	if (!CollideBoxOBB(*player, *other)){

		return false;
	}
	if (SendStatus()._muteki == true)return false;
	std::cout << "当たったよ";
	m_damegeSound->PlayToOneTime();
	SendStatus()._life -= 1;
	SendStatus()._muteki = true;
	m_damageFlg = true;
	SendStatus()._moveState = PlayerBase::ePlayerMoveState::eDamage;
	return true;

}

// 動いてるときの処理
void PlayerUpdater::Move(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera){
	static float cmx = -100.0f, cmy = -8.0f, cmz = 692.0f, cmrx = -170, cmry = -90;
	static float cm_move = 5.0f;
	static float rad = 0;

	float move_x = 0, move_z = 0;
	rad += 1;
	if (rad > 360)rad -= 360;


	if (GameController::GetKey().IsKeyDown(DIK_LEFT)){
		cmry += cm_move * 1;
	}
	else if (GameController::GetKey().IsKeyDown(DIK_RIGHT)){
		cmry -= cm_move * 1;
	}
	if (GameController::GetKey().IsKeyDown(DIK_DOWN)){
		cmrx += cm_move * 1;
	}
	else if (GameController::GetKey().IsKeyDown(DIK_UP)){
		cmrx -= cm_move * 1;
	}
	else{
		if (GameController::GetKey().IsKeyDown(DIK_LCONTROL))
		{
			if (GameController::GetKey().IsKeyDown(DIK_A)){
				cmx -= (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
				cmz += (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
			}
			else if (GameController::GetKey().IsKeyDown(DIK_D)){
				cmx += (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
				cmz -= (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
			}
			if (GameController::GetKey().IsKeyDown(DIK_S)){
				cmx += (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
				cmz += (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
			}
			else if (GameController::GetKey().IsKeyDown(DIK_W)){
				cmx -= (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
				cmz -= (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
			}
		}
		else
		{
			if (GameController::GetKey().IsKeyDown(DIK_A)){
				cmx -= cm_move * cos(kAetherPI * cmry / 180);
				cmz += cm_move * sin(kAetherPI * cmry / 180);
			}
			else if (GameController::GetKey().IsKeyDown(DIK_D)){
				cmx += cm_move * cos(kAetherPI * cmry / 180);
				cmz -= cm_move * sin(kAetherPI * cmry / 180);
			}
			if (GameController::GetKey().IsKeyDown(DIK_S)){
				cmx += cm_move * sin(kAetherPI * cmry / 180);
				cmz += cm_move * cos(kAetherPI * cmry / 180);
			}
			else if (GameController::GetKey().IsKeyDown(DIK_W)){
				cmx -= cm_move * sin(kAetherPI * cmry / 180);
				cmz -= cm_move * cos(kAetherPI * cmry / 180);
			}
		}


	}

	// いどー
	camera->Translation() = Vector3(cmx, cmy, cmz);
	camera->Rotation() = Vector3(cmrx, cmry, 1);

	// モデルと連動
	playerObject->GetTransform()._translation._x = camera->Translation()._x - 10;
	playerObject->GetTransform()._translation._z = camera->Translation()._z;

}


bool PlayerUpdater::IsDamage(){
	return m_damageFlg;
}