#include "RockUpdater.h"
#include <iostream>
#include <Sphere.h>
#include<GameController.h>


using namespace n_Rock;
using namespace aetherClass;


RockUpdater::RockUpdater(){
	m_event = eEvent::eNormal;
	m_countDown = 150;
	m_rockSound = std::make_shared<GameSound>();
	bool hoge = m_rockSound->Load("Sound/Rock/Iwa_korogaru.wav");
	if (!hoge){
		assert(!"エラー＆死にました");
	}
	m_rockSound->SetValume(+2000);
}


//Update process
void RockUpdater::Update(ModelBase *Rock){

	if (!Rock){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}

	if (rock_flag == ON){
		First(Rock);
	}

}

void RockUpdater::FlagON(){
	rock_flag = ON;
}

void RockUpdater::FlagOFF(){
	rock_flag = OFF;
}

int RockUpdater::FlagGet(){
	return rock_flag;
}

void RockUpdater::First(ModelBase*Rock){

	std::cout << "First\n";

	Rock->property._transform._translation._y += speed;

	speed *= 1.12;

	//std::cout << Rock->property._transform._translation._x << std::endl;
	if (GameController::GetKey().IsKeyDown(DIK_SPACE))m_event = eEvent::eThrow;
	if (Rock->property._transform._translation._y > 120.0f){

		if (m_event == eEvent::eNormal){

			Rock->property._transform._translation._y = 120.0f;

			Rock->property._transform._translation._x -= 0.5f;

			Rock->property._transform._rotation._z += 10.0f;

			Rock->property._transform._translation._x += 13.0f;
			m_rockSound->SetSpeed(eSoundSpeed::eHighSpeed);
			m_rockSound->PlayToOneTime();
		}
		else if (m_event == eEvent::eThrow){
			Rock->property._transform._translation._y = 120.0f;

			Rock->property._transform._translation._x -= 0.5f;

			Rock->property._transform._rotation._z += 3.0f;

			Rock->property._transform._translation._x += 5.0f;
			m_rockSound->SetSpeed(eSoundSpeed::eSecondSpeed);
			m_rockSound->PlayToOneTime();
			m_countDown--;

		}

		if (m_countDown <= 0){
			m_event = eEvent::eNormal;
			m_countDown = 150;
		}
		if (Rock->property._transform._translation._x > 6200){
			rock_flag = SET;
			Rock->property._transform._translation._x -= 0.5f;
			m_rockSound->Stop();
		}
	}
}

bool RockUpdater::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){

	// TODO: 当たったかを調べる条件式を記載
	if (!aetherFunction::CollideBoxOBB(*player, *other)){
		return false;
	}
	return true;

}