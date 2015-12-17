#pragma once
#include"Rock.h"
#include"Sphere.h"

namespace n_Rock{
	class RockUpdater
	{
	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void Open(DxModel::Sphere*);
		void Close(DxModel::Sphere*);

		
	public:
		RockUpdater();
		~RockUpdater() = default;

		void Update(DxModel::Sphere*model, bool buttonState);
		
	};
}