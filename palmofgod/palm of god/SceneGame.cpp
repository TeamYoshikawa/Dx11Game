#include "SceneGame.h"
#include <GameController.h>
#include <iostream>
#include <PixelShader.h>
#include"Cube.h"
using namespace aetherClass;
const std::string SceneGame::m_thisName = "Game";
SceneGame::SceneGame() :
GameScene(m_thisName, GetManager()){}


SceneGame::~SceneGame()
{
}

bool SceneGame::Initialize(){
	std::cout << "Initialize game scene" << std::endl;

	// UIの作成
	m_ui = std::make_shared<UiGame>();
	m_ui->Initialize();

	// カメラオブジェクトの作成
	m_camera = std::make_shared<CameraManager>();
	m_camera->Initialize();

	// シェーダーの詳細情報の設定
	ShaderDesc textureDesc;
	
	textureDesc._vertex._entryName = "vs_main";
	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";

	textureDesc._pixel._entryName = "ps_main";
	textureDesc._pixel._srcFile = L"Shader/ColorTextureAdd2.ps";


	
	// ピクセルシェーダーの作成
	m_pixelShader = std::make_shared<PixelShader>();
	m_pixelShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	Material material;
	material._ambient._color = Color(1, 0, 0, 1);
	material._diffuse._color = Color(1, 0, 0, 1);
	material._specular._color = Color(1, 0, 0, 1);
	material._specularPower = 4;

	// ライトの作成
	m_lightmanager = std::make_shared<LightManager>();
	m_lightmanager->Initialize();

	// プレイヤーの作成
	m_player = std::make_shared<PlayerManager>();
	m_player->Initialize(m_camera->GetCamera());


	// ステージモデルの作成
	m_stage = std::make_shared<FbxModel>();
	m_stage->LoadFBX("ModelData/models/STAGEKANZENBAN.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera->GetCamera().get());
	m_stage->GetTransform()._scale = Vector3(1.0f, 1.0f, -1.0f);

	m_stage->SetModelMaterialColor(Color(0.2, 0.0, 0.2, 1), eMatrerialType::eAmbient);
	m_stage->SetModelMaterialColor(Color(1, 1, 1, 1.0), eMatrerialType::eDiffuse);
	m_stage->SetModelMaterialColor(Color(1, 0, 0, 1.0), eMatrerialType::eSpecular);

	// 岩の作成
	m_rock = std::make_shared<RockManager>();
	m_rock->Initialize(m_camera->GetCamera().get());

	//槍の作成
	m_spear = std::make_shared<SpearManager>();
	m_spear->Initialize(m_camera->GetCamera().get());

	// マテリアルシェーダー作成時の情報の設定
	ShaderDesc materialDesc;
	materialDesc._vertex._entryName = "vs_main";
	materialDesc._vertex._srcFile = L"Shader/MaterialVS.hlsl";
	materialDesc._pixel._entryName = "ps_main";
	materialDesc._pixel._srcFile = L"Shader/MaterialPS.hlsl";

	// マテリアルシェーダーの作成
	m_materialShader = std::make_shared<MaterialShader>();
	m_materialShader->Initialize(materialDesc, ShaderType::eVertex | ShaderType::ePixel);
	m_materialShader->SetLight(m_lightmanager->GetLight().get());
	m_materialShader->SetCamera(m_camera->GetCamera().get());
	m_lightmanager->GetLight()->Translation() = m_camera->GetCamera()->Translation();

	// プレイヤーの最初の状態の設定
	m_player->SetState(PlayerBase::ePlayerMoveState::eMove);

	// ゲームの状態の設定
	m_gameState = GetGameState();
	std::cout << "Initialize compleate" << std::endl;
	return true;
}

bool SceneGame::Updater(){
	GameController::GetPointer()->Frame();
	m_gameState = GetGameState();
	// デバッグ用
	if (GameController::GetPointer()->IsRightButtonTrigger())
	{
		m_camera->NextCameraSet();
	}

	// プレイヤーが一定位置に進んだら
	if (m_player->IsChangeCamera())
	{
		m_ui->Update();
		m_camera->NextCameraSet();
	}

	FirstRockEvent();
	m_player->Update();
	m_lightmanager->Update();
	
	if (m_camera->eID13){
		m_spear->Update();
	}

	m_ui->Set(m_player->LifeGet());

	return true;
}

void SceneGame::Render(){

	m_ui->Render();

	m_camera->Render();
	m_lightmanager->Render();
	m_stage->Render(m_materialShader.get());

	m_player->Render(m_materialShader);

	m_rock->Render(m_pixelShader);
	m_spear->Render(m_pixelShader);
	return;
}

void SceneGame::Finalize(){

	return;
}

//
void SceneGame::FirstRockEvent(){
	if (m_gameState!=SceneGame::eGameState::eRockEvent)
	{
		return;
	}
	

	m_rock->Update();
	switch (m_rock->FlagGet())
	{
	case SAVE:
		m_player->SetState(PlayerBase::ePlayerMoveState::eStatnd);
		break;
	case ON:
		// 押されないでONなら進む初めてダメージをくらいに行く
		if (!m_rock->GetIsPushButton())
		{
			if (!m_player->GetIsDamage())
			{
				m_player->SetState(PlayerBase::ePlayerMoveState::eMove);
			}
		
			if (m_player->HitMesh(m_rock->Get()))
			{
				m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
			}
			
		}
		break;
	case OFF:
		m_player->SetState(PlayerBase::ePlayerMoveState::eMove);
		m_gameState = eGameState::eNull;
		break;

	}
	return;
}

SceneGame::eGameState SceneGame::GetGameState(){
	switch (m_player->Status()._navigationID)
	{
	case 4:
	case 5:
	case 6:
		return SceneGame::eGameState::eRockEvent;

	default:
		return SceneGame::eGameState::eNull;
	}
}