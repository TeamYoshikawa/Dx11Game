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

PlayerBase::PlayerStatus& PlayerUpdater::SendStatus(){
	return SendShareStatus();
}

void PlayerUpdater::SendStatus(PlayerBase::PlayerStatus&){
	return;
}

void PlayerUpdater::Updating(const std::shared_ptr<DxModel::FbxStaticMesh>& playerObject, float frame){


	if (playerObject->Transform()._translation._x > SendStatus()._nextMoveDirection._x)
	{
		std::cout << "止まってるよ" << std::endl;
		//return;
	}


	playerObject->Transform()._translation += SendStatus()._nextMoveDirection / 100;
	float length = SendStatus()._nextMoveDirection._x - playerObject->Transform()._translation._x;
	if (length < 1)
	{
		//playerObject->Transform()._translation._x = SendStatus()._nextMoveDirection._x;
	}

	return;
}

// 指定されたオブジェクトに向かって追いかける
void PlayerUpdater::FaceTheObject(const std::shared_ptr<DxModel::FbxStaticMesh>& player, const std::shared_ptr<DxModel::ModelBase>& object){
	SendStatus()._nextMoveDirection = object->Translation() - player->Transform()._translation;

	float rad = atan2(SendStatus()._nextMoveDirection._x, SendStatus()._nextMoveDirection._z);
	float hoge = rad / PI * 180;
	std::cout << "rotation:" << hoge << std::endl;
	std::cout << "player rotation:" << player->Transform()._rotation._y << std::endl;

	player->Transform()._rotation._y = hoge;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<DxModel::FbxStaticMesh>&){

	return true;
}


bool PlayerUpdater::HIttingProcessor(const std::shared_ptr<DxModel::ModelBase>&){

	return true;
}


