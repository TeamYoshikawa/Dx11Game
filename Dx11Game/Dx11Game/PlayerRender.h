/*
	Player�̃����_�[�N���X
	�`�揈����S��

*/
#ifndef _PLAYERRENDER_H
#define _PLAYERRENDER_H
#include "PlayerBase.h"
class PlayerRender :
	private PlayerBase
{
	private:

		bool InitializeObject()override;
		void Run()override;
	public:
		PlayerRender();
		PlayerRender(PlayerRender&);
		~PlayerRender();
};

#endif