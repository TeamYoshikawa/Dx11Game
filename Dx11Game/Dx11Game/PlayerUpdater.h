#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
	PlayerのUpdaterクラス
	更新処理を担当



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