#include "SceneGame.h"
#include "FbxBase.h"
const std::string SceneGame::m_thisName = "Game";

SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName,*manager){
	
	
}


SceneGame::~SceneGame()
{
}

void SceneGame::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	std::cout << "Start game" << std::endl;


	m_camera = std::make_shared<DxCamera::ViewCamera>();
	m_camera->Translation(DxMath::Vector3(0, 0, -500));

	m_shader = std::make_shared<DxShader::TextureShader>();
	m_shader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");

	m_player = std::make_shared<PlayerManager>();
	m_player->Initialize(m_camera);

	return;
}


void SceneGame::Updata(){
	m_player->Update(5);
	return;
}


void SceneGame::Render(){
	m_camera->Render();
	m_player->Render(m_shader);
	return;
}

void SceneGame::Shutdown(){

	return;
}