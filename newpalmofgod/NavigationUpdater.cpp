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