#include "PlayerBase.h"

PlayerBase::PlayerStatus PlayerBase::m_status;

PlayerBase::PlayerBase()
{
}


PlayerBase::~PlayerBase()
{
}

PlayerBase::PlayerStatus& PlayerBase::SendShareStatus(){
	return m_status;
}

PlayerBase::PlayerStatus& PlayerBase::SendStatus(){
	return SendShareStatus();
}

void PlayerBase::SendStatus(PlayerBase::PlayerStatus& status){


	return;
}