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

// 初期化処理
bool GutioScene::Initialize(){
	std::cout << "gutioいにしゃらいず" << std::endl;
	return true;
}

// 描画処理
void GutioScene::Render(){

}

// 更新処理
bool GutioScene::Updater(){
	return true;
}

// 解放処理
void GutioScene::Finalize(){
	
}