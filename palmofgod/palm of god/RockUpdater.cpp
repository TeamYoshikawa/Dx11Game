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
	else {
		Close(Rock);
	}


}

void RockUpdater::Open(ModelBase*Rock){

		//std::cout << "‚¨‚³‚ê‚½\n";

		Rock->GetTransform()._translation._y += speed;

		speed *= 1.12;

		if (Rock->GetTransform()._translation._y > 120.0f){

			Rock->GetTransform()._translation._y = 120.0f;

			Rock->GetTransform()._translation._x -= 0.5f;
			Rock->GetTransform()._rotation._x += 10.0f;
			//Rock->GetTransform()._translation._y += 2.0f;
			Rock->GetTransform()._translation._z -= 5.0f;
		}

		if (Rock->GetTransform()._translation._z < 200){
			r_flag = ON;
			/*std::cout << r_flag << "\n";*/
		}
	}

	

void RockUpdater::Close(ModelBase*Rock){

		//std::cout << "‚¨‚³‚ê‚Ä‚È‚¢\n";

		Rock->GetTransform()._translation._y += speed;

		speed *= 1.12;

		//std::cout << Rock->GetTransform()._translation._z << "\n";

		if (Rock->GetTransform()._translation._y > 120.0f){

			Rock->GetTransform()._translation._y = 120.0f;

			Rock->GetTransform()._translation._x -= 0.5f;
			Rock->GetTransform()._rotation._x += 10.0f;
			Rock->GetTransform()._translation._z -= 5.0f;
		}
	}

