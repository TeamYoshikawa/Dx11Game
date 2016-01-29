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
		ButtonOn(spear);
		s_flag = ON;
	}
	else{
		ButtonOff(spear);
	}
	

	return;
}

void SpearUpdater::ButtonOn(ModelBase* spear)
{
	spear->GetTransform()._translation._y -= 10.0f;

	if (spear->GetTransform()._translation._y > -200.5f)spear->GetTransform()._translation._y = -200.5f;
		
	s_flag = OFF;
}

void SpearUpdater::ButtonOff(ModelBase* spear)
{
	spear->GetTransform()._translation._y += 10.0f;
	if (spear->GetTransform()._translation._y > 350.5f)spear->GetTransform()._translation._y = 350.5f;
	
}

int SpearUpdater::FlagGet()
{
	return s_flag;
}