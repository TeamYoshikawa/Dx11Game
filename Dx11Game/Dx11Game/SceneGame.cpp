#include "SceneGame.h"
#include "FbxBase.h"

#include <GameController.h>
#include <CollideBoxOBB.h>

using namespace DxMath;
const std::string SceneGame::m_thisName = "Game";
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
	m_cube->Translation(Vector3(320.0f, -100.f, 200.0f));
	m_cube->Scaling(Vector3(10.0f, 10.0f, 10.0f));

	m_player->SerchNextPoint(m_cube);

	m_stage = std::make_shared<DxModel::FbxStaticMesh>();
	m_stage->LoadFBX("ModelData/models/STAGEMODEL.fbx", DxFbx::FbxLoader::eAxisSystem::eAxisOpenGL);
	m_stage->Initialize(m_camera->GetCamera().get(), "ModelData/textures/texture.jpg");
	m_stage->Transform()._scale = Vector3(1.0f, 1.0f, -1.0f);
	HINSTANCE hInstance = GetModuleHandle(NULL);
	DxController::GameController::Create(hInstance, hWnd);

	return;
}
int a = 0;
void SceneGame::Updata(){
	
	if (DxController::GameController::GetPointer()->IsLeftButtonTrigger())
	{
		m_camera->ChangeCamera(a);
		++a;
		return;
	}
	m_player->Update(1);

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

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_LSHIFT))
	{
		if (DxController::GameController::GetPointer()->IsKeyDown(DIK_W))
		{
			m_cube->Rotation()._y += 1.0f;
		}

		if (DxController::GameController::GetPointer()->IsKeyDown(DIK_S))
		{
			m_cube->Rotation()._y -= 1.0f;
		}

		if (DxController::GameController::GetPointer()->IsKeyDown(DIK_A))
		{
			m_cube->Rotation()._x -= 1.0f;
		}

		if (DxController::GameController::GetPointer()->IsKeyDown(DIK_D))
		{
			m_cube->Rotation()._x += 1.0f;
		}
	}

	std::cout << "X :" << m_cube->Translation()._x << "\t";
	std::cout << "Y :" << m_cube->Translation()._y << "\t";
	std::cout << "Z :" << m_cube->Translation()._z << std::endl;



	return;
}


void SceneGame::Render(){
	m_camera->Render();
	m_stage->AllNodeRender(m_shader, DxModel::eRenderWay::eTexture);
	m_player->Render(m_shader);
	m_cube->Render(m_shader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneGame::Shutdown(){

	return;
}