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
#include <memory>
class PlayerManager
{
	private:
		std::unique_ptr<PlayerUpdater> m_updater;
		std::unique_ptr<PlayerRender> m_render;

	public:
		PlayerManager();
		~PlayerManager();

		bool Initialize(std::shared_ptr<DxCamera::ViewCamera>,std::string fileName="null");
		void Render(DxShader::ShaderBase*, DxModel::eRenderWay);
		void Update();
};

#endif