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
		void Initialize()override;
		PlayerBase::PlayerStatus& SendStatus()override;
		void SendStatus(PlayerBase::PlayerStatus&)override;
		void Updating(const std::shared_ptr<DxModel::FbxStaticMesh>&, float);
		bool HittingProcessor(const std::shared_ptr<DxModel::FbxStaticMesh>&);
		bool HIttingProcessor(const std::shared_ptr<DxModel::ModelBase>&);
	private:
		void Destroy()override;
};

#endif