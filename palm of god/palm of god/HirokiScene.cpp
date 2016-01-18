#include "HirokiScene.h"
#include <iostream>
#include "GutioScene.h"
std::string HirokiScene::m_name = "Hiroki";

HirokiScene::HirokiScene():
GameScene(m_name, GetManager())
{
}


HirokiScene::~HirokiScene()
{
}

// ����������
bool HirokiScene::Initialize(){
	std::cout << "���ɂ���炢��" << std::endl;
	/*	�V�[���̓o�^���@	*/
	/*	�����ňڂ�\���̂���V�[�����擾���Ă���	*/
	GameScene* scene = new GutioScene();
	RegisterScene(scene);

	/*
		�����I��delete���s��邽��
		delete�����Ă��܂��ƕs���ȃA�N�Z�X�ƂȂ苭���I������
	*/
	//delete scene;
	return true;
}

// �`�揈��
void HirokiScene::Render(){

}

// �؂�ւ��p
//���ۂ͂���Ȃ�������Ȃ�I�I�I�I�I�I�I�I�I�I�I�I�I
int changeTime = 0;

// �X�V����
bool HirokiScene::Updater(){
	changeTime += 1;
	if (changeTime > 100)
	{
		ChangeScene(GutioScene::m_name);
	}
	std::cout << changeTime << std::endl;

	return true;
}

// �������
void HirokiScene::Finalize(){
	std::cout << "�ӂ����Ȃ炢��" << std::endl;
}