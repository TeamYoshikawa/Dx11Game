#pragma once
#include"PitFall.h"

namespace Pitfall{
	class PitFallUpdater
	{
	private:
		PitFallUpdater(const PitFallUpdater&){};
		void operator =(const PitFallUpdater &){};

		void Open(DxModel::ModelBase*);
		void Close(DxModel::ModelBase*);
		
		float m_speed;
	public:
		PitFallUpdater();
		~PitFallUpdater() = default;

		void Update(DxModel::ModelBase*model,bool buttonState);

	};

}