#include "PitFallUpdater.h"

using namespace Pitfall;
using namespace DxModel;

PitFallUpdater::PitFallUpdater() : m_speed(20){
}

//Update process
void PitFallUpdater::Update(ModelBase *pitfall , bool buttonState = false){
	if (!pitfall){ 
		MessageBox(NULL, L"missing Object", ERROR, MB_OK);
		return; 
	}

	if (buttonState){
		Open(pitfall);
	}
	else
		Close(pitfall);

}

void PitFallUpdater::Open(ModelBase*pitfall){
	m_speed *= 0.97;
	if (m_speed < 0.1){
		pitfall->Rotation()._z = 90;
	}
	if (pitfall->Rotation()._z > 90){
		pitfall->Rotation()._z -= m_speed;
	}
	else{
		pitfall->Rotation()._z += m_speed;
	}
}

void PitFallUpdater::Close(ModelBase*pitfall){
	m_speed = 10;
	pitfall->Rotation()._z -= m_speed;
	if (pitfall->Rotation()._z < 0){
		pitfall->Rotation()._z = 0; 
		m_speed = 20;
	}

}

