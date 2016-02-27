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

	m_isHitting = false;
	m_prevKey = NULL;
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

void PlayerUpdater::Updating(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera,bool IsHitWall){

	// �ړ��̏���
	Move(playerObject,camera,IsHitWall);
	//GetKey();
	
	return;
}


bool PlayerUpdater::HittingProcessor(ModelBase* player, ModelBase* other){

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

bool PlayerUpdater::HittingWall(ModelBase* player, ModelBase* wall)
{
	if (!CollideBoxOBB(*player, *wall))
	{
		return false;
	}
	return true;
}


// �����Ă�Ƃ��̏���
void PlayerUpdater::Move(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera,bool IsHitWall){
	static float cmx = -50.0f, cmy = -8.0f, cmz = 692.0f, cmrx = -170, cmry = -90;
	float cm_move = 5.0f;
	int pushKey = NULL;;
	if (IsHitWall)
	{
	
		m_isHitting = true;
		cm_move *= -1;
		std::cout << "�ǂɓ���������" << std::endl;
	}
	else
	{
		m_isHitting = false;
	}
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
				pushKey = DIK_A;
			}
			else if (GameController::GetKey().IsKeyDown(DIK_D)){
				cmx += (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
				cmz -= (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
				pushKey = DIK_D;
			}else
			if (GameController::GetKey().IsKeyDown(DIK_S)){
				cmx += (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
				cmz += (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
				pushKey = DIK_S;
			}
			else if (GameController::GetKey().IsKeyDown(DIK_W)){
				cmx -= (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
				cmz -= (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
				pushKey = DIK_W;
			}
		}
		else
		{
			if (GameController::GetKey().IsKeyDown(DIK_A)){
				cmx -= cm_move * cos(kAetherPI * cmry / 180);
				cmz += cm_move * sin(kAetherPI * cmry / 180);
				pushKey = DIK_A;
			}
			else if (GameController::GetKey().IsKeyDown(DIK_D)){
				cmx += cm_move * cos(kAetherPI * cmry / 180);
				cmz -= cm_move * sin(kAetherPI * cmry / 180);
				pushKey = DIK_D;
			}else
			if (GameController::GetKey().IsKeyDown(DIK_S)){
				cmx += cm_move * sin(kAetherPI * cmry / 180);
				cmz += cm_move * cos(kAetherPI * cmry / 180);
				pushKey = DIK_S;
			}
			else if (GameController::GetKey().IsKeyDown(DIK_W)){
				cmx -= cm_move * sin(kAetherPI * cmry / 180);
				cmz -= cm_move * cos(kAetherPI * cmry / 180);
				pushKey = DIK_W;
			}
		}
	}
	
	Vector3 move = Vector3(cmx, cmy, cmz);

	if (IsHitWall&&m_prevKey != pushKey)
	{
		move *= -1;
		
		m_prevKey = pushKey;
	}
	
	/* ���ǁ[*/
	camera->Translation() = move;
	camera->Rotation() = Vector3(cmrx, cmry, 1);

	//// ���f���ƘA��
	playerObject->GetTransform()._translation._x = camera->Translation()._x - 10;
	playerObject->GetTransform()._translation._z = camera->Translation()._z;
	
	return;
}

// PlayerUpdater::eKey PlayerUpdater::GetKey()
//{
//	if (GameController::GetKey().IsKeyDown(DIK_W))
//	{
//		return eKey::eUp;
//	}
//	if (GameController::GetKey().IsKeyDown(DIK_S))
//	{
//		return eKey::eDown;
//	}
//	if (GameController::GetKey().IsKeyDown(DIK_D))
//	{
//		return eKey::eRight;
//	}
//	if (GameController::GetKey().IsKeyDown(DIK_A))
//	{
//		return eKey::eLeft;
//	}
//	return eKey::eNull;
//}


bool PlayerUpdater::IsDamage(){
	return m_damageFlg;
}