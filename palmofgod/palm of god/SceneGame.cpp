#include "SceneGame.h"
#include <GameController.h>
#include <iostream>
#include <PixelShader.h>
#include "FbxStaticModel.h"
using namespace aetherClass;
const std::string SceneGame::m_thisName = "Game";
SceneGame::SceneGame() :
GameScene(m_thisName, GetManager()){}


SceneGame::~SceneGame()
{
}
#include"Cube.h"
std::shared_ptr<aetherClass::Cube>m_cube;
bool SceneGame::Initialize(){
	std::cout << "Start game" << std::endl;


	m_camera = std::make_shared<CameraManager>();
	m_camera->Initialize();

	m_shader = std::make_shared<PixelShader>();
	ShaderDesc textureDesc;
	textureDesc._vertex._entryName = "vs_main";
	textureDesc._vertex._srcFile = L"Shader/MaterialVS.hlsl";

	textureDesc._pixel._entryName = "ps_main";
	textureDesc._pixel._srcFile = L"Shader/MaterialPS.hlsl";
	m_shader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);
	
	m_cube = std::make_shared<Cube>();
	m_cube->Initialize();
	m_cube->SetCamera(m_camera->GetCamera().get());
	m_cube->GetTransform()._scale = 10;
	m_cube->GetTransform()._translation = m_camera->GetCamera()->Translation();
	Material material;
	material._ambient._color = Color(1, 0, 0, 1);
	material._diffuse._color = Color(1, 0, 0, 1);
	material._specular._color = Color(1, 0, 0, 1);
	material._specularPower = 4;// _color = Color(1, 0, 0, 1);
	m_cube->GetMaterial() = material;
	/*
	m_light = std::make_shared<Light>();
	m_light->Translation() = Vector3(-50, 50, -50);
	m_lightshader->SetLight(m_light.get());
	*/

	m_stagemanager = std::make_shared<StageManager>();
	m_stagemanager->Initialize();

	m_player = std::make_shared<PlayerManager>();
	m_player->Initialize(m_camera->GetCamera());

	m_stage = std::make_shared<FbxStaticModel>();
	m_stage->LoadFBX("ModelData/models/STAGEMODEL.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera->GetCamera().get());
	m_stage->GetTransform()._scale = Vector3(1.0f, 1.0f, -1.0f);

	m_positionCheckBoxTexture = std::make_shared<Texture>();
	m_positionCheckBoxTexture->Load("ModelData/textures/cylinder_template.jpg");
	m_positionCheck = std::make_shared<Cube>();
	m_positionCheck->Initialize();
	m_positionCheck->SetCamera(m_camera->GetCamera().get());
	m_positionCheck->SetTexture(m_positionCheckBoxTexture.get());
	m_positionCheck->GetTransform()._scale = Vector3(50, 50, 50);
	m_positionCheck->GetTransform()._translation=Vector3(-280.0f, -100.f, 185.0f);

	m_rock = std::make_shared<RockManager>();
	m_rock->Initialize(m_camera->GetCamera().get());

	m_lightshader = std::make_shared<MaterialShader>();
	ShaderDesc lightDesc;
	lightDesc._vertex._entryName = "vs_main";
	lightDesc._vertex._srcFile = L"Shader/MaterialVS.hlsl";

	lightDesc._pixel._entryName = "ps_main";
	lightDesc._pixel._srcFile = L"Shader/MaterialPS.hlsl";
	m_lightshader->Initialize(lightDesc, ShaderType::eVertex | ShaderType::ePixel);
	m_lightshader->SetLight(m_stagemanager->GetLight().get());
	m_lightshader->SetCamera(m_camera->GetCamera().get());
	m_stagemanager->GetLight()->Translation() = m_camera->GetCamera()->Translation();
	return true;
}


bool SceneGame::Updater(){
	GameController::GetPointer()->Frame();

	if (GameController::GetPointer()->IsKeyDown(DIK_W))
	{
		m_stagemanager->GetLight()->Translation()._z += 1;
	}

	if (GameController::GetPointer()->IsKeyDown(DIK_S))
	{
		m_stagemanager->GetLight()->Translation()._z -= 1;
	}


	if (GameController::GetPointer()->IsKeyDown(DIK_A))
	{
		m_stagemanager->GetLight()->Translation()._x += 1;
	}


	if (GameController::GetPointer()->IsKeyDown(DIK_D))
	{
		m_stagemanager->GetLight()->Translation()._x -= 1;
	}

	if (GameController::GetPointer()->IsKeyDown(DIK_Q))
	{
		m_stagemanager->GetLight()->Translation()._y += 1;
	}

	if (GameController::GetPointer()->IsKeyDown(DIK_E))
	{
		m_stagemanager->GetLight()->Translation()._y -= 1;
	}

	/*std::cout << "X :" << m_positionCheck->GetTransform()._translation._x << "\t";
	std::cout << "Y :" << m_positionCheck->GetTransform()._translation._y << "\t";
	std::cout << "Z :" << m_positionCheck->GetTransform()._translation._z << std::endl;
*/
	if (m_player->IsChangeCamera())
	{
		m_camera->NextCameraSet();
		m_stagemanager->NextLightSet();	
	}

	m_player->Update(0.01f);
	m_stagemanager->Update();

	if (m_player->Status()._navigationID == 3)
	{
		m_rock->Update();
	}
	m_cube->GetTransform()._translation = m_stagemanager->GetLight()->Translation();
	
	Vector3 translation = m_cube->GetTransform()._translation;
	printf("%f,%f,%f\n\n", translation._x, translation._y, translation._z);
	return true;
}


void SceneGame::Render(){

	m_camera->Render();
	m_stagemanager->Render();
	m_stage->Render(m_lightshader.get());

	m_player->Render(m_shader);
	m_cube->Render(m_lightshader.get());
	m_rock->Render(m_shader);
//	m_positionCheck->Render(m_shader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneGame::Finalize(){

	return;
}
