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

	r_flag = ON;
	Open(Rock);
}

void RockUpdater::Open(ModelBase*Rock){

		FlagGet();
		static int counter = 0;
		counter += 1;
		const int waitTime = 15;
		//std::cout << "‚¨‚³‚ê‚½\n";

		if (counter > waitTime)
		{
			Rock->GetTransform()._translation._y += speed;

			speed *= 1.12;
		}
	
		if (Rock->GetTransform()._translation._y > 120.0f){

			Rock->GetTransform()._translation._y = 120.0f;

			Rock->GetTransform()._translation._x -= 0.5f;
			Rock->GetTransform()._rotation._x += 10.0f;
			//Rock->GetTransform()._translation._y += 2.0f;
			Rock->GetTransform()._translation._z -= 15.0f;
		}

		if (Rock->GetTransform()._translation._z < 200){
			r_flag = OFF;
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


int RockUpdater::FlagGet(){
	//std::cout << "ŒÄ‚Î‚ê‚½";
	return r_flag;
}