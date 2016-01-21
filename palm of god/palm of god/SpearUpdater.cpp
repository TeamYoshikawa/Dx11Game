#include "SpearUpdater.h"
#include<ModelBase.h>


SpearUpdater::SpearUpdater(){}

SpearUpdater::~SpearUpdater(){}

void SpearUpdater::Updating(DxModel::Cube* spear, bool buttonState = true)
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

void SpearUpdater::ButtonOn(DxModel::Cube* spear)
{
	spear->Translation()._y += 1.0f;

	if (spear->Translation()._y > 1.5f)spear->Translation()._y = 1.5f; 
		
		
}

void SpearUpdater::ButtonOff(DxModel::Cube* spear)
{
	spear->Translation()._y -= 1.0f;
	if (spear->Translation()._y < -1.5f)spear->Translation()._y = -1.5f;
	
}