#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
PlayerのUpdaterクラス
更新処理を担当



*/
#include "PlayerBase.h"
#include <memory>
#include <FbxModel.h>
#include <ModelBase.h>


namespace{
	const int kDamageWaitTime = 10000;
	const int kDeadWaitTime = 300;
}
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
	void Updating(const std::shared_ptr<aetherClass::FbxModel>&);
	void FaceTheObject(const std::shared_ptr<aetherClass::FbxModel>&, const std::shared_ptr<aetherClass::ModelBase>&);
	bool HittingProcessor(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);

	bool IsDamage();
private:
	void Move(const std::shared_ptr<aetherClass::FbxModel>& playerObject);  // 動いてるときの処理
	void Stand(const std::shared_ptr<aetherClass::FbxModel>& playerObject); // 立ち止まるときの処理
	void Fall(const std::shared_ptr<aetherClass::FbxModel>& playerObject);  // 落ちる時の処理
	void Damage(const std::shared_ptr<aetherClass::FbxModel>& playerObject); // ダメージ受けた時の処理
	void Destroy()override;

private:
	int m_damageCounter;
	int m_daedCounter;
	bool m_damageFlg;
};

#endif