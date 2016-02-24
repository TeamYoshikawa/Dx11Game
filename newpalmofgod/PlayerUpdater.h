#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
Player��Updater�N���X
�X�V������S��



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
	void Move(const std::shared_ptr<aetherClass::FbxModel>& playerObject);  // �����Ă�Ƃ��̏���
	void Stand(const std::shared_ptr<aetherClass::FbxModel>& playerObject); // �����~�܂�Ƃ��̏���
	void Fall(const std::shared_ptr<aetherClass::FbxModel>& playerObject);  // �����鎞�̏���
	void Damage(const std::shared_ptr<aetherClass::FbxModel>& playerObject); // �_���[�W�󂯂����̏���
	void Destroy()override;

private:
	int m_damageCounter;
	int m_daedCounter;
	bool m_damageFlg;
};

#endif