#include "SceneGame.h"

const std::string SceneGame::m_thisName = "Game";

SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName,*manager){
	
	
}


SceneGame::~SceneGame()
{
}

void SceneGame::Initialize(){
	std::cout << "Start game" << std::endl;
	std::cout << "ƒtƒ‰ƒO" << IsChange() << std::endl;
	return;
}


void SceneGame::Updata(){

	return;
}


void SceneGame::Render(){

	return;
}

void SceneGame::Shutdown(){

	return;
}