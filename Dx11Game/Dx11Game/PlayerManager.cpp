#include "PlayerManager.h"


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
	//m_playerObject->LoadFBX("パス名");
	//m_playerObject->Initialize(camera.get(), "テクスチャのパス名");

	return true;
}
void PlayerManager::Render(const std::shared_ptr<DxShader::ShaderBase> shader){
	m_render->Rendering(m_playerObject,shader);

	return;
}
void PlayerManager::Update(float frame){
	m_updater->Updating(m_playerObject,frame);

	return;
}


PlayerBase::PlayerStatus PlayerManager::Status(){
	return m_updater->SendStatus();
}

void PlayerManager::Status(PlayerBase::PlayerStatus&){

	
	return;
}

bool PlayerManager::HitMesh(const std::shared_ptr<DxModel::ModelBase>&){
	return true;
}
bool PlayerManager::HitMesh(const std::shared_ptr<DxModel::FbxStaticMesh>&){
	return true;
}