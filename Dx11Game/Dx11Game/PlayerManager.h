#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
/*
	Player�Ǘ��N���X
	updater��render�̃I�u�W�F�N�g��ێ����A
	player�̏�Ԃ̊Ǘ��Ȃǂ𐿂������Ƃ��H

*/
#include "PlayerBase.h"
#include "PlayerUpdater.h"
#include "PlayerRender.h"
#include <memory>
class PlayerManager
{

	public:
		PlayerManager();
		~PlayerManager();

		bool Initialize(const std::shared_ptr<DxCamera::ViewCamera>);
		
		void Render(const std::shared_ptr<DxShader::ShaderBase>);
		void Update(float);
		PlayerBase::PlayerStatus Status();
		void Status(PlayerBase::PlayerStatus&);

		bool HitMesh(const std::shared_ptr<DxModel::ModelBase>&);
		bool HitMesh(const std::shared_ptr<DxModel::FbxStaticMesh>&);

	private:
		std::unique_ptr<PlayerUpdater> m_updater;
		std::unique_ptr<PlayerRender> m_render;
		std::shared_ptr<DxModel::FbxStaticMesh> m_playerObject;
};

#endif