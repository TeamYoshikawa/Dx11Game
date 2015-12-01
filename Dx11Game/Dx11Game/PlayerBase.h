#ifndef _PLAYERBASE_H
#define _PLAYERBASE_H
/*
	プレイヤーの基底クラス
	updaterとrenderで共有するパラメーターを保持

*/
#include <Windows.h>
struct Vector3{
	float _x, _y, _z;
};

class PlayerBase
{

	protected:
		struct Status{
			Status(){
				SecureZeroMemory(&_vector, sizeof(_vector));
				_speed = 0.0f;
			}
			Vector3 _vector;
			float _speed;
		};
	public:
		PlayerBase();
		~PlayerBase();

		Status& GetStatus();
		void Process();
	private:
		static Status m_status;

	private:
		virtual bool InitializeObject() = 0;
		virtual void Run() = 0;
};
#endif