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
	m_playerObject->LoadFBX("ModelData/models/player5.fbx",eAxisSystem::eAxisOpenGL);
	m_playerObject->SetCamera(camera.get());
	m_playerObject->GetTransform()._translation = Vector3(-100.0f, 105.0f, 670.0f);
	m_playerObject->GetTransform()._scale = Vector3(1.3f, -1.3f, 1.3f);
	
	m_navigation = std::make_unique<PlayerNavigation>();
	m_navigation->Initialize(camera);

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


	SetNextPoint(m_navigation->GetNavigationBox());

	m_isCahngeCamera = false;
	return true;
}

// 描画処理
void PlayerManager::Render(const std::shared_ptr<ShaderBase> shader){
	//m_render->Rendering(m_playerObject,shader);	

	// ナビゲーションの確認用描画
	// 基本的には隠した状態にする
	//m_collideBox->Render(m_collideBoxShader.get());
	//m_navigation->Render(shader);
	return;
}

// 更新処理
void PlayerManager::Update(){
	// 現在のナビゲーションの場所を取得
	Status()._navigationID = m_navigation->GetNavigationID();
	if (m_navigation->GetNavigationID() == 14)
	{
		return;
	}
	m_updater->Updating(m_playerObject);

	UpdateColliderBox();

	// TODO : ナビゲーションにぶつかった時の処理
	if (aetherFunction::CollideBoxOBB(*m_collideBox, *m_navigation->GetNavigationBox()))
	{
		m_navigation->NextSet();
		SetNextPoint(m_navigation->GetNavigationBox());
		if (m_navigation->GetNavigationID() != 4){
			m_isCahngeCamera = true;
		}
	}
	else
	{
		m_isCahngeCamera = false;
	}

	return;
}

void PlayerManager::SetState(PlayerBase::ePlayerMoveState state){
	Status()._moveState = state;
}

void PlayerManager::UpdateColliderBox(){
	// コリジョンボックスがプレイヤーを囲むようにする
	const Vector3 translation = m_playerObject->GetTransform()._translation;
	m_collideBox->GetTransform()._translation = translation;
	const Vector3 rotation = m_playerObject->GetTransform()._rotation;
	m_collideBox->GetTransform()._rotation = rotation;
}

// 引数で指定されたオブジェクトに対して向かう
void PlayerManager::SetNextPoint(const std::shared_ptr<ModelBase>& nextPointObject){
	
	// アップデーターに役割を任せる
	m_updater->FaceTheObject(m_playerObject, nextPointObject);

	return;
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
bool PlayerManager::HitMesh(std::shared_ptr<ModelBase>& other){

	if (!m_updater->HittingProcessor(m_collideBox, other))
	{
		return false;
	}

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

bool PlayerManager::GetIsDamage(){
	return m_updater->IsDamage();
}

bool PlayerManager::IsDead(){
	return Status()._isDead;
}