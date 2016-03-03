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
	m_playerSound->SetValume(-1000);

	m_damegeSound = std::make_shared<GameSound>();
	m_damegeSound->Load("Sound/Player/damage03.wav");
	m_damegeSound->SetValume(+3000);

	m_isHitting = false;
	m_prevKey = NULL;

	m_currentPos = Vector3(-50, -8, 692);
	m_nextPos = m_currentPos;

	//std::cout << "Init!!!!!!!!!!!!!!!!!!!!!" << std::endl;
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

void PlayerUpdater::Updating(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera, bool IsHitWall){

	// 移動の処理
	Move(playerObject, camera, IsHitWall);
	//GetKey();
	TimeSpiral();


	return;
}


bool PlayerUpdater::HittingProcessor(ModelBase* player, ModelBase* other){

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

bool PlayerUpdater::HittingWall(ModelBase* player, ModelBase* wall)
{
	if (!CollideBoxOBB(*player, *wall))
	{
		return false;
	}
	return true;
}


// 動いてるときの処理
void PlayerUpdater::Move(const std::shared_ptr<FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera> camera, bool IsHitWall){
	static float cmx = -50.0f, cmy = -8.0f, cmz = 692.0f, cmrx = -170, cmry = -90;
	//std::cout << "CurrentPosition:" << std::endl;
	//std::cout << "X:" << m_currentPos._x << std::endl;
	//std::cout << "Y:" << m_currentPos._y << std::endl;
	//std::cout << "z:" << m_currentPos._z << std::endl;


	if (IsHitWall)
	{

		m_isHitting = true;
		//cm_move *= -1.33;
		cmx = m_currentPos._x;
		cmy = m_currentPos._y;
		cmz = m_currentPos._z;
		camera->property._translation = m_currentPos;
		playerObject->property._transform._translation._x = camera->property._translation._x - 10;
		playerObject->property._transform._translation._z = camera->property._translation._z;
		std::cout << "壁に当たったよ" << std::endl;
	}
	else
	{
		m_isHitting = false;
		cmx = m_nextPos._x;
		cmy = m_nextPos._y;
		cmz = m_nextPos._z;
	}

	m_currentPos = Vector3(cmx, cmy, cmz);

	float cm_move = 3.0f;
	int pushKey = NULL;;
	//if (IsHitWall)
	//{

	//	m_isHitting = true;
	//	cm_move *= -1.33;
	//	std::cout << "壁に当たったよ" << std::endl;
	//}
	//else
	//{
	//	m_isHitting = false;
	//}
	if (GameController::GetKey().IsKeyDown(DIK_LEFT)){
		cmry += cm_move * 0.43;
		m_playerSound->PlayToOneTime();
	}
	else if (GameController::GetKey().IsKeyDown(DIK_RIGHT)){
		cmry -= cm_move * 0.43;
		m_playerSound->PlayToOneTime();
	}
	if (GameController::GetKey().IsKeyDown(DIK_DOWN)){
		cmrx += cm_move * 0.35;
		m_playerSound->PlayToOneTime();
	}
	else if (GameController::GetKey().IsKeyDown(DIK_UP)){
		cmrx -= cm_move * 0.35;
		m_playerSound->PlayToOneTime();
	}
	if (cmrx < -225){ cmrx = -225; }
	if (cmrx > -125){ cmrx = -125; }

	if (GameController::GetKey().IsKeyDown(DIK_LCONTROL))
	{
		if (GameController::GetKey().IsKeyDown(DIK_A)){
			cmx -= (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
			cmz += (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
		else if (GameController::GetKey().IsKeyDown(DIK_D)){
			cmx += (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
			cmz -= (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
		if (GameController::GetKey().IsKeyDown(DIK_S)){
			cmx += (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
			cmz += (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
		else if (GameController::GetKey().IsKeyDown(DIK_W)){
			cmx -= (cm_move*2.0f) * sin(kAetherPI * cmry / 180);
			cmz -= (cm_move*2.0f) * cos(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
	}
	else
	{
		if (GameController::GetKey().IsKeyDown(DIK_A)){
			cmx -= cm_move * cos(kAetherPI * cmry / 180);
			cmz += cm_move * sin(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
		else if (GameController::GetKey().IsKeyDown(DIK_D)){
			cmx += cm_move * cos(kAetherPI * cmry / 180);
			cmz -= cm_move * sin(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
		if (GameController::GetKey().IsKeyDown(DIK_S)){
			cmx += cm_move * sin(kAetherPI * cmry / 180);
			cmz += cm_move * cos(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
		else if (GameController::GetKey().IsKeyDown(DIK_W)){
			cmx -= cm_move * sin(kAetherPI * cmry / 180);
			cmz -= cm_move * cos(kAetherPI * cmry / 180);
			m_playerSound->PlayToOneTime();
		}
	}

	//Vector3 move = Vector3(cmx, cmy, cmz);
	m_nextPos = Vector3(cmx, cmy, cmz);

	//std::cout << "CMX = " << cmx << std::endl;

	//if (IsHitWall&&m_prevKey != pushKey)
	//{
	//	move *= -1;

	//	m_prevKey = pushKey;
	//}

	/* いどー*/
	camera->property._translation = m_nextPos;
	camera->property._rotation= Vector3(cmrx, cmry, 1);

	//// モデルと連動

	playerObject->property._transform._translation._x = camera->property._translation._x - 10;
	playerObject->property._transform._translation._z = camera->property._translation._z;



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

void PlayerUpdater::TimeSpiral()
{
	if (SendStatus()._muteki == false)return;

	static int time = 180;
	if (time <= 0)
	{
		SendStatus()._muteki = false;
		time = 180;
	}

	time--;

	std::cout << time << std::endl;
}