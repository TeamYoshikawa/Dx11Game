#include "RockUpdater.h"
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
	
	Rock->GetTransform()._translation._y -= 0.0f;

}

void RockUpdater::Close(ModelBase*Rock){

	Rock->GetTransform()._translation._y -= 0.3f;
	
	if (Rock->GetTransform()._translation._y<2.5f){

		Rock->GetTransform()._rotation._x += 25.0f;
		Rock->GetTransform()._translation._y += 2.0f;
		Rock->GetTransform()._translation._z -= 8.0f;
	}
}

