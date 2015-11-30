#include "SceneTitle.h"
#include "SceneGame.h"
const std::string SceneTitle::m_thisName = "Title";
SceneTitle::SceneTitle(SceneManager* manager) :
SceneBase(m_thisName, *manager)
{
}


SceneTitle::~SceneTitle()
{
}


void SceneTitle::Initialize(){
	std::cout << "Start title" << std::endl;

	return;
}


void SceneTitle::Updata(){

	return;
}


void SceneTitle::Render(){

	return;
}

void SceneTitle::Shutdown(){

	return;
}