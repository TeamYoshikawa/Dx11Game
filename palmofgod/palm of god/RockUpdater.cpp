#include "RockUpdater.h"
#include <iostream>
#include <Sphere.h>
using namespace n_Rock;
using namespace aetherClass;


RockUpdater::RockUpdater(){

}

//Update process
void RockUpdater::Update(ModelBase *Rock, bool buttonState = false){


	if (!Rock){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}

	if (buttonState){
		Open(Rock);
	}
	else
		Close(Rock);
	
}

void RockUpdater::Open(ModelBase*Rock){

	std::cout << "HIROKI‚ªŒÄ‚Î‚ê‚½\n";
	std::cout << Rock->GetTransform()._translation._x << "\n";
	std::cout << Rock->GetTransform()._translation._y << "\n";
	std::cout << Rock->GetTransform()._translation._z << "\n";
	
	Rock->GetTransform()._translation._y -= 0.0f;

}

void RockUpdater::Close(ModelBase*Rock){


	//m_Rock->GetTransform()._translation = Vector3(2900.0f, -300.0f, 2100.0f);

	Rock->GetTransform()._translation._y += speed;

	
	
	speed *= 1.12;

	std::cout << Rock->GetTransform()._translation._x << "\n";
	std::cout << Rock->GetTransform()._translation._y << "\n";

	if (Rock->GetTransform()._translation._y > 120.0f){
		
		Rock->GetTransform()._translation._y = 120.0f;

		Rock->GetTransform()._translation._x -= 0.5f;
		Rock->GetTransform()._rotation._x += 10.0f;
		//Rock->GetTransform()._translation._y += 2.0f;
		Rock->GetTransform()._translation._z -= 5.0f;
	}
	
}

