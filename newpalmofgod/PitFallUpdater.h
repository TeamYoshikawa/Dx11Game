#pragma once
#include"PitFall.h"

#define ON 1
#define OFF 0

namespace Pitfall{
	class PitFallUpdater
	{
	private:
		PitFallUpdater(const PitFallUpdater&){};
		void operator =(const PitFallUpdater &){};

		void Open(aetherClass::ModelBase*);
		void Close(aetherClass::ModelBase*);
		
		float m_speed;
	public:
		PitFallUpdater();
		~PitFallUpdater() = default;

		void Update(aetherClass::ModelBase*model,bool buttonState);
		
		int FlagGet();

		int s_flag = OFF;
	};

}