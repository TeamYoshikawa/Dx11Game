#include "SceneGame.h"

const std::string SceneGame::m_thisName = "Game";

SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName,*manager){
	
	
}


SceneGame::~SceneGame()
{
}

void SceneGame::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	std::cout << "Start game" << std::endl;

	m_static = std::make_shared<DxModel::FbxStaticMesh>();

	m_static->LoadFBX("Box_Sample.fbx", DxFbx::FbxLoader::eAxisSystem::eAxisOpenGL);

	//m_static->Initialize()
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