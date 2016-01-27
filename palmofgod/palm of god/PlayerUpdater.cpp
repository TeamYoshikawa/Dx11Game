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
	
	w_stopcnt = 0;
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

	//�^���I��(�ŏ��̃g���b�v�̏ꏊ��)�~�܂铮�������Ă��邾��

	if (SendStatus()._navigationID != 4){
		playerObject->GetTransform()._translation += SendStatus()._nextMoveDirection / 170;
	}
	else
	{
		if (w_stopcnt > 500)
		{
			playerObject->GetTransform()._translation += SendStatus()._nextMoveDirection / 170;
		}
		
		w_stopcnt++;
		std::cout << w_stopcnt<< "\n";
	}

	//�����œ���(���������Ă��Ȃ�)

	//playerObject->GetTransform()._translation += SendStatus()._nextMoveDirection / 170;

	return;
}

// �w�肳�ꂽ�I�u�W�F�N�g�Ɍ������Ēǂ�������
void PlayerUpdater::FaceTheObject(const std::shared_ptr<FbxModel>& player, const std::shared_ptr<ModelBase>& object){
	SendStatus()._nextMoveDirection = object->GetTransform()._translation- player->GetTransform()._translation;

	float rad = atan2(SendStatus()._nextMoveDirection._x, SendStatus()._nextMoveDirection._z);
	float rotationY = rad / kAetherPI * 180;

	player->GetTransform()._rotation._y = rotationY;
}


bool PlayerUpdater::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){
	

	// TODO: �����������𒲂ׂ���������L��
	if (!CollideBoxOBB(*player, *other)){
		
		return false;
	}
	if (SendStatus()._muteki == true)return false;
		std::cout << "����������";
		SendStatus()._life -= 1;
		SendStatus()._muteki = true;
		return true;

}
