#pragma once
#include"Rock.h"
#include"Sphere.h"

namespace n_Rock{
	class RockUpdater
	{
	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void Open(DxModel::ModelBase*);
		void Close(DxModel::ModelBase*);

		
	public:
		RockUpdater();
		~RockUpdater() = default;

		void Update(DxModel::ModelBase*model, bool buttonState);
		
	};
}