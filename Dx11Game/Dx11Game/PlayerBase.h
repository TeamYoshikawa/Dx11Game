#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H
/*
	�v���C���[�̊��N���X
	updater��render�ŋ��L����p�����[�^�[��ێ�

*/
#include <Windows.h>

#include <Direct3DManager.h>
#include <Vector3.h>

class PlayerBase
{
	public:

		
		// ��Ԃ�ǉ����Ă���
		enum class ePlayerMoveState{
			eNull = 0,
			eMove,
			eStatnd,
			eFall,
		};

		// ��{�X�e�[�^�X
		struct PlayerStatus{
			PlayerStatus(){
				_vector = 0.0f;
				_moveState = ePlayerMoveState::eNull;
				_speed = 0.0f;
				_nextMoveDirection = 0.0f;
			}
			DxMath::Vector3 _vector;
			DxMath::Vector3 _nextMoveDirection;
			ePlayerMoveState _moveState;
			float _speed;
		};


	public:
		PlayerBase();
		virtual ~PlayerBase();

		virtual PlayerStatus& SendShareStatus();
		virtual PlayerStatus& SendStatus();
		virtual void SendStatus(PlayerStatus&);
	private:
		virtual void Initialize() = 0;
		virtual void Destroy() = 0;

	private:
		static PlayerStatus m_status;


};
#endif