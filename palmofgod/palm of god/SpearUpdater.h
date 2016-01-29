#pragma once
#ifndef _SPEARUPDATER_H_
#define _SPEARUPDATER_H_

//#include"Spear.h"
#include <memory>
#include <ModelBase.h>
//#include<Cube.h>

#define ON 1
#define OFF 0

namespace n_Spear{
	class SpearUpdater
	{
	private:
		//���̔�яo��
		void ButtonOn(aetherClass::ModelBase*);
		//���̎��[
		void ButtonOff(aetherClass::ModelBase*);

		void operator =(const SpearUpdater &);

	public:
		SpearUpdater();
		~SpearUpdater();

		void Updating(aetherClass::ModelBase*, bool buttonState);
		int FlagGet();

		int s_flag = OFF;

	};

}

#endif