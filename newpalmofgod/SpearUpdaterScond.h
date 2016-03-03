#pragma once
#ifndef _SPEARUPDATERSCOND_H_
#define _SPEARUPDATERSCOND_H_

//#include"Spear.h"
#include <memory>
#include <ModelBase.h>
#include <FbxModel.h>
#include <GameSound.h>
//#include<Cube.h>

#define OFF 0
#define ON 1
#define SET 2

static bool flag2 = true;
static int spear_flag2;


namespace n_Spear{
	class SpearUpdaterScond
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

		void operator =(const SpearUpdaterScond &);

		eEvent m_event;

		float m_speed;

		int m_countDown;

		std::shared_ptr<aetherClass::GameSound> m_tobidasuSound;
		std::shared_ptr<aetherClass::GameSound> m_hikkomuSound;
	public:
		SpearUpdaterScond();
		~SpearUpdaterScond();

		void Updating(std::shared_ptr<aetherClass::FbxModel>&);
		bool HittingProcessor(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);

		void FlagOn();
		int FlagGet();
	};

}

#endif