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

	m_cube = std::make_shared<DxModel::Cube>();
	m_cube->Initialize(m_camera->GetCamera().get(), "ModelData/textures/tex.png");
	m_cube->Translation(Vector3(320.0f, -100.f, 200.0f));
	m_cube->Scaling(Vector3(10.0f, 10.0f, 10.0f));

	m_player->SerchNextPoint(m_cube);

	m_stage = std::make_shared<DxModel::FbxStaticMesh>();
	m_stage->LoadFBX("ModelData/models/STAGEMODEL.fbx", DxFbx::FbxLoader::eAxisSystem::eAxisOpenGL);
	m_stage->Initialize(m_camera->GetCamera().get(), "ModelData/textures/texture.jpg");
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

	
	return;
}


void SceneGame::Render(){
	if (GetAsyncKeyState('W') & 0x8000)
	{
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
	}
	std::cout << m_light->Translation()._x << "\n";
	std::cout << m_light->Translation()._z << "\n";

	m_camera->Render();
	if (GetAsyncKeyState('X') & 0x8000){
	m_stage->AllNodeRender(m_lightshader, DxModel::eRenderWay::eDiffuseLight);
	}
	else{
	m_stage->AllNodeRender(m_shader, DxModel::eRenderWay::eTexture);
	}

	m_player->Render(m_shader);
	m_cube->Render(m_shader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneGame::Shutdown(){

	return;
}
