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

	protected:

		// 基本ステータス
		struct PlayerStatus{
			PlayerStatus(){
				SecureZeroMemory(&_vector, sizeof(_vector));
				_speed = 0.0f;
			}
			Vector3 _vector;
			float _speed;
		};

		// 状態を追加していく
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