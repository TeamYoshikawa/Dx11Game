#include "PlayerManager.h"
#include <iostream>

PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}


bool PlayerManager::Initialize(const std::shared_ptr<DxCamera::ViewCamera> camera){
	m_updater = std::make_unique<PlayerUpdater>();
	m_updater->Initialize();

	m_render = std::make_unique<PlayerRender>();
	m_render->Initialize();

	m_playerObject = std::make_shared<DxModel::FbxStaticMesh>();
	m_playerObject->LoadFBX("ModelData/models/player5.fbx",DxFbx::FbxLoader::eAxisSystem::eAxisOpenGL);
	m_playerObject->Initialize(camera.get(), "ModelData/textures/tex.png");
	m_playerObject->Transform()._translation = DxMath::Vector3(-280.0f, -100.f, 185.0f);
	m_playerObject->Transform()._scale = DxMath::Vector3(1.f, -1.f, 1.f);

	m_navigation = std::make_unique<PlayerNavigation>();
	m_navigation->Initialize(camera);


	m_collideBox = std::make_shared<DxModel::Cube>();
	m_collideBox->Initialize(camera.get(),"ModelData/textures/Chips_Cover.jpg");
	
	const DxMath::Vector3 translation = m_playerObject->Transform()._translation;
	m_collideBox->Translation(translation);
	m_collideBox->Scaling(DxMath::Vector3(20.0f, 100.0f, 20.0f));
	
	SetNextPoint(m_navigation->GetNavigationBox());

	m_isCahngeCamera = false;
	return true;
}

// �`�揈��
void PlayerManager::Render(const std::shared_ptr<DxShader::ShaderBase> shader){
	m_render->Rendering(m_playerObject,shader);
	//m_collideBox->Render(shader, DxModel::eRenderWay::eTexture);


	// �i�r�Q�[�V�����̊m�F�p�`��
	// ��{�I�ɂ͉B������Ԃɂ���

	//m_navigation->Render(shader);
	return;
}

// �X�V����
void PlayerManager::Update(float frame){
	// ���݂̃i�r�Q�[�V�����̏ꏊ���擾
	Status()._navigationID = m_navigation->GetNavigationID();
	if (m_navigation->GetNavigationID() == 3)
	{
		return;
	}
	m_updater->Updating(m_playerObject,frame);
	m_collideBox->Translation() = m_playerObject->Transform()._translation;

	// �R���W�����{�b�N�X���v���C���[���͂ނ悤�ɂ���
	const DxMath::Vector3 translation = m_playerObject->Transform()._translation;
	m_collideBox->Translation(translation);

	if (m_collider.IsCollideOBB(m_collideBox, m_navigation->GetNavigationBox()))
	{
		m_navigation->NextSet();
		SetNextPoint(m_navigation->GetNavigationBox());
		m_isCahngeCamera = true;
	}
	else
	{
		m_isCahngeCamera = false;
	}
	return;
}

// �����Ŏw�肳�ꂽ�I�u�W�F�N�g�ɑ΂��Č�����
void PlayerManager::SetNextPoint(const std::shared_ptr<DxModel::ModelBase>& nextPointObject){
	
	// �A�b�v�f�[�^�[�ɖ�����C����
	m_updater->FaceTheObject(m_playerObject, nextPointObject);

	return;
}

// �v���C���[�̏��𑗂�
PlayerBase::PlayerStatus& PlayerManager::Status(){
	return m_updater->SendStatus();
}

void PlayerManager::Status(PlayerBase::PlayerStatus& status){

	return;
}

// ModelBase�̔h���I�u�W�F�N�g�Ƃ̓����蔻��p
bool PlayerManager::HitMesh(const std::shared_ptr<DxModel::ModelBase>& other){

	if (!m_updater->HittingProcessor(m_collideBox, other))
	{
		return false;
	}
	
	return true;
}

// Fbx���m�̓����蔻��p
bool PlayerManager::HitMesh(const std::shared_ptr<DxModel::FbxStaticMesh>&){

	return true;
}


void PlayerManager::NextSerch(){
	SetNextPoint(m_navigation->GetNavigationBox());
}

bool PlayerManager::IsChangeCamera(){
	if (!m_isCahngeCamera)
	{
		return false;
	}

	NextSerch();
	return true;
}