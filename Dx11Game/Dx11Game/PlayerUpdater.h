#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
	PlayerのUpdaterクラス
	更新処理を担当



*/
#include "PlayerBase.h"
#include <memory>
#include <FbxStaticMesh.h>
#include <ModelBase.h>
#include <CollideBoxOBB.h>
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
		void FaceTheObject(const std::shared_ptr<DxModel::FbxStaticMesh>&, const std::shared_ptr<DxModel::ModelBase>&);
		bool HittingProcessor(const std::shared_ptr<DxModel::FbxStaticMesh>&);
		bool HIttingProcessor(const std::shared_ptr<DxModel::ModelBase>&, const std::shared_ptr<DxModel::ModelBase>&);
	private:
		void Destroy()override;

	private:
		CollideBoxOBB m_boxCllider;

};

#endif