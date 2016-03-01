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

bool SceneGame::Initialize()
{
	std::cout << "Initialize game scene" << std::endl;

	//シーン作成
	GameScene *Scene = new SceneTitle;

	//シーン登録
	RegisterScene(Scene);

	// UIの作成
	m_ui = std::make_shared<UiGame>();
	m_ui->Initialize();

	// カメラオブジェクトの作成
	m_camera = std::make_shared<ViewCamera>();
	m_camera->Translation() = Vector3(-100, -8, 692);
	m_camera->Rotation() = Vector3(-170.0f, 178.0f, 1.0f);


	//サウンドの作成
	m_sound = std::make_shared<GameSound>();
	m_sound->Load("Sound/BGM/BGM.wav");
	m_sound->SetValume(-3000);
	m_sound->PlayToLoop();

	m_texture = std::make_shared<Texture>();
	m_texture->Load("SkyBoxTexture/night.png");

	// スカイボックスの作成
	m_skybox = std::make_shared<aetherClass::Skybox>();
	m_skybox->Initialize();
	m_skybox->SetCamera(m_camera.get());
	m_skybox->SetTexture(m_texture.get());

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

	//槍の作成
	m_spear = std::make_shared<SpearManager>();
	m_spear->Initialize(m_camera.get());  //m_camera->GetCamera().get());

	//壁の作成
	m_wall = std::make_shared<WallManager>();
	m_wall->Initialize(m_camera.get());   //m_camera->GetCamera().get());

	//落ちる壁の作成
	m_fallwall = std::make_shared<FallingWallManager>();
	m_fallwall->Initialize(m_camera.get());


	//ナビゲーション
	m_navigation = std::make_shared<NavigationManager>();
	m_navigation->Initialize(m_camera.get());

	//テキストの作成
	m_text = std::make_shared<TextManager>();
	m_text->Initialize(m_camera.get());


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


	//各イベントの初期化
	m_trapState = eTrapState::eNull;
	m_naviState = eNaviState::eNull;

	return true;
}


//各Updaterを呼び出す
bool SceneGame::Updater(){

	//ナビゲーションとの当たり判定
	bool IsHitNavi = false;
	int hitNaviNumber = 0;

	for (int i = 0; i < m_navigation->NaviCnt(); i++){
		IsHitNavi = m_navigation->HitMesh(m_player->Get(), m_navigation->Navi_Get(i));
		if (IsHitNavi){
			hitNaviNumber = i;
			//ナビゲーションのIDの設定
			m_navigation->Update(hitNaviNumber);
			m_naviState = eNaviState::eNaviEvent;
			break;
		}
	}

	if (m_naviState == eNaviState::eNaviEvent){
		m_text->SetID(m_navigation->Navi_IDGet());
		m_naviState=eNaviState::eNull;
	}


	//壁との当たり判定
	bool IsHitWall = false;
	for (int i = 0; i < m_wall->WallCnt(); i++){
		IsHitWall = m_player->HitWallMesh(m_wall->Get(i));
		if (IsHitWall){
			break;
		}
	}

	//壁
	m_wall->Update();

	//プレイヤー
	m_player->Update(m_camera, IsHitWall);

	//ライト
	m_lightmanager->Update();

	//UI
	m_ui->Set(m_player->LifeGet());
	m_ui->Update();


	//各トラップとプレイヤーの当たり判定
	if (m_player->HitMesh(m_rock->Get().get()))
	{
		m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
	}

	if (m_player->HitMesh(m_spear->Get().get()))
	{
		m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
	}

	if (m_player->HitMesh(m_fallwall->GetFallingWall().get()))
	{
		m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
	}

	//各トラップのイベントの呼び出し
	if (m_rock->HitMesh(m_player->Get(), m_rock->Switch_Get()))
	{
		m_trapState = eTrapState::eRockEvent;
	}

	if (m_spear->HitMesh(m_player->Get(), m_spear->S_Get()))
	{
		m_trapState = eTrapState::eSpearEvent;
	}

	if (m_fallwall->HitMesh(m_player->Get(), m_fallwall->GetFallingWall()))
	{
		m_trapState = eTrapState::efallwall;
	}

	//イベントが発生していたらUpdateを呼ぶ
	if (m_trapState == eTrapState::eRockEvent){
		m_rock->Update();
	}
	if (m_trapState == eTrapState::eSpearEvent){
		m_spear->Update();
	}
	//if (m_trapState == eTrapState::efallwall){
	m_fallwall->Update();
	//}


	//タイトルに戻る
	if (GameController::GetKey().IsKeyDown(DIK_R)){
		ChangeScene("Title", false);
	}

	return true;
}

//描画
void SceneGame::Render(){

	//カメラ
	m_camera->Render();

	//UI
	m_ui->Render();

	//ステージ
	m_stage->Render(m_materialShader.get());

	//壁
	m_wall->Render(m_pixelShader);

	//プレイヤー
	m_player->Render(m_materialShader);

	//各トラップ
	m_rock->Render(m_pixelShader);
	m_spear->Render(m_pixelShader);
	m_fallwall->Render(m_pixelShader);

	//ライト
	m_lightmanager->Render();

	//ナビゲーション
	m_navigation->Render(m_pixelShader);

	//テキスト
	m_text->Render(m_pixelShader.get());

	//スカイボックス
	m_skybox->Render(m_pixelShader.get());

	return;
}

void SceneGame::Finalize(){

	return;
}

