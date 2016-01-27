#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H
/*
	プレイヤーの基底クラス
	updaterとrenderで共有するパラメーターを保持

*/
#include <Windows.h>

#include <Direct3DManager.h>
#include <Vector3.h>

class PlayerBase
{
	public:

		
		// 状態を追加していく
		enum class ePlayerMoveState{
			eNull = 0,
			eMove,
			eStatnd,
			eFall,
		};

		// 基本ステータス
		struct PlayerStatus{
			PlayerStatus(){
				_vector = 0.0f;
				_moveState = ePlayerMoveState::eNull;
				_speed = 0.0f;
				_nextMoveDirection = 0.0f;
				_life = 3;
			}
			aetherClass::Vector3 _vector;
			aetherClass::Vector3 _nextMoveDirection;
			ePlayerMoveState _moveState;
			float _speed;
			int _navigationID;
			int _life;
			bool _muteki;
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