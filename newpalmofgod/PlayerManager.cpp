#include "PlayerManager.h"
#include <iostream>
#include <Physics.h>
#include <PixelShader.h>
using namespace aetherClass;
using namespace aetherFunction;
PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}


bool PlayerManager::Initialize(const std::shared_ptr<ViewCamera> camera){
	m_updater = std::make_unique<PlayerUpdater>();
	m_updater->Initialize();

	m_render = std::make_unique<PlayerRender>();
	m_render->Initialize();

	m_playerObject = std::make_shared<FbxModel>();
	m_playerObject->LoadFBX("ModelData/models/player5.fbx", eAxisSystem::eAxisOpenGL);
	m_playerObject->SetCamera(camera.get());
	m_playerObject->GetTransform()._translation = Vector3(-100.0f, 105.0f, 670.0f);
	m_playerObject->GetTransform()._scale = Vector3(1.3f, -1.3f, 1.3f);


	m_collideTexture = std::make_shared<Texture>();
	m_collideTexture->Load("ModelData/textures/Chips_Cover.jpg");
	m_collideBox = std::make_shared<Cube>();
	m_collideBox->Initialize();
	m_collideBox->SetTexture(m_collideTexture.get());
	m_collideBox->SetCamera(camera.get());
	const Vector3 translation = m_playerObject->GetTransform()._translation;
	m_collideBox->GetTransform()._translation = translation;
	m_collideBox->GetTransform()._scale = Vector3(70.0f, 100.0f, 20.0f);

	ShaderDesc desc;
	desc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	desc._vertex._entryName = "vs_main";
	desc._pixel._srcFile = L"Shader/ColorTextureAdd2.ps";
	desc._pixel._entryName = "ps_main";

	m_collideBoxShader = std::make_shared <aetherClass::PixelShader>();
	m_collideBoxShader->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);

	m_isCahngeCamera = false;
	return true;
}

// �`�揈��
void PlayerManager::Render(const std::shared_ptr<ShaderBase> shader){
	m_render->Rendering(m_playerObject, shader);

	// �i�r�Q�[�V�����̊m�F�p�`��
	// ��{�I�ɂ͉B������Ԃɂ���
	//m_collideBox->Render(m_collideBoxShader.get());
	//m_navigation->Render(shader);
	return;
}

// �X�V����
void PlayerManager::Update(){
	// ���݂̃i�r�Q�[�V�����̏ꏊ���擾

	m_updater->Updating(m_playerObject);

	UpdateColliderBox();

	return;
}

void PlayerManager::SetState(PlayerBase::ePlayerMoveState state){
	Status()._moveState = state;
}

void PlayerManager::UpdateColliderBox(){
	// �R���W�����{�b�N�X���v���C���[���͂ނ悤�ɂ���
	const Vector3 translation = m_playerObject->GetTransform()._translation;
	m_collideBox->GetTransform()._translation = translation;
	const Vector3 rotation = m_playerObject->GetTransform()._rotation;
	m_collideBox->GetTransform()._rotation = rotation;
}



// �v���C���[�̏��𑗂�
PlayerBase::PlayerStatus& PlayerManager::Status(){
	return m_updater->SendStatus();
}

void PlayerManager::Status(PlayerBase::PlayerStatus& status){
	return;
}

int PlayerManager::LifeGet(){
	return Status()._life;
}

// ModelBase�̔h���I�u�W�F�N�g�Ƃ̓����蔻��p
bool PlayerManager::HitMesh(std::shared_ptr<ModelBase>& other){

	if (!m_updater->HittingProcessor(m_collideBox, other))
	{
		return false;
	}

	return true;
}


bool PlayerManager::GetIsDamage(){
	return m_updater->IsDamage();
}

bool PlayerManager::IsDead(){
	return Status()._isDead;
}

std::shared_ptr<aetherClass::ModelBase> PlayerManager::Get(){

	return m_collideBox;
}
