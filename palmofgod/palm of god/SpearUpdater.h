#pragma once
#ifndef _SPEARUPDATER_H_
#define _SPEARUPDATER_H_

//#include"Spear.h"
#include <memory>
#include <ModelBase.h>
//#include<Cube.h>

namespace n_Spear{
	class SpearUpdater
	{
	private:
		//‘„‚Ì”ò‚Ño‚µ
		void ButtonOn(aetherClass::ModelBase*);
		//‘„‚Ìû”[
		void ButtonOff(aetherClass::ModelBase*);

		void operator =(const SpearUpdater &);

	public:
		SpearUpdater();
		~SpearUpdater();

		void Updating(aetherClass::ModelBase*, bool buttonState);


	};

}

#endif