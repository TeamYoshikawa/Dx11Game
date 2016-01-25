#include "SpearUpdater.h"
#include<ModelBase.h>

using namespace aetherClass;
using namespace n_Spear;
SpearUpdater::SpearUpdater(){}

SpearUpdater::~SpearUpdater(){}

void SpearUpdater::Updating(ModelBase* spear, bool buttonState = true)
{
	if (!spear){
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return;
	}
	if (buttonState){
		//MessageBox(NULL, L"ON", ERROR, MB_OK);
		ButtonOn(spear);
	}
	else{
		ButtonOff(spear);
	}
	

	return;
}

void SpearUpdater::ButtonOn(ModelBase* spear)
{
	spear->GetTransform()._translation._y += 1.0f;

	if (spear->GetTransform()._translation._y > 1.5f)spear->GetTransform()._translation._y = 1.5f;
		
		
}

void SpearUpdater::ButtonOff(ModelBase* spear)
{
	spear->GetTransform()._translation._y -= 1.0f;
	if (spear->GetTransform()._translation._y < -1.5f)spear->GetTransform()._translation._y = -1.5f;
	
}