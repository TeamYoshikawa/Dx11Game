#include "PlayerUpdater.h"
#include <memory>
#include <ModelBase.h>
#include <FbxModel.h>
#include <MathUtility.h>
#include <iostream>
using namespace aetherClass;
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

// �Q�b�^�[
PlayerBase::PlayerStatus& PlayerUpdater::SendStatus(){
	return SendShareStatus();
}

// �Z�b�^�[
void PlayerUpdater::SendStatus(PlayerBase::PlayerStatus&){
	
	return;
}

void PlayerUpdater::Updating(const std::shared_ptr<FbxModel>& playerObject, float frame){

	// �ړ��̏���
	playerObject->GetTransform()._translation += SendStatus()._nextMoveDirection / 500;

	return;
}

// �w�肳�ꂽ�I�u�W�F�N�g�Ɍ������Ēǂ�������
void PlayerUpdater::FaceTheObject(const std::shared_ptr<FbxModel>& player, const std::shared_ptr<ModelBase>& object){
	SendStatus()._nextMoveDirection = object->GetTransform()._translation- player->GetTransform()._translation;

	float rad = atan2(SendStatus()._nextMoveDirection._x, SendStatus()._nextMoveDirection._z);
	float rotationY = rad / kAetherPI * 180;

	player->GetTransform()._rotation._y = rotationY;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<FbxModel>& player, const std::shared_ptr<ModelBase>& other){

	// TODO: �����������𒲂ׂ���������L��
	return true;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<aetherClass::FbxModel>&){

	return true;
}
