#include "RockUpdater.h"

using namespace n_Rock;
using namespace DxModel;

RockUpdater::RockUpdater(){

}

//Update process
void RockUpdater::Update(Sphere *Rock, bool buttonState = false){
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

void RockUpdater::Open(Sphere*Rock){
	
	Rock->Translation()._y -= 0.0f;

}

void RockUpdater::Close(Sphere*Rock){

	Rock->Translation()._y -= 0.3f;
	
	if (Rock->Translation()._y<2.5f){

		Rock->Rotation()._x += 25.0f;
		Rock->Translation()._y += 2.0f;
		Rock->Translation()._z -= 8.0f;
	}
}

