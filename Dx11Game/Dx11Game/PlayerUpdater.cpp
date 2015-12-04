#include "PlayerUpdater.h"
#include <memory>
#include <ModelBase.h>
#include <FbxStaticMesh.h>
PlayerUpdater::PlayerUpdater(){}
PlayerUpdater::PlayerUpdater(PlayerUpdater& other){}


PlayerUpdater::~PlayerUpdater(){

	// 基本ここから動かすなよ！絶対動かすなよ！！！
	Destroy();

}


void PlayerUpdater::Initialize(){

	return;
}

void PlayerUpdater::Destroy(){
	/*
	解放処理

	*/
	return;
}

PlayerBase::PlayerStatus& PlayerUpdater::SendStatus(){
	return SendShareStatus();
}

void PlayerUpdater::SendStatus(PlayerBase::PlayerStatus&){
	return;
}

void PlayerUpdater::Updating(const std::shared_ptr<DxModel::FbxStaticMesh>&, float){

	return;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<DxModel::FbxStaticMesh>&){

	return true;
}


bool PlayerUpdater::HIttingProcessor(const std::shared_ptr<DxModel::ModelBase>&){

	return true;
}


