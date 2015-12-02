#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}


bool PlayerManager::Initialize(std::shared_ptr<DxCamera::ViewCamera> camera, std::string fileName){
	m_updater = std::make_unique<PlayerUpdater>();
	m_updater->Initialize();
	m_render = std::make_unique<PlayerRender>();
	m_render->Initialize(camera, fileName);

	return true;
}
void PlayerManager::Render(DxShader::ShaderBase* shader, DxModel::eRenderWay way){
	m_render->Frame(shader,way);

	return;
}
void PlayerManager::Update(){
	m_updater->Frame();

	return;
}