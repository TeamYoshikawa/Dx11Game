#include "PlayerRender.h"

PlayerRender::PlayerRender()
{

}
PlayerRender::PlayerRender(PlayerRender& other){}

PlayerRender::~PlayerRender()
{

}

void PlayerRender::Initialize(){

	return;
}

void PlayerRender::Destroy(){

	return;
}

void PlayerRender::Rendering(const std::shared_ptr<DxModel::FbxStaticMesh> object, const std::shared_ptr<DxShader::ShaderBase> shader){
	object->AllNodeRender(shader,DxModel::eRenderWay::eTexture);
	return;
}

bool PlayerRender::PlayAnimation(){

	return true;
}

void PlayerRender::SendStatus(PlayerBase::PlayerStatus&){
	return;
}

PlayerBase::PlayerStatus& PlayerRender::SendStatus(){
	return SendShareStatus();
}