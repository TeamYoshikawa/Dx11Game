#include "PlayerBase.h"

PlayerBase::PlayerStatus PlayerBase::m_status;

PlayerBase::PlayerBase()
{
}


PlayerBase::~PlayerBase()
{
}

PlayerBase::PlayerStatus& PlayerBase::GetStatus(){
	return m_status;
}

void PlayerBase::SetState(ePlayerState state){
	m_state = state;
}