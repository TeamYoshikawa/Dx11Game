#include "NavigationUpdater.h"
#include <Cube.h>
#include <iostream>

using namespace aetherClass;

void NavigationUpdater::Update(ModelBase *navigation){

	if (!navigation){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}

}

bool NavigationUpdater::HittingProcessor(const std::shared_ptr<ModelBase>& player, const std::shared_ptr<ModelBase>& other){

	// TODO: �����������𒲂ׂ���������L��
	if (!aetherFunction::CollideBoxOBB(*player, *other)){
		return false;
	}
	return true;

}
