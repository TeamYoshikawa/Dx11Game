#include "SpearUpdaterScond.h"
#include<Physics.h>
#include<ModelBase.h>
#include<GameController.h>
#include<iostream>

using namespace aetherClass;
using namespace n_Spear;
SpearUpdaterScond::SpearUpdaterScond()
{
	m_event = eEvent::eNormal;
	m_countDown = 300;
	spear_flag2 = OFF;
	m_tobidasuSound = std::make_shared<GameSound>();
	m_tobidasuSound->Load("Sound/Spear/tobidasu.wav");
	m_tobidasuSound->SetValume(-2000);

	m_hikkomuSound = std::make_shared<GameSound>();
	m_hikkomuSound->Load("Sound/Spear/hikkomu.wav");
	m_hikkomuSound->SetValume(-2000);
}

SpearUpdaterScond::~SpearUpdaterScond(){}

void SpearUpdaterScond::Updating(std::shared_ptr<FbxModel>& spear)
{
	if (!spear){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}
	if (GameController::GetKey().IsKeyDown(DIK_SPACE)){
		m_event = eEvent::eThrow;

	}
	if (spear_flag2 == ON){
		if (m_event == eEvent::eNormal){
			SpearNormal(spear);
		}
		if (m_event == eEvent::eThrow){
			SpearThrow(spear);
			m_countDown--;
		}

	}
	if (m_countDown < 0){
		m_event == eEvent::eNormal;
		m_countDown = 150;
		m_tobidasuSound->Stop();
		m_hikkomuSound->Stop();
	}
	//std::cout << m_countDown << std::endl;
	return;
}

void SpearUpdaterScond::FlagOn()
{
	spear_flag2 = ON;
}

void SpearUpdaterScond::SpearNormal(std::shared_ptr<FbxModel>& spear)
{
	//std::cout << spear->property._transform._translation._y << std::endl;
	m_speed = 70.0f;
	if (flag2 == true){
		spear->property._transform._translation._z -= m_speed;
		if (spear->property._transform._translation._z < 620.0f){
			spear->property._transform._translation._z = 620.0f;
			m_tobidasuSound->PlayToOneTime();
			flag2 = false;
		}
	}
	else if (flag2 == false){
		spear->property._transform._translation._z += 4.0f;
		if (spear->property._transform._translation._z > 1500.0f){
			spear->property._transform._translation._z = 1500.0f;
			m_hikkomuSound->PlayToOneTime();
			flag2 = true;
		}
	}
}

void SpearUpdaterScond::SpearThrow(std::shared_ptr<FbxModel>& spear)
{
	m_speed = 12.5f;
	if (flag2 == true){
		spear->property._transform._translation._z -= m_speed;
		if (spear->property._transform._translation._z < 620.0f){
			spear->property._transform._translation._z = 620.0f;
			flag2 = false;
			m_tobidasuSound->SetSpeed(eSoundSpeed::eSecondSpeed);
			m_tobidasuSound->PlayToOneTime();
		}
	}
	else if (flag2 == false){
		spear->property._transform._translation._z += 2.0f;
		if (spear->property._transform._translation._z > 1500.0f){
			spear->property._transform._translation._z = 1500.0f;
			flag2 = true;
			m_hikkomuSound->SetSpeed(eSoundSpeed::eSecondSpeed);
			m_hikkomuSound->PlayToOneTime();
		}
	}
}

bool SpearUpdaterScond::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){

	// TODO: “–‚½‚Á‚½‚©‚ğ’²‚×‚éğŒ®‚ğ‹LÚ
	if (!aetherFunction::CollideBoxOBB(*player, *other)){
		return false;
	}
	return true;

}

int SpearUpdaterScond::FlagGet()
{
	return spear_flag2;
}