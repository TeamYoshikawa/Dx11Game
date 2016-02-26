#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
/*
Player管理クラス
updaterとrenderのオブジェクトを保持し、
playerの状態の管理などを請け負うとこ？

*/
#include "PlayerBase.h"
#include "PlayerUpdater.h"
#include "PlayerRender.h"
#include <Cube.h>
#include<ViewCamera.h>
#include <FbxModel.h>
#include <Texture.h>
#include <memory>
class PlayerManager
{

public:
	PlayerManager();
	~PlayerManager();

	bool Initialize();//const std::shared_ptr<aetherClass::ViewCamera>);

	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update(const std::shared_ptr<aetherClass::ViewCamera>);
	PlayerBase::PlayerStatus& Status();
	void Status(PlayerBase::PlayerStatus&);

	// 外部オブジェクトとの当たり判定用
	bool HitMesh(std::shared_ptr<aetherClass::ModelBase>&);


	std::shared_ptr<aetherClass::ModelBase> Get();

	int LifeGet();

	void SetState(PlayerBase::ePlayerMoveState);

	bool GetIsDamage();

	bool IsDead();

private:
	// 次に行く道をセット
	void SetNextPoint(const std::shared_ptr<aetherClass::ModelBase>&);

	// コライドをプレイヤーについてくるようにする
	void UpdateColliderBox();

private:

	std::unique_ptr<PlayerUpdater> m_updater;		// プレイヤーの更新オブジェクト
	std::unique_ptr<PlayerRender> m_render;	        // プレイヤーの描画オブジェくト
	std::shared_ptr<aetherClass::Texture> m_collideTexture;
	std::shared_ptr<aetherClass::FbxModel> m_playerObject; // プレイヤーのモデルオブジェクト
	std::shared_ptr<aetherClass::ModelBase> m_collideBox;	// 実際に当たり判定を行うオブジェクト
	std::shared_ptr<aetherClass::ViewCamera> m_camera;
	std::shared_ptr<aetherClass::ShaderBase> m_collideBoxShader;
	bool m_isCahngeCamera;		// カメラを切り替えるフラグ
};

#endif