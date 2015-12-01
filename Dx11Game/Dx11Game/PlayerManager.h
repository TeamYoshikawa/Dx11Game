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
	private:
		std::unique_ptr<PlayerUpdater> m_updater;
		std::unique_ptr<PlayerRender> m_render;

	public:
		PlayerManager();
		~PlayerManager();

		bool Initialize();
		void Render();
		void Update();
};

#endif