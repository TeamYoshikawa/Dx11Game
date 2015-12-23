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

	m_lightshader = std::make_shared<DxShader::LightShader>();
	m_lightshader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/DiffuseLightVS.hlsl", L"Shader/DiffuseLightPS.hlsl");

	m_light = std::make_shared<DxLight::Light>();
	m_light->Translation(DxMath::Vector3(-50, 50, -50));
	m_lightshader->SetLight(m_light.get());

	m_player = std::make_shared<PlayerManager>();
	m_player->Initialize(m_camera->GetCamera());

	m_stage = std::make_shared<DxModel::FbxStaticMesh>();
	m_stage->LoadFBX("ModelData/models/STAGEMODEL.fbx", DxFbx::FbxLoader::eAxisSystem::eAxisOpenGL);
	m_stage->Initialize(m_camera->GetCamera().get(), "ModelData/textures/texture.jpg");
	m_stage->Transform()._scale = Vector3(1.0f, 1.0f, -1.0f);

	m_positionCheck = std::make_shared<DxModel::Cube>();
	m_positionCheck->Initialize(m_camera->GetCamera().get(),"ModelData/textures/cylinder_template.jpg");
	m_positionCheck->Scaling(Vector3(50, 50, 50));
	m_positionCheck->Translation(Vector3(-280.0f, -100.f, 185.0f));

	m_rock = std::make_shared<RockManager>();
	m_rock->Initialize(m_camera->GetCamera().get());

	HINSTANCE hInstance = GetModuleHandle(NULL);
	DxController::GameController::Create(hInstance, hWnd);

	return;
}


void SceneGame::Updata(){
	DxController::GameController::GetPointer()->Frame();

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_W))
	{
		m_positionCheck->Translation()._z += 1;
	}

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_S))
	{
		m_positionCheck->Translation()._z -= 1;
	}


	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_A))
	{
		m_positionCheck->Translation()._x += 1;
	}


	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_D))
	{
		m_positionCheck->Translation()._x -= 1;
	}

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_Q))
	{
		m_positionCheck->Translation()._y += 1;
	}

	if (DxController::GameController::GetPointer()->IsKeyDown(DIK_E))
	{
		m_positionCheck->Translation()._y -= 1;
	}

	/*std::cout << "X :" << m_positionCheck->Translation()._x << "\t";
	std::cout << "Y :" << m_positionCheck->Translation()._y << "\t";
	std::cout << "Z :" << m_positionCheck->Translation()._z << std::endl;
*/
	if (m_player->IsChangeCamera())
	{
		m_camera->NextCameraSet();
	
		std::cout << "‚«‚½" << std::endl;
	}

	m_player->Update(0.01f);

	if (m_player->Status()._navigationID == 3)
	{
		m_rock->Update();
	}
	
	return;
}


void SceneGame::Render(){

	m_camera->Render();
	m_stage->AllNodeRender(m_lightshader, DxModel::eRenderWay::eTexture);

	m_player->Render(m_shader);
	
	m_rock->Render(m_shader, DxModel::eRenderWay::eTexture);
//	m_positionCheck->Render(m_shader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneGame::Shutdown(){

	return;
}
