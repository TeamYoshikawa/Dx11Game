#include "GutioScene.h"
#include <iostream>
std::string GutioScene::m_name = "Gutio";

GutioScene::GutioScene() :
GameScene(m_name, GetManager())
{
}


GutioScene::~GutioScene()
{
}

// ����������
bool GutioScene::Initialize(){
	std::cout << "gutio���ɂ���炢��" << std::endl;
	return true;
}

// �`�揈��
void GutioScene::Render(){

}

// �X�V����
bool GutioScene::Updater(){
	return true;
}

// �������
void GutioScene::Finalize(){
	
}