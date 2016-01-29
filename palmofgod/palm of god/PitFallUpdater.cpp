#include "PitFallUpdater.h"

using namespace Pitfall;
using namespace aetherClass;

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
		s_flag = ON;
	}
	else
		Close(pitfall);

}

void PitFallUpdater::Open(ModelBase*pitfall){
	m_speed *= 0.97;
	if (m_speed < 0.1){
		pitfall->GetTransform()._rotation._z = 90;
	}
	if (pitfall->GetTransform()._rotation._z > 90){
		pitfall->GetTransform()._rotation._z -= m_speed;
	}
	else{
		pitfall->GetTransform()._rotation._z += m_speed;
	}

	//

}

void PitFallUpdater::Close(ModelBase*pitfall){
	m_speed = 10;
	pitfall->GetTransform()._rotation._z -= m_speed;
	if (pitfall->GetTransform()._rotation._z < 0){
		pitfall->GetTransform()._rotation._z = 0;
		m_speed = 20;
	}
	s_flag = OFF;

}

int PitFallUpdater::FlagGet()
{
	return s_flag;
}