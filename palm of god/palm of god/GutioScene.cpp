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

// ‰Šú‰»ˆ—
bool GutioScene::Initialize(){
	std::cout << "gutio‚¢‚É‚µ‚á‚ç‚¢‚¸" << std::endl;
	return true;
}

// •`‰æˆ—
void GutioScene::Render(){

}

// XVˆ—
bool GutioScene::Updater(){
	return true;
}

// ‰ğ•úˆ—
void GutioScene::Finalize(){
	
}