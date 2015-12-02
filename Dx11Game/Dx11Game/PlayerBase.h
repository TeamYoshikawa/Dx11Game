#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H
/*
	�v���C���[�̊��N���X
	updater��render�ŋ��L����p�����[�^�[��ێ�

*/
#include <Windows.h>

#include <Direct3DManager.h>
struct Vector3{
	float _x, _y, _z;
};

class PlayerBase
{

	protected:

		// ��{�X�e�[�^�X
		struct PlayerStatus{
			PlayerStatus(){
				SecureZeroMemory(&_vector, sizeof(_vector));
				_speed = 0.0f;
			}
			Vector3 _vector;
			float _speed;
		};

		// ��Ԃ�ǉ����Ă���
		enum class ePlayerState{
			eNull,
			eStand,
		};
	public:
		PlayerBase();
		~PlayerBase();

		PlayerStatus& GetStatus();
		ePlayerState GetNowState();
		void SetState(ePlayerState);
	private:
		static PlayerStatus m_status;
		static ePlayerState m_state;
};
#endif