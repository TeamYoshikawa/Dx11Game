#pragma once
#include"Rock.h"

namespace n_Rock{
	class RockUpdater
	{
	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void Open(DxModel::Cube*);
		void Close(DxModel::Cube*);

		
	public:
		RockUpdater();
		~RockUpdater() = default;

		void Update(DxModel::Cube*model, bool buttonState);
		
	};
}