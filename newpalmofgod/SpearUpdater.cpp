#include "SpearUpdater.h"
#include<Physics.h>
#include<ModelBase.h>
#include<GameController.h>
#include<iostream>

using namespace aetherClass;
using namespace n_Spear;
SpearUpdater::SpearUpdater()
{
	m_event = eEvent::eNormal;
	m_countDown = 150;
	spear_flag = OFF;
}

SpearUpdater::~SpearUpdater(){}

void SpearUpdater::Updating(ModelBase* spear)
{
	if (!spear){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}
	if (spear_flag == ON){
		ButtonOn(spear);
	}
	std::cout << spear_flag << std::endl;
	return;
}

void SpearUpdater::FlagOn()
{
	spear_flag = ON;
}

void SpearUpdater::FlagOff()
{
	spear_flag = OFF;
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
		spear_flag = SET;
	}
	
}

bool SpearUpdater::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){

	// TODO: “–‚½‚Á‚½‚©‚ğ’²‚×‚éğŒ®‚ğ‹LÚ
	if (!aetherFunction::CollideBoxOBB(*player, *other)){
		return false;
	}
	return true;

}

int SpearUpdater::FlagGet()
{
	return spear_flag;
}