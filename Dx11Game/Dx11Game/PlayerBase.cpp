#include "PlayerBase.h"

PlayerBase::Status PlayerBase::m_status;

PlayerBase::PlayerBase()
{
}


PlayerBase::~PlayerBase()
{
}

PlayerBase::Status& PlayerBase::GetStatus(){
	return m_status;
}

void PlayerBase::Process(){
	this->Run();
}