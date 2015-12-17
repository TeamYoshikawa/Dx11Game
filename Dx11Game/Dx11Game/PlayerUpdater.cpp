#include "PlayerUpdater.h"
#include <memory>
#include <ModelBase.h>
#include <FbxStaticMesh.h>
#include <iostream>

#define PI 3.14159265358979323846264338327950288

PlayerUpdater::PlayerUpdater(){}
PlayerUpdater::PlayerUpdater(PlayerUpdater& other){}


PlayerUpdater::~PlayerUpdater(){

	Destroy();

}


void PlayerUpdater::Initialize(){

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

void PlayerUpdater::Updating(const std::shared_ptr<DxModel::FbxStaticMesh>& playerObject, float frame){

	// 移動の処理
	playerObject->Transform()._translation += SendStatus()._nextMoveDirection / 500;

	return;
}

// 指定されたオブジェクトに向かって追いかける
void PlayerUpdater::FaceTheObject(const std::shared_ptr<DxModel::FbxStaticMesh>& player, const std::shared_ptr<DxModel::ModelBase>& object){
	SendStatus()._nextMoveDirection = object->Translation() - player->Transform()._translation;

	float rad = atan2(SendStatus()._nextMoveDirection._x, SendStatus()._nextMoveDirection._z);
	float rotationY = rad / PI * 180;

	player->Transform()._rotation._y = rotationY;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<DxModel::ModelBase>& player, const std::shared_ptr<DxModel::ModelBase>& other){

	if (!m_boxCllider.IsCollideOBB(player, other))
	{
		return false;
	}
	return true;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<DxModel::FbxStaticMesh>&){

	return true;
}
