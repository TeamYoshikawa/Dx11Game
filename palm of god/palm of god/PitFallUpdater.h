#pragma once
#include"PitFall.h"

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

	};

}