#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
	Player��Updater�N���X
	�X�V������S��



*/
#include "PlayerBase.h"
class PlayerUpdater :
	private PlayerBase
{
	private:
		bool InitializeObject()override; 
		void Run()override;
	public:
		PlayerUpdater();
		PlayerUpdater(PlayerUpdater&);
		~PlayerUpdater();

};

#endif