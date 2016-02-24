#pragma once
#include <ModelBase.h>
#include <Physics.h>
//#include"Sphere.h"

#define OFF 0
#define ON  1
#define SET 2

static int rock_flag = OFF;

namespace n_Rock{
	class RockUpdater
	{

		enum eEvent{
			eNormal,
			eThrow
		};

	private:
		RockUpdater(const RockUpdater&) = default;
		void operator =(const RockUpdater &);

		void First(aetherClass::ModelBase*);
		void Second(aetherClass::ModelBase*);

		float speed= 1.0f;

		eEvent m_event;
		int m_countDown;
		
	public:
		RockUpdater();
		~RockUpdater() = default;

		bool HittingProcessor(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);
		
		void FlagON();
		void FlagOFF();
		int FlagGet();


		void Update(aetherClass::ModelBase*model);
		
	};
}