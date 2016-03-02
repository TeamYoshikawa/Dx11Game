#pragma once
#ifndef _SPEARUPDATER_H_
#define _SPEARUPDATER_H_

//#include"Spear.h"
#include <memory>
#include <ModelBase.h>
#include <FbxModel.h>
#include <GameSound.h>
//#include<Cube.h>

#define OFF 0
#define ON 1
#define SET 2

static bool flag = true;
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
		void SpearNormal(std::shared_ptr<aetherClass::FbxModel>&);
		void SpearThrow(std::shared_ptr<aetherClass::FbxModel>&);

		void Soumatou();

		void operator =(const SpearUpdater &);

		eEvent m_event;

		float m_speed;

		int m_countDown;

		std::shared_ptr<aetherClass::GameSound> m_spearSound;
	public:
		SpearUpdater();
		~SpearUpdater();

		void Updating(std::shared_ptr<aetherClass::FbxModel>&);
		bool HittingProcessor(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);

		void FlagOn();
		int FlagGet();
	
		

	};

}

#endif