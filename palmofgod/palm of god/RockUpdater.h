#pragma once
#include <ModelBase.h>
//#include"Sphere.h"

namespace n_Rock{
	class RockUpdater
	{
	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void Open(aetherClass::ModelBase*);
		void Close(aetherClass::ModelBase*);

		float speed= 1.0f;
		
	public:
		RockUpdater();
		~RockUpdater() = default;

		


		void Update(aetherClass::ModelBase*model, bool buttonState);
		
	};
}