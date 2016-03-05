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

	//�V�[���쐬
	GameScene *Scene = new SceneTitle;
	GameScene *Scene2 = new SceneEnd;
	GameScene *Scene3 = new SceneClear;


	//�V�[���o�^
	RegisterScene(Scene);
	RegisterScene(Scene2);
	RegisterScene(Scene3);

	
	// �J�����I�u�W�F�N�g�̍쐬
	m_camera = std::make_shared<ViewCamera>();
	m_camera->property._translation = Vector3(-100, -8, 692);
	m_camera->property._rotation = Vector3(-170.0f, 178.0f, 1.0f);


	//�T�E���h�̍쐬
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


	//��������e�N�X�`��
	for (int i = 0; i < 4; i++)
	{
		m_descTexture[i] = std::make_shared<Texture>();
	}

	m_descTexture[0]->Load("image/Controlls.png");	//�L�����ړ�
	m_descTexture[1]->Load("image/player_dash.png");	//����
	m_descTexture[2]->Load("image/player_kamera.png");	//�J����
	m_descTexture[3]->Load("image/Controlls2.png");	//���n��

	//�������������
	for (int i = 0; i < 4; i++)
	{
		m_desc[i] = std::make_shared<Rectangle3D>();
		m_desc[i]->Initialize();
		m_desc[i]->SetCamera(m_camera.get());
		m_desc[i]->SetTexture(m_descTexture[i].get());
	}
	m_desc[0]->property._transform._translation = Vector3(370.0f, 80.0f,40.0f);
	m_desc[0]->property._transform._scale = Vector3(150,-80,100);
	//m_desc[1]->property._transform._translation = Vector3(300.0f, -30.0f, 870.0f); //�z���������ƂȂ����N�����Ȃ��̂ŕs�v�摜������Ԃɏ����Ă��������܂����O�O�G
	m_desc[1]->property._transform._translation = Vector3(300.0f, -30.0f, 80000.0f);
	m_desc[1]->property._transform._scale = Vector3(-100, -100, 500);
	//m_desc[2]->property._transform._translation = Vector3(400.0f, 80.0f, 40.0f);//����
	m_desc[2]->property._transform._translation = Vector3(400.0f, 80.0f, 80000.0f);
	m_desc[2]->property._transform._scale = Vector3(100, -100, 500);
	m_desc[3]->property._transform._translation = Vector3(3075.0f,40.0f, 700.0f);
	m_desc[3]->property._transform._scale = Vector3(-200, -80, 500);
	m_desc[3]->property._transform._rotation._y = 90;


	// �V�F�[�_�[�̏ڍ׏��̐ݒ�
	ShaderDesc textureDesc;

	textureDesc._vertex._entryName = "vs_main";
	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";

	textureDesc._pixel._entryName = "ps_main";
	textureDesc._pixel._srcFile = L"Shader/Texture.ps";


	// �s�N�Z���V�F�[�_�[�̍쐬
	m_pixelShader = std::make_shared<PixelShader>();
	m_pixelShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	Material material;
	material._ambient._color = Color(1, 0, 0, 1);
	material._diffuse._color = Color(1, 0, 0, 1);
	material._specular._color = Color(1, 0, 0, 1);
	material._specularPower = 4;


	// ���C�g�̍쐬
	m_lightmanager = std::make_shared<LightManager>();
	m_lightmanager->Initialize();

	// �v���C���[�̍쐬
	m_player = std::make_shared<PlayerManager>();
	m_player->Initialize();//m_camera->GetCamera());

	m_player->Status() = PlayerBase::PlayerStatus();


	// �X�e�[�W���f���̍쐬
	m_stage = std::make_shared<FbxModel>();
	m_stage->LoadFBX("ModelData/models/Stage_Door2.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera.get());//m_camera->GetCamera().get());
	m_stage->property._transform._scale = Vector3(1.0f, 1.0f, -1.0f);

	m_stage->SetModelMaterialColor(Color(0.0, 0.1, 0.1, 1), eMatrerialType::eAmbient);
	m_stage->SetModelMaterialColor(Color(0.7, 0.6, 0.6, 0.0), eMatrerialType::eDiffuse);
	m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 1.0), eMatrerialType::eSpecular);
	//m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 0.0), eMatrerialType::eEmissive);

	// ��̍쐬
	m_rock = std::make_shared<RockManager>();
	m_rock->Initialize(m_camera.get());   //m_camera->GetCamera().get());

	//���̍쐬
	m_spear = std::make_shared<SpearManager>();
	m_spear->Initialize(m_camera.get());  //m_camera->GetCamera().get());

	//�ǂ̍쐬
	m_wall = std::make_shared<WallManager>();
	m_wall->Initialize(m_camera.get());   //m_camera->GetCamera().get());

	//������ǂ̍쐬
	m_fallwall = std::make_shared<FallingWallManager>();
	m_fallwall->Initialize(m_camera.get());


	//�i�r�Q�[�V����
	m_navigation = std::make_shared<NavigationManager>();
	m_navigation->Initialize(m_camera.get());

	// UI�̍쐬
	m_ui = std::make_shared<UiGame>();
	m_ui->Initialize();

	m_soumatou = std::make_shared<SoumatouManager>();
	m_soumatou->Initialize();


	//�e�L�X�g�̍쐬
	m_text = std::make_shared<TextManager>();
	m_text->Initialize(m_camera.get());


	// �}�e���A���V�F�[�_�[�쐬���̏��̐ݒ�
	ShaderDesc materialDesc;
	materialDesc._vertex._entryName = "vs_main";
	materialDesc._vertex._srcFile = L"Shader/MaterialVS.hlsl";
	materialDesc._pixel._entryName = "ps_main";
	materialDesc._pixel._srcFile = L"Shader/MaterialPS.hlsl";

	// �}�e���A���V�F�[�_�[�̍쐬
	m_materialShader = std::make_shared<MaterialShader>();
	m_materialShader->Initialize(materialDesc, ShaderType::eVertex | ShaderType::ePixel);
	m_materialShader->SetLight(m_lightmanager->GetLight().get());
	m_materialShader->SetCamera(m_camera.get());    //m_camera->GetCamera().get());
	m_lightmanager->GetLight()->property._translation = m_camera->property._translation;

	// �v���C���[�̍ŏ��̏�Ԃ̐ݒ�
	m_player->SetState(PlayerBase::ePlayerMoveState::eMove);


	//�e�C�x���g�̏�����
	m_trapState = eTrapState::eNull;
	m_naviState = eNaviState::eNull;
	m_rockState = eRockState::eNull;
	m_damageState = eDamageState::eNull;

	return true;
}


//�eUpdater���Ăяo��
bool SceneGame::Updater(){

	//�i�r�Q�[�V�����Ƃ̓����蔻��
	bool IsHitNavi = false;
	int hitNaviNumber = 0;

	for (int i = 0; i < m_navigation->NaviCnt(); i++){
		IsHitNavi = m_navigation->HitMesh(m_player->Get(), m_navigation->Navi_Get(i).m_navigation);
		if (IsHitNavi && !m_navigation->Navi_Get(i).m_isRunEnd){
		hitNaviNumber = i;
		//�i�r�Q�[�V������ID�̐ݒ�
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


	//�ǂƂ̓����蔻��
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

	//��
	m_wall->Update();

	//�v���C���[
	m_player->Update(m_camera, IsHitWall);
	
	//���C�g
	m_lightmanager->Update();


	//skybox
	m_skybox->property._transform._rotation._y += 0.05;


	//UI
	m_ui->Set(m_player->LifeGet());
	m_ui->Update();


	//�e�g���b�v�ƃv���C���[�̓����蔻��
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

	//�e�g���b�v�̃C�x���g�̌Ăяo��
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
	

	//�C�x���g���������Ă�����Update���Ă�
	if (m_rockState == eRockState::eRockEvent){
		m_rock->Update();
	}
	if (m_trapState == eTrapState::eSpearEvent){
		m_spear->Update();
	}
	if (m_trapState == eTrapState::eSpearEvent2){
		m_spear->Update2();
	}
	
	///	���肭��ǂɂ��ẮA��ԑJ�ڂ�����Ƒ����󒆂Œ�~����̂�
	///	�������Z�o���ċ쓮������`���ɕύX���Ă܂��B
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

//�`��
void SceneGame::Render(){

	//�J����
	m_camera->Render();

	//�X�e�[�W
	m_stage->Render(m_materialShader.get());

	//��
	m_wall->Render(m_pixelShader);
	
	//�v���C���[
	m_player->Render(m_materialShader);

	//�e�g���b�v
	m_rock->Render(m_pixelShader);
	m_spear->Render(m_materialShader);
	m_fallwall->Render(m_pixelShader);

	//���C�g
	m_lightmanager->Render();

	//�i�r�Q�[�V����
	m_navigation->Render(m_pixelShader);

	//UI
	m_ui->Render();

	//�e�L�X�g
	m_text->Render(m_pixelShader.get());

	//�X�J�C�{�b�N�X
	m_skybox->Render(m_pixelShader.get());

	m_soumatou->Render();
	
	//�������
	for (int i = 0; i < 4; i++)
	{
		m_desc[i]->Render(m_pixelShader.get());
	}

	return;
}

void SceneGame::Finalize(){

	return;
}

