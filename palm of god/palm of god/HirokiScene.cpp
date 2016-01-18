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

// 初期化処理
bool HirokiScene::Initialize(){
	std::cout << "いにしゃらいず" << std::endl;
	/*	シーンの登録方法	*/
	/*	ここで移る可能性のあるシーンを取得しておく	*/
	GameScene* scene = new GutioScene();
	RegisterScene(scene);

	/*
		内部的にdeleteが行わるため
		deleteをしてしまうと不正なアクセスとなり強制終了する
	*/
	//delete scene;
	return true;
}

// 描画処理
void HirokiScene::Render(){

}

// 切り替え用
//実際はこんなやり方すんなよ！！！！！！！！！！！！！
int changeTime = 0;

// 更新処理
bool HirokiScene::Updater(){
	changeTime += 1;
	if (changeTime > 100)
	{
		ChangeScene(GutioScene::m_name);
	}
	std::cout << changeTime << std::endl;

	return true;
}

// 解放処理
void HirokiScene::Finalize(){
	std::cout << "ふぁいならいず" << std::endl;
}