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
#include "PlayerNavigation.h"
#include <memory>
#include <CollideBoxOBB.h>
class PlayerManager
{

	public:
		PlayerManager();
		~PlayerManager();

		bool Initialize(const std::shared_ptr<DxCamera::ViewCamera>);
		
		void Render(const std::shared_ptr<DxShader::ShaderBase>);
		void Update(float);
		PlayerBase::PlayerStatus& Status();
		void Status(PlayerBase::PlayerStatus&);

		// 外部オブジェクトとの当たり判定用
		bool HitMesh(const std::shared_ptr<DxModel::ModelBase>&);
		bool HitMesh(const std::shared_ptr<DxModel::FbxStaticMesh>&);

		void NextSerch();

		bool IsChangeCamera();	// カメラを切り替えるかの判別用
		std::unique_ptr<PlayerNavigation> m_navigation; // プレイヤーのルート用オブジェクト
	private:
		// 次に行く道をセット
		void SetNextPoint(const std::shared_ptr<DxModel::ModelBase>&);

	private:
		std::unique_ptr<PlayerUpdater> m_updater;		// プレイヤーの更新オブジェクト
		std::unique_ptr<PlayerRender> m_render;	        // プレイヤーの描画オブジェくト
		

		std::shared_ptr<DxModel::FbxStaticMesh> m_playerObject; // プレイヤーのモデルオブジェクト
		std::shared_ptr<DxModel::ModelBase> m_collideBox;	// 実際に当たり判定を行うオブジェクト

		CollideBoxOBB m_collider;	// 当たり判定を行う関数
		bool m_isCahngeCamera;		// カメラを切り替えるフラグ
		
};

#endif