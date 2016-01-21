#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
	PlayerのUpdaterクラス
	更新処理を担当



*/
#include "PlayerBase.h"
#include <memory>
#include <FbxStaticModel.h>
#include <ModelBase.h>

class PlayerUpdater :
	private PlayerBase
{
	
	public:
		PlayerUpdater();
		PlayerUpdater(PlayerUpdater&);
		~PlayerUpdater();
		void Initialize()override;
		PlayerBase::PlayerStatus& SendStatus()override;
		void SendStatus(PlayerBase::PlayerStatus&)override;
		void Updating(const std::shared_ptr<aetherClass::FbxStaticModel>&, float);
		void FaceTheObject(const std::shared_ptr<aetherClass::FbxStaticModel>&, const std::shared_ptr<aetherClass::ModelBase>&);
		bool HittingProcessor(const std::shared_ptr<aetherClass::FbxStaticModel>&);
		bool HittingProcessor(const std::shared_ptr<aetherClass::FbxStaticModel>&, const std::shared_ptr<aetherClass::ModelBase>&);
	private:
		void Destroy()override;

};

#endif