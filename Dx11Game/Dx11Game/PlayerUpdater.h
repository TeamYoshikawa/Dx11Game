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
	
	public:
		PlayerUpdater();
		PlayerUpdater(PlayerUpdater&);
		~PlayerUpdater();
		bool Initialize();
		void Frame();
		

};

#endif