#pragma once
#include <ModelBase.h>

namespace n_Wall{
	class WallUpdater
	{
	private:
		WallUpdater(const WallUpdater&) = default;
		void operator =(const WallUpdater &);

		void First(aetherClass::ModelBase*);
		void Second(aetherClass::ModelBase*);

		float speed = 1.0f;

	public:
		WallUpdater();
		~WallUpdater() = default;
		bool HitProcessor(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);
		void Update(aetherClass::ModelBase*model);

	};
}