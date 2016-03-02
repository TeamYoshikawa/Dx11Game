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
	m_spearSound = std::make_shared<GameSound>();
	m_spearSound->Load("Sound/Spear/tobidasu.wav");
	m_spearSound->SetValume(-2000);
}

SpearUpdater::~SpearUpdater(){}

void SpearUpdater::Updating(std::shared_ptr<FbxModel>& spear)
{
	if (!spear){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}
	
	if (spear_flag == ON){
		if (m_event == eEvent::eNormal){
			SpearNormal(spear);
		}
		if (m_event == eEvent::eThrow){
			SpearThrow(spear);
			//m_countDown--;
		}
	}
	
	Soumatou();
	std::cout << m_countDown << std::endl;
	return;
}

void SpearUpdater::FlagOn()
{
	spear_flag = ON;
}

void SpearUpdater::Soumatou()
{
	if (GameController::GetKey().IsKeyDown(DIK_SPACE)){
		m_event = eEvent::eThrow;
		m_countDown--;
	}
	if (m_countDown < 0){
		m_event == eEvent::eNormal;
		m_countDown = 150;
	}
}

void SpearUpdater::SpearNormal(std::shared_ptr<FbxModel>& spear)
{
		std::cout << spear->property._transform._translation._y << std::endl;
		m_speed = 25.0f;
		if (flag == true){
			spear->property._transform._translation._y -= m_speed;
				if (spear->property._transform._translation._y < 300.0f){
					spear->property._transform._translation._y = 300.0f;
					flag = false;
					m_spearSound->PlayToOneTime();
				}
		}
		else if(flag==false){
				spear->property._transform._translation._y += 4.0f;
				if (spear->property._transform._translation._y > 640.0f){
					spear->property._transform._translation._y = 640.0f;
					flag = true;
					m_spearSound->PlayToOneTime();
					m_spearSound->SetSpeed(eSoundSpeed::eSecondSpeed);
				}
		}
}

void SpearUpdater::SpearThrow(std::shared_ptr<FbxModel>& spear)
{
	m_speed = 12.5f;
	if (flag == true){
		spear->property._transform._translation._y -= m_speed;
		if (spear->property._transform._translation._y < 300.0f){
			spear->property._transform._translation._y = 300.0f;
			flag = false;
			m_spearSound->Stop();
		}
	}
	else if (flag == false){
		spear->property._transform._translation._y += 2.0f;
		if (spear->property._transform._translation._y > 640.0f){
			spear->property._transform._translation._y = 640.0f;
			flag = true;
		}
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