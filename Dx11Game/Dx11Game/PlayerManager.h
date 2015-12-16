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

		bool HitMesh(const std::shared_ptr<DxModel::ModelBase>&);
		bool HitMesh(const std::shared_ptr<DxModel::FbxStaticMesh>&);

		void NextSerch();

	private:
		void SerchNextPoint(const std::shared_ptr<DxModel::ModelBase>&);
	private:
		std::unique_ptr<PlayerUpdater> m_updater;
		std::unique_ptr<PlayerRender> m_render;

		std::unique_ptr<PlayerNavigation> m_navigation;
		std::shared_ptr<DxModel::FbxStaticMesh> m_playerObject;
		std::shared_ptr<DxModel::ModelBase> m_collideBox;
};

#endif