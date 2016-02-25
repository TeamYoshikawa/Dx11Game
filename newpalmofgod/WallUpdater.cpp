#include "WallUpdater.h"
#include <iostream>
#include <Sphere.h>
#include <Physics.h>
using namespace n_Wall;
using namespace aetherFunction;
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

bool WallUpdater::HitProcessor(const std::shared_ptr<aetherClass::ModelBase>&wall, const std::shared_ptr<aetherClass::ModelBase>&player)
{
	if (!CollideBoxOBB(*wall, *player)){
		return false;
	}
	return true;
}