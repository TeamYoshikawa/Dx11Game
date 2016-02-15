#pragma once
#include <ModelBase.h>
//#include"Sphere.h"

#define ON 1
#define OFF 0
#define SAVE 2
namespace n_Rock{
	class RockUpdater
	{
	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void First(aetherClass::ModelBase*);
		void Second(aetherClass::ModelBase*);

		float speed= 1.0f;
		
	public:
		RockUpdater();
		~RockUpdater() = default;

		void Update(aetherClass::ModelBase*model);
		
	};
}