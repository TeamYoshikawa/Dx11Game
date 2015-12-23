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

// 描画処理
void PlayerManager::Render(const std::shared_ptr<DxShader::ShaderBase> shader){
	m_render->Rendering(m_playerObject,shader);
	//m_collideBox->Render(shader, DxModel::eRenderWay::eTexture);


	// ナビゲーションの確認用描画
	// 基本的には隠した状態にする

	//m_navigation->Render(shader);
	return;
}

// 更新処理
void PlayerManager::Update(float frame){
	// 現在のナビゲーションの場所を取得
	Status()._navigationID = m_navigation->GetNavigationID();
	if (m_navigation->GetNavigationID() == 3)
	{
		return;
	}
	m_updater->Updating(m_playerObject,frame);
	m_collideBox->Translation() = m_playerObject->Transform()._translation;

	// コリジョンボックスがプレイヤーを囲むようにする
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

// 引数で指定されたオブジェクトに対して向かう
void PlayerManager::SetNextPoint(const std::shared_ptr<DxModel::ModelBase>& nextPointObject){
	
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

// ModelBaseの派生オブジェクトとの当たり判定用
bool PlayerManager::HitMesh(const std::shared_ptr<DxModel::ModelBase>& other){

	if (!m_updater->HittingProcessor(m_collideBox, other))
	{
		return false;
	}
	
	return true;
}

// Fbx同士の当たり判定用
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