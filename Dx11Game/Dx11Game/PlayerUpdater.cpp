#include "PlayerUpdater.h"
#include <memory>
#include <ModelBase.h>
#include <FbxStaticMesh.h>
PlayerUpdater::PlayerUpdater(){}
PlayerUpdater::PlayerUpdater(PlayerUpdater& other){}


PlayerUpdater::~PlayerUpdater(){

	// ��{�������瓮�����Ȃ�I��Γ������Ȃ�I�I�I
	Destroy();

}


void PlayerUpdater::Initialize(){

	return;
}

void PlayerUpdater::Destroy(){
	/*
	�������

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


