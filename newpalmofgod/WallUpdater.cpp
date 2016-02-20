#include "WallUpdater.h"
#include <iostream>
#include <Sphere.h>
using namespace n_Wall;
using namespace aetherClass;


WallUpdater::WallUpdater(){

}



//Update process
void WallUpdater::Update(ModelBase *Wall){

	if (!Wall){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}
	
}

void WallUpdater::First(ModelBase*Wall){

	std::cout << "First\n";

	Wall->GetTransform()._translation._y += speed;

	speed *= 1.12;

	std::cout << Wall->GetTransform()._translation._z << std::endl;

	if (Wall->GetTransform()._translation._y > 50.0f){

		Wall->GetTransform()._translation._y = 120.0f;

		Wall->GetTransform()._translation._x -= 0.5f;

		Wall->GetTransform()._rotation._x += 10.0f;

		Wall->GetTransform()._translation._z -= 15.0f;
	}

	
}
