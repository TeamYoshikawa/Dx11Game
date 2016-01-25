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
#include <FbxModel.h>
#include <Texture.h>
#include <memory>
class PlayerManager
{

	public:
		PlayerManager();
		~PlayerManager();

		bool Initialize(const std::shared_ptr<aetherClass::ViewCamera>);
		
		void Render(const std::shared_ptr<aetherClass::ShaderBase>);
		void Update(float);
		PlayerBase::PlayerStatus& Status();
		void Status(PlayerBase::PlayerStatus&);

		// 外部オブジェクトとの当たり判定用
		bool HitMesh(const std::shared_ptr<aetherClass::ModelBase>&);
		bool HitMesh(const std::shared_ptr<aetherClass::FbxModel>&);

		void NextSerch();

		bool IsChangeCamera();	// カメラを切り替えるかの判別用
		std::unique_ptr<PlayerNavigation> m_navigation; // プレイヤーのルート用オブジェクト

		std::shared_ptr<aetherClass::ModelBase> get_collideBox();
	private:
		// 次に行く道をセット
		void SetNextPoint(const std::shared_ptr<aetherClass::ModelBase>&);

	private:

		std::unique_ptr<PlayerUpdater> m_updater;		// プレイヤーの更新オブジェクト
		std::unique_ptr<PlayerRender> m_render;	        // プレイヤーの描画オブジェくト
		std::shared_ptr<aetherClass::Texture> m_collideTexture;
		std::shared_ptr<aetherClass::FbxModel> m_playerObject; // プレイヤーのモデルオブジェクト
		std::shared_ptr<aetherClass::ModelBase> m_collideBox;	// 実際に当たり判定を行うオブジェクト

		bool m_isCahngeCamera;		// カメラを切り替えるフラグ
		
};

#endif