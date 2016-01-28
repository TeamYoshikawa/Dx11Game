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

	// UI�̍쐬
	m_ui = std::make_shared<UiGame>();
	m_ui->Initialize();

	// �J�����I�u�W�F�N�g�̍쐬
	m_camera = std::make_shared<CameraManager>();
	m_camera->Initialize();

	// �V�F�[�_�[�̏ڍ׏��̐ݒ�
	ShaderDesc textureDesc;
	
	textureDesc._vertex._entryName = "vs_main";
	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";

	textureDesc._pixel._entryName = "ps_main";
	textureDesc._pixel._srcFile = L"Shader/ColorTextureAdd2.ps";


	
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
	m_player->Initialize(m_camera->GetCamera());


	// �X�e�[�W���f���̍쐬
	m_stage = std::make_shared<FbxModel>();
	m_stage->LoadFBX("ModelData/models/STAGEKANZENBAN.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera->GetCamera().get());
	m_stage->GetTransform()._scale = Vector3(1.0f, 1.0f, -1.0f);

	m_stage->SetModelMaterialColor(Color(0.2, 0.0, 0.2, 1), eMatrerialType::eAmbient);
	m_stage->SetModelMaterialColor(Color(1, 1, 1, 1.0), eMatrerialType::eDiffuse);
	m_stage->SetModelMaterialColor(Color(1, 0, 0, 1.0), eMatrerialType::eSpecular);

	// ��̍쐬
	m_rock = std::make_shared<RockManager>();
	m_rock->Initialize(m_camera->GetCamera().get());

	//���̍쐬
	m_spear = std::make_shared<SpearManager>();
	m_spear->Initialize(m_camera->GetCamera().get());

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
	m_materialShader->SetCamera(m_camera->GetCamera().get());
	m_lightmanager->GetLight()->Translation() = m_camera->GetCamera()->Translation();

	// �v���C���[�̍ŏ��̏�Ԃ̐ݒ�
	m_player->SetState(PlayerBase::ePlayerMoveState::eMove);

	// �Q�[���̏�Ԃ̐ݒ�
	m_gameState = GetGameState();
	std::cout << "Initialize compleate" << std::endl;
	return true;
}

bool SceneGame::Updater(){
	GameController::GetPointer()->Frame();
	m_gameState = GetGameState();
	// �f�o�b�O�p
	if (GameController::GetPointer()->IsRightButtonTrigger())
	{
		m_camera->NextCameraSet();
	}

	// �v���C���[�����ʒu�ɐi�񂾂�
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
		// ������Ȃ���ON�Ȃ�i�ޏ��߂ă_���[�W�����炢�ɍs��
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