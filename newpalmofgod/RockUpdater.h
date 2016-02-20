#pragma once
#include <ModelBase.h>
//#include"Sphere.h"
#include<GameController.h>

#define OFF 0
#define ON  1

namespace n_Rock{
	class RockUpdater
	{
	private:
		enum eEvent{
			eNormal,
			eThrow
		};
	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void First(aetherClass::ModelBase*);
		void Second(aetherClass::ModelBase*);

		float speed= 1.0f;

		int flag = OFF;
		
		eEvent m_event;
		int m_countDown;
	public:
		RockUpdater();
		~RockUpdater() = default;

		void Update(aetherClass::ModelBase*model);
		
	};
}