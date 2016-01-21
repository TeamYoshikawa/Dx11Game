#include "PlayerRender.h"
#include <FbxStaticModel.h>
using namespace aetherClass;
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

void PlayerRender::Rendering(const std::shared_ptr<FbxStaticModel> object, 
	const std::shared_ptr<ShaderBase> shader){
	
	object->Render(shader.get());
	
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