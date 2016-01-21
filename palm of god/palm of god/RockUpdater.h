#pragma once
#include"Rock.h"
//#include"Sphere.h"

namespace n_Rock{
	class RockUpdater
	{
	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void Open(aetherClass::Cube*);
		void Close(aetherClass::Cube*);

		
	public:
		RockUpdater();
		~RockUpdater() = default;

		void Update(aetherClass::Cube*model, bool buttonState);
		
	};
}