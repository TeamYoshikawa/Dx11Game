#include "SceneGame.h"
#include <GameController.h>
#include <iostream>
#include <PixelShader.h>
#include "SceneTitle.h"
#include "SceneClear.h"
#include"Singleton.h"
#include"ResultData.h"


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
	GameScene *Scene2 = new SceneEnd;
	GameScene *Scene3 = new SceneClear;


	//シーン登録
	RegisterScene(Scene);
	RegisterScene(Scene2);
	RegisterScene(Scene3);

	
	// カメラオブジェクトの作成
	m_camera = std::make_shared<ViewCamera>();
	m_camera->property._translation = Vector3(-100, -8, 692);
	m_camera->property._rotation = Vector3(-170.0f, 178.0f, 1.0f);


	//サウンドの作成
	m_sound = std::make_shared<GameSound>();
	m_sound->Load("Sound/BGM/BGM.wav");
	m_sound->SetValume(-3000);
	m_sound->PlayToLoop();

	Texture *skytexture;

	skytexture = new Texture;
	skytexture->Load("skybox/night.png");

	m_skybox = std::make_shared<Skybox>();
	m_skybox->Initialize();
	m_skybox->SetCamera(m_camera.get());
	m_skybox->SetTexture(skytexture);


	//操作説明テクスチャ
	for (int i = 0; i < 4; i++)
	{
		m_descTexture[i] = std::make_shared<Texture>();
	}

	m_descTexture[0]->Load("image/Controlls.png");	//キャラ移動
	m_descTexture[1]->Load("image/player_dash.png");	//走る
	m_descTexture[2]->Load("image/player_kamera.png");	//カメラ
	m_descTexture[3]->Load("image/Controlls2.png");	//走馬灯

	//操作説明初期化
	for (int i = 0; i < 4; i++)
	{
		m_desc[i] = std::make_shared<Rectangle3D>();
		m_desc[i]->Initialize();
		m_desc[i]->SetCamera(m_camera.get());
		m_desc[i]->SetTexture(m_descTexture[i].get());
	}
	m_desc[0]->property._transform._translation = Vector3(370.0f, 80.0f,40.0f);
	m_desc[0]->property._transform._scale = Vector3(150,-80,100);
	//m_desc[1]->property._transform._translation = Vector3(300.0f, -30.0f, 870.0f); //配列個数いじるとなぜか起動しないので不要画像を亜空間に消えていただきました＾＾；
	m_desc[1]->property._transform._translation = Vector3(300.0f, -30.0f, 80000.0f);
	m_desc[1]->property._transform._scale = Vector3(-100, -100, 500);
	//m_desc[2]->property._transform._translation = Vector3(400.0f, 80.0f, 40.0f);//同上
	m_desc[2]->property._transform._translation = Vector3(400.0f, 80.0f, 80000.0f);
	m_desc[2]->property._transform._scale = Vector3(100, -100, 500);
	m_desc[3]->property._transform._translation = Vector3(3075.0f,40.0f, 700.0f);
	m_desc[3]->property._transform._scale = Vector3(-200, -80, 500);
	m_desc[3]->property._transform._rotation._y = 90;


	// シェーダーの詳細情報の設定
	ShaderDesc textureDesc;

	textureDesc._vertex._entryName = "vs_main";
	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";

	textureDesc._pixel._entryName = "ps_main";
	textureDesc._pixel._srcFile = L"Shader/Texture.ps";


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

	m_player->Status() = PlayerBase::PlayerStatus();


	// ステージモデルの作成
	m_stage = std::make_shared<FbxModel>();
	m_stage->LoadFBX("ModelData/models/Stage_Door2.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera.get());//m_camera->GetCamera().get());
	m_stage->property._transform._scale = Vector3(1.0f, 1.0f, -1.0f);

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

	// UIの作成
	m_ui = std::make_shared<UiGame>();
	m_ui->Initialize();

	m_soumatou = std::make_shared<SoumatouManager>();
	m_soumatou->Initialize();


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
	m_lightmanager->GetLight()->property._translation = m_camera->property._translation;

	// プレイヤーの最初の状態の設定
	m_player->SetState(PlayerBase::ePlayerMoveState::eMove);


	//各イベントの初期化
	m_trapState = eTrapState::eNull;
	m_naviState = eNaviState::eNull;
	m_rockState = eRockState::eNull;
	m_damageState = eDamageState::eNull;

	return true;
}


//各Updaterを呼び出す
bool SceneGame::Updater(){

	//ナビゲーションとの当たり判定
	bool IsHitNavi = false;
	int hitNaviNumber = 0;

	for (int i = 0; i < m_navigation->NaviCnt(); i++){
		IsHitNavi = m_navigation->HitMesh(m_player->Get(), m_navigation->Navi_Get(i).m_navigation);
		if (IsHitNavi && !m_navigation->Navi_Get(i).m_isRunEnd){
		hitNaviNumber = i;
		//ナビゲーションのIDの設定
		m_navigation->Update(hitNaviNumber);
		m_naviState = eNaviState::eNaviEvent;
		break;
	}
}

	if (m_naviState == eNaviState::eNaviEvent){
		m_text->SetID(m_navigation->Navi_IDGet());
		if (m_text->GetTime() > 150){
			m_naviState = eNaviState::eNull;
		}
	}


	//壁との当たり判定
	bool IsHitWall = false;
	for (int i = 0; i < m_wall->WallCnt(); i++){
		IsHitWall = m_player->HitWallMesh(m_wall->Get(i));
		if (IsHitWall){
			break;
		}
	}

	if (m_player->HitWallMesh(m_fallwall->GetFallingWall()))
	{
		IsHitWall = true;
	}

	m_soumatou->Update();

	//壁
	m_wall->Update();

	//プレイヤー
	m_player->Update(m_camera, IsHitWall);
	
	//ライト
	m_lightmanager->Update();


	//skybox
	m_skybox->property._transform._rotation._y += 0.05;


	//UI
	m_ui->Set(m_player->LifeGet());
	m_ui->Update();


	//各トラップとプレイヤーの当たり判定
	if (m_player->HitMesh(m_rock->Get().get()))
	{
		m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
		m_damageState=eDamageState::eDamageEvent;
	}

	for (int i = 0; i < m_spear->SpearCnt(); i++){
		if (m_player->HitMesh(m_spear->Get(i).get()))
		{
			m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
			m_damageState = eDamageState::eDamageEvent;
		}
	}
	

	for (int i = 0; i < m_spear->SpearCnt2(); i++){
		if (m_player->HitMesh(m_spear->Get2(i).get()))
		{
			m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
			m_damageState = eDamageState::eDamageEvent;
		}
	}

	if (m_player->HitMesh(m_fallwall->GetCollider().get()))
	{
		m_player->SetState(PlayerBase::ePlayerMoveState::eDamage);
		ChangeScene("End", LoadState::eUnuse, LoadWaitState::eUnuse);
	}

	//各トラップのイベントの呼び出し
	if (m_rock->HitMesh(m_player->Get(), m_rock->Switch_Get()))
	{
		m_rockState = eRockState::eRockEvent;
	}

	if (m_spear->HitMesh(m_player->Get(), m_spear->Switch_Get())){
		m_trapState = eTrapState::eSpearEvent;
	}
	if (m_spear->HitMesh2(m_player->Get(), m_spear->Switch_Get2())){
		m_trapState = eTrapState::eSpearEvent2;
	}
	if (m_rock->Get()->property._transform._translation._x > 6200){
		m_rockState = eRockState::eNull;
	}


	float a = m_player->Get()->property._transform._translation._x;
	float b = m_fallwall->GetFallingWall()->property._transform._translation._x;
	float distance = a - b;
	

	//イベントが発生していたらUpdateを呼ぶ
	if (m_rockState == eRockState::eRockEvent){
		m_rock->Update();
	}
	if (m_trapState == eTrapState::eSpearEvent){
		m_spear->Update();
	}
	if (m_trapState == eTrapState::eSpearEvent2){
		m_spear->Update2();
	}
	
	///	迫りくる壁については、状態遷移をすると槍が空中で停止するので
	///	距離を算出して駆動させる形式に変更してます。
	if (distance >= -1500 && distance <= 1000)
	{
		m_fallwall->Update();
	}

	if (m_player->LifeGet() == 0){
		ChangeScene("End", LoadState::eUnuse, LoadWaitState::eUnuse);
	}
	if (m_navigation->HitMesh(m_player->Get(), m_navigation->Clear_Get())){
		ChangeScene("Clear", LoadState::eUnuse, LoadWaitState::eUnuse);
	}

	Singleton<ResultData>::GetInstance().LifePointSet(m_player->LifeGet());
	Singleton<ResultData>::GetInstance().SoumatouCountSet(m_soumatou->SoumatouGet());

	static int damage_cnt = 0;
	if (m_damageState == eDamageState::eDamageEvent){
		m_soumatou->DamageFlagTrue();
		damage_cnt++;
		std::cout << damage_cnt << std::endl;
	}

	if (damage_cnt > 150){
		damage_cnt = 0;
		m_damageState = eDamageState::eNull;
		m_soumatou->DamageFlagFalse();

	}


	/*std::cout << "x"<<m_camera->property._translation._x;
	std::cout << "y" << m_camera->property._translation._y;
	std::cout << "z" << m_camera->property._translation._z;*/
	return true;
}

//描画
void SceneGame::Render(){

	//カメラ
	m_camera->Render();

	//ステージ
	m_stage->Render(m_materialShader.get());

	//壁
	m_wall->Render(m_pixelShader);
	
	//プレイヤー
	m_player->Render(m_materialShader);

	//各トラップ
	m_rock->Render(m_pixelShader);
	m_spear->Render(m_materialShader);
	m_fallwall->Render(m_pixelShader);

	//ライト
	m_lightmanager->Render();

	//ナビゲーション
	m_navigation->Render(m_pixelShader);

	//UI
	m_ui->Render();

	//テキスト
	m_text->Render(m_pixelShader.get());

	//スカイボックス
	m_skybox->Render(m_pixelShader.get());

	m_soumatou->Render();
	
	//操作説明
	for (int i = 0; i < 4; i++)
	{
		m_desc[i]->Render(m_pixelShader.get());
	}

	return;
}

void SceneGame::Finalize(){

	return;
}

