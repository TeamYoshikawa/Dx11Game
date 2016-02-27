#include "SceneGame.h"
#include <GameController.h>
#include <iostream>
#include <PixelShader.h>
#include "SceneTitle.h"
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

	GameScene *Scene = new SceneTitle;

	RegisterScene(Scene);

	// UIの作成
	m_ui = std::make_shared<UiGame>();
	m_ui->Initialize();

	// カメラオブジェクトの作成
	m_camera = std::make_shared<ViewCamera>();
	m_camera->Translation() = Vector3(-100, -8, 692);
	m_camera->Rotation() = Vector3(-170.0f, 178.0f, 1.0f);

    m_sound = std::make_shared<GameSound>();
	m_sound->Load("Sound/BGM/BGM.wav");
    m_sound->SetValume(-3000);
	m_sound->PlayToLoop();

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
	m_player->Initialize();//m_camera->GetCamera());


    // ステージモデルの作成
    m_stage = std::make_shared<FbxModel>();
    m_stage->LoadFBX("ModelData/models/STAGEKANZENBAN.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera.get());//m_camera->GetCamera().get());
    m_stage->GetTransform()._scale = Vector3(1.0f, 1.0f, -1.0f);

    m_stage->SetModelMaterialColor(Color(0.0, 0.1, 0.1, 1), eMatrerialType::eAmbient);
    m_stage->SetModelMaterialColor(Color(0.7, 0.6, 0.6, 0.0), eMatrerialType::eDiffuse);
    m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 1.0), eMatrerialType::eSpecular);
	//m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 0.0), eMatrerialType::eEmissive);

    // 岩の作成
    m_rock = std::make_shared<RockManager>();
	m_rock->Initialize(m_camera.get());   //m_camera->GetCamera().get());

    m_spear = std::make_shared<SpearManager>();
	m_spear->Initialize(m_camera.get());  //m_camera->GetCamera().get());


    m_wall = std::make_shared<WallManager>();
	m_wall->Initialize(m_camera.get());   //m_camera->GetCamera().get());


	//ナビゲーション
	m_navigation = std::make_shared<NavigationManager>();
	m_navigation->Initialize(m_camera.get());


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
	m_materialShader->SetCamera(m_camera.get());    //m_camera->GetCamera().get());
    m_lightmanager->GetLight()->Translation() = m_camera->Translation();
	
    // プレイヤーの最初の状態の設定
    m_player->SetState(PlayerBase::ePlayerMoveState::eMove);

    m_gameState = eGameState::eNull;

    return true;
}

bool SceneGame::Updater(){

	m_wall->Update();

	m_navigation->Update();


	if (m_player->HitMesh(m_rock->Get().get()))
	{
		m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
	}

	if (m_player->HitMesh(m_spear->Get().get()))
	{
		m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
	}

	if (m_rock->HitMesh(m_player->Get(),m_rock->S_Get()))
	{
		m_gameState = eGameState::eRockEvent;
	}

	if (m_gameState == eGameState::eRockEvent){
		m_rock->Update();
	}

	if (m_spear->HitMesh(m_player->Get(), m_spear->S_Get())){
		m_gameState = eGameState::eSpearEvent;
	}
	if (m_gameState == eGameState::eSpearEvent){
		m_spear->Update();
	}


	//壁との当たり判定
	bool IsHitWall = false;

	for (int i = 0; i < m_wall->WallCnt(); i++){
		
		IsHitWall = m_player->HitWallMesh(m_wall->Get(i));
		if (IsHitWall){
			break;
		}
	}

	m_player->Update(m_camera, IsHitWall);

	m_lightmanager->Update();

	m_ui->Set(m_player->LifeGet());

	if (GameController::GetKey().IsKeyDown(DIK_R)){
		ChangeScene("Title",false);
	}

	m_ui->Update();
	return true;
}

void SceneGame::Render(){

	m_camera->Render();

	m_ui->Render();

	m_spear->Render(m_pixelShader);

	m_lightmanager->Render();
	
	m_stage->Render(m_materialShader.get());

	m_player->Render(m_materialShader);

	m_rock->Render(m_pixelShader);

	m_wall->Render(m_pixelShader);

	m_navigation->Render(m_pixelShader);

	return;
}

void SceneGame::Finalize(){

	return;
}

