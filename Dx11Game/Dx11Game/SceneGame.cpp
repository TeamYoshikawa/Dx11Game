#include "SceneGame.h"
#include "FbxBase.h"

#include <GameController.h>
#include <CollideBoxOBB.h>

const std::string SceneGame::m_thisName = "Game";
DxMath::Vector3 prev;
SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName, *manager){


}


SceneGame::~SceneGame()
{
}

void SceneGame::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	std::cout << "Start game" << std::endl;


	m_camera = std::make_shared<CameraManager>();
	m_camera->Initialize();

	m_shader = std::make_shared<DxShader::TextureShader>();
	m_shader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");

	m_player = std::make_shared<PlayerManager>();
	m_player->Initialize(m_camera->GetCamera());

	m_cube = std::make_shared<DxModel::Cube>();
	m_cube->Initialize(m_camera->GetCamera().get(), "ModelData/textures/tex.png");

	prev = m_cube->Translation();

	m_player->SerchNextPoint(m_cube);

	m_stage = std::make_shared<DxModel::FbxStaticMesh>();
	m_stage->Initialize(m_camera->GetCamera().get(), "ModelData/textures/texture.jpg");

	HINSTANCE hInstance = GetModuleHandle(NULL);
	DxController::GameController::Create(hInstance, hWnd);

	return;
}

void SceneGame::Updata(){
	
	std::cout << m_player->HitMesh(m_cube) << std::endl;
	if (m_player->HitMesh(m_cube))
	{
		return;
	}
	m_player->Update(5);

	DxController::GameController::GetPointer()->Frame();

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_W))
	{
		m_cube->Translation()._z += 1.0f;
	}

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_S))
	{
		m_cube->Translation()._z -= 1.0f;
	}

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_A))
	{
		m_cube->Translation()._x -= 1.0f;
	}

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_D))
	{
		m_cube->Translation()._x += 1.0f;
	}

	return;
}


void SceneGame::Render(){
	m_camera->Render();
	m_player->Render(m_shader);
	m_cube->Render(m_shader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneGame::Shutdown(){

	return;
}