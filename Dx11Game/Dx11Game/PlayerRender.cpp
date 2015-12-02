#include "PlayerRender.h"
#include <Cube.h>

PlayerRender::PlayerRender()
{
	m_playerObject = nullptr;
}
PlayerRender::PlayerRender(PlayerRender& other){}

PlayerRender::~PlayerRender()
{

}

bool PlayerRender::Initialize(const std::shared_ptr<DxCamera::ViewCamera> camera, std::string fileName){
	m_playerObject = std::make_shared<DxModel::Cube>();
	m_playerObject->Initialize(camera.get(), fileName.c_str());
	return true;
}

void PlayerRender::Frame(DxShader::ShaderBase* shader, DxModel::eRenderWay way){
	m_playerObject->Render(shader, way);
	return;
}