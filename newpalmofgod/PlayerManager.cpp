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


bool PlayerManager::Initialize(){//const std::shared_ptr<ViewCamera> camera){
	m_updater = std::make_unique<PlayerUpdater>();
	m_updater->Initialize();

	m_render = std::make_unique<PlayerRender>();
	m_render->Initialize();

	// プレイヤーが持つカメラの初期化
	m_camera = std::make_shared<ViewCamera>();
	m_camera->property._translation = Vector3(-100, -8, 692);
	m_camera->property._rotation = Vector3(-170.0f, 178.0f, 1.0f);

	m_playerObject = std::make_shared<FbxModel>();
	m_playerObject->LoadFBX("ModelData/models/player5.fbx", eAxisSystem::eAxisOpenGL);
	m_playerObject->SetCamera(m_camera.get());
	m_playerObject->property._transform._translation = Vector3(-50.0f, 105.0f, 670.0f);
	m_playerObject->property._transform._scale = Vector3(1.3f, -1.3f, 1.3f);

	m_collideTexture = std::make_shared<Texture>();
	m_collideTexture->Load("ModelData/textures/Chips_Cover.jpg");
	m_collideBox = std::make_shared<Cube>();
	m_collideBox->Initialize();
	m_collideBox->SetTexture(m_collideTexture.get());
	m_collideBox->SetCamera(m_camera.get());
	const Vector3 translation = m_playerObject->property._transform._translation;
	m_collideBox->property._transform._translation = translation;
	m_collideBox->property._transform._scale = Vector3(70.0f, 100.0f, 20.0f);

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

// 描画処理
void PlayerManager::Render(const std::shared_ptr<ShaderBase> shader){
	m_render->Rendering(m_playerObject, shader);

	// ナビゲーションの確認用描画
	// 基本的には隠した状態にする
	//m_collideBox->Render(m_collideBoxShader.get());
	//m_navigation->Render(shader);
	return;
}

// 更新処理
void PlayerManager::Update(const std::shared_ptr<aetherClass::ViewCamera> camera,bool IsHitWall){
	// 現在のナビゲーションの場所を取得

	m_updater->Updating(m_playerObject,camera,IsHitWall);

	UpdateColliderBox();

	return;
}

void PlayerManager::SetState(PlayerBase::ePlayerMoveState state){
	Status()._moveState = state;
}

void PlayerManager::UpdateColliderBox(){
	// コリジョンボックスがプレイヤーを囲むようにする
	const Vector3 translation = m_playerObject->property._transform._translation;
	m_collideBox->property._transform._translation = translation;
	const Vector3 rotation = m_playerObject->property._transform._rotation;
	m_collideBox->property._transform._rotation = rotation;
}



// プレイヤーの情報を送る
PlayerBase::PlayerStatus& PlayerManager::Status(){
	return m_updater->SendStatus();
}

void PlayerManager::Status(PlayerBase::PlayerStatus& status){
	return;
}

int PlayerManager::LifeGet(){
	return Status()._life;
}

// ModelBaseの派生オブジェクトとの当たり判定用
bool PlayerManager::HitMesh(ModelBase *other){

		if (!m_updater->HittingProcessor(m_collideBox.get(), other))
		{
			return false;
		}
	
		return true;
	
}

bool PlayerManager::HitWallMesh(std::shared_ptr<ModelBase> wall)
{
	
	if (m_updater->HittingWall(m_collideBox.get(), wall.get())){
			return true;
		}
	return false;
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

std::shared_ptr<aetherClass::ViewCamera> PlayerManager::GetCamera()
{
	return m_camera;
}
