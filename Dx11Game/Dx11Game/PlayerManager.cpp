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
	m_playerObject->Transform()._translation = DxMath::Vector3(-20.0f, 0.0f, 0.0f);
	m_playerObject->Transform()._scale = DxMath::Vector3(0.05f, 0.05f, 0.05f);


	m_collideBox = std::make_shared<DxModel::Cube>();
	m_collideBox->Initialize(camera.get(),"ModelData/textures/texture.jpg");
	
	m_collideBox->Translation() = m_playerObject->Transform()._translation;
	m_collideBox->Scaling(DxMath::Vector3(1.0f, 2.0f, 1.0f));
	

	return true;
}
void PlayerManager::Render(const std::shared_ptr<DxShader::ShaderBase> shader){
	m_render->Rendering(m_playerObject,shader);
	m_collideBox->Render(shader, DxModel::eRenderWay::eTexture);
	return;
}
void PlayerManager::Update(float frame){
	m_updater->Updating(m_playerObject,frame);
	m_collideBox->Translation() = m_playerObject->Transform()._translation;
	m_collideBox->Translation()._x = m_playerObject->Transform()._translation._x-0.95;
	return;
}

// 引数で指定されたオブジェクトに対して向かう
void PlayerManager::SerchNextPoint(const std::shared_ptr<DxModel::ModelBase>& nextPointObject){
	
	// アップデーターに役割を任せる
	m_updater->FaceTheObject(m_playerObject, nextPointObject);

	return;
}

PlayerBase::PlayerStatus& PlayerManager::Status(){
	return m_updater->SendStatus();
}

void PlayerManager::Status(PlayerBase::PlayerStatus& status){

	return;
}

bool PlayerManager::HitMesh(const std::shared_ptr<DxModel::ModelBase>& other){
	if (!m_updater->HIttingProcessor(m_collideBox, other))
	{
		return false;
	}
	
	return true;
}
bool PlayerManager::HitMesh(const std::shared_ptr<DxModel::FbxStaticMesh>&){

	return true;
}