/*
	Playerのレンダークラス
	描画処理を担当

*/
#ifndef _PLAYERRENDER_H
#define _PLAYERRENDER_H
#include "PlayerBase.h"
#include <ShaderBase.h>
#include <ModelBase.h>
#include <FbxModel.h>
class PlayerRender :
	private PlayerBase
{
		
	public:
		PlayerRender();
		PlayerRender(PlayerRender&);
		~PlayerRender();

		void Initialize()override; 
		PlayerBase::PlayerStatus& SendStatus()override;
		void SendStatus(PlayerBase::PlayerStatus&)override;
		void Rendering(const std::shared_ptr<aetherClass::FbxModel>, const std::shared_ptr<aetherClass::ShaderBase>);
		bool PlayAnimation();
	private:
		void Destroy()override;

};

#endif