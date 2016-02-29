#ifndef _PLAYERUPDATER_H
#define _PLAYERUPDATER_H
/*
Player��Updater�N���X
�X�V������S��



*/
#include "PlayerBase.h"
#include "GameSound.h"
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
//private:
//	enum class eKey{
//		eUp,
//		eDown,
//		eLeft,
//		eRight,
//		eNull
//	};
//
public:
	
	PlayerUpdater();
	PlayerUpdater(PlayerUpdater&);
	~PlayerUpdater();
	void Initialize()override;
	PlayerBase::PlayerStatus& SendStatus()override;
	void SendStatus(PlayerBase::PlayerStatus&)override;
	void Updating(const std::shared_ptr<aetherClass::FbxModel>&, std::shared_ptr<aetherClass::ViewCamera>,bool);
	bool HittingProcessor(aetherClass::ModelBase*, aetherClass::ModelBase*);
	bool HittingWall(aetherClass::ModelBase*, aetherClass::ModelBase*);

	//eKey GetKey();
	bool IsDamage();
private:
	void Move(const std::shared_ptr<aetherClass::FbxModel>& playerObject, std::shared_ptr<aetherClass::ViewCamera>,bool);  // �����Ă�Ƃ��̏���
	void Stand(const std::shared_ptr<aetherClass::FbxModel>& playerObject); // �����~�܂�Ƃ��̏���
	void Fall(const std::shared_ptr<aetherClass::FbxModel>& playerObject);  // �����鎞�̏���
	void Damage(const std::shared_ptr<aetherClass::FbxModel>& playerObject); // �_���[�W�󂯂����̏���
	void Destroy()override;
	aetherClass::Vector3 m_prevMoveDirection;

	void TimeSpiral();
	/*eKey m_KeyEvent;*/
private:
	int m_damageCounter;
	int m_daedCounter;
	bool m_damageFlg;
	std::shared_ptr<aetherClass::GameSound> m_playerSound;
	std::shared_ptr<aetherClass::GameSound> m_damegeSound;

	int m_mutekiTime;
};

#endif