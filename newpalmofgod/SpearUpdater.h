#pragma once
#ifndef _SPEARUPDATER_H_
#define _SPEARUPDATER_H_

//#include"Spear.h"
#include <memory>
#include <ModelBase.h>
//#include<Cube.h>

#define OFF 0
#define ON 1
#define SET 2

static int spear_flag;

namespace n_Spear{
	class SpearUpdater
	{
	private:
		enum eEvent{
			eNormal,
			eThrow
		};
	private:
		//ëÑÇÃîÚÇ—èoÇµ
		void ButtonOn(aetherClass::ModelBase*);

		void operator =(const SpearUpdater &);

		eEvent m_event;

		int m_countDown;
	public:
		SpearUpdater();
		~SpearUpdater();

		void Updating(aetherClass::ModelBase*);
		bool HittingProcessor(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);

		void FlagOn();
		void FlagOff();
		int FlagGet();

		

	};

}

#endif