#include "SpearUpdater.h"
#include<ModelBase.h>
#include<GameController.h>
#include<iostream>

using namespace aetherClass;
using namespace n_Spear;
SpearUpdater::SpearUpdater()
{
	m_event = eEvent::eNormal;
	m_countDown = 150;
	s_flag = OFF;
}

SpearUpdater::~SpearUpdater(){}

void SpearUpdater::Updating(ModelBase* spear)
{
	if (!spear){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}
	if (s_flag == ON){
		ButtonOn(spear);
	}
	std::cout << s_flag << std::endl;
	return;
}

void SpearUpdater::FlagOn()
{
	s_flag = ON;
}

void SpearUpdater::FlagOff()
{
	s_flag = OFF;
}

void SpearUpdater::ButtonOn(ModelBase* spear)
{
	if (GameController::GetKey().IsKeyDown(DIK_SPACE))m_event = eEvent::eThrow;
	if (m_event == eEvent::eNormal){
		std::cout << spear->GetTransform()._translation._z << std::endl;
		spear->GetTransform()._translation._z -= 30.0f;
	}
	else if(m_event==eEvent::eThrow){
		spear->GetTransform()._translation._z -= 5.0f;
		m_countDown--;
	}
	if (m_countDown <= 0)m_event = eEvent::eNormal;
	if (spear->GetTransform()._translation._z < -3000){
		s_flag = SET;
	}
	
}

int SpearUpdater::FlagGet()
{
	return s_flag;
}