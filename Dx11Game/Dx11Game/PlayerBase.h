#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H
/*
	プレイヤーの基底クラス
	updaterとrenderで共有するパラメーターを保持

*/
#include <Windows.h>

#include <Direct3DManager.h>
struct Vector3{
	float _x, _y, _z;
};

class PlayerBase
{
	public:

		
		// 状態を追加していく
		enum class ePlayerMoveState{
			eNull = 0,
			eStand,
			eRight,
			eStraight,
			eBack,
		};

		// 基本ステータス
		struct PlayerStatus{
			PlayerStatus(){
				SecureZeroMemory(&_vector, sizeof(_vector));
				m_state = ePlayerMoveState::eNull;
				_speed = 0.0f;
			}
			Vector3 _vector;
			ePlayerMoveState m_state;
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