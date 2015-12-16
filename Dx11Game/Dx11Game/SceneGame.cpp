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

	HINSTANCE hInstance = GetModuleHandle(NULL);
	DxController::GameController::Create(hInstance, hWnd);

	return;
}
int a = 0;
void SceneGame::Updata(){
	DxController::GameController::GetPointer()->Frame();


	if (DxController::GameController::GetPointer()->IsLeftButtonTrigger())
	{
		m_camera->ChangeCamera(1);
		m_player->NextSerch();
	}

	m_player->Update(1);



	
	return;
}


void SceneGame::Render(){

	m_camera->Render();
	m_stage->AllNodeRender(m_shader, DxModel::eRenderWay::eTexture);

	m_player->Render(m_shader);

	

	return;
}

void SceneGame::Shutdown(){

	return;
}
