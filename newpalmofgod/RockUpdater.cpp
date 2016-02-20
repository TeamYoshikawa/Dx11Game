#include "RockUpdater.h"
#include <iostream>
#include <Sphere.h>
using namespace n_Rock;
using namespace aetherClass;


RockUpdater::RockUpdater(){
	m_event = eEvent::eNormal;
	m_countDown = 150;
}



//Update process
void RockUpdater::Update(ModelBase *Rock){
	
	if (!Rock){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}

	if (flag == OFF){
		First(Rock);
	}

}

void RockUpdater::First(ModelBase*Rock){

		std::cout << "First\n";

		Rock->GetTransform()._translation._y += speed;

		speed *= 1.12;
		
		std::cout << Rock->GetTransform()._translation._z << std::endl;
	
		
		if (GameController::GetKey().IsKeyDown(DIK_SPACE))m_event = eEvent::eThrow;
		if (Rock->GetTransform()._translation._y > 120.0f){
			
			if (m_event == eEvent::eNormal){
				Rock->GetTransform()._translation._y = 120.0f;

				Rock->GetTransform()._translation._x -= 0.5f;

				Rock->GetTransform()._rotation._x += 10.0f;

				Rock->GetTransform()._translation._z -= 15.0f;
			}
			else if (m_event == eEvent::eThrow){
				Rock->GetTransform()._translation._y = 120.0f;
				
				Rock->GetTransform()._translation._x -= 0.5f;

				Rock->GetTransform()._rotation._x += 3.0f;

				Rock->GetTransform()._translation._z -= 5.0f;
				m_countDown--;
			}
		}
		if (m_countDown <= 0)m_event = eEvent::eNormal;
		if (Rock->GetTransform()._translation._z < 200){
			flag = ON;
		}
	}

