#include "FallingWallUpdater.h"
#include <GameController.h>

using namespace std;
using namespace aetherClass;

FallingWallUpdater::FallingWallUpdater()
{
	isFallflg = true;
	m_eState = eState::eInterval;
	m_eEvent = eEvent::eNomal;
	m_countDown = 150;
}

void FallingWallUpdater::Update(ModelBase* fallingWall)
{
	if (!fallingWall){ cout << "Not Found FallingWall" << endl; return; }
	if (m_eState == eState::eStop)return;

	float gravity = 9.8f;
	static float cnt = 1;
	static float interval = 120;

	if (fallingWall->property._transform._translation._y >= -30)
	{
		m_eState = eState::eMoveUp;
	}
	if (fallingWall->property._transform._translation._y <= -470)
	{
		m_eState = eState::eInterval;
	}
	if (interval <= 0)
	{
		interval = 120;
		m_eState = eState::eMoveDown;
	}

	if (GameController::GetKey().IsKeyDown(DIK_SPACE)){
		m_eEvent = eEvent::eThrow;
	}

	if (m_eEvent == eEvent::eNomal){
		switch (m_eState)
		{
		case eState::eInterval:
			interval--;
			break;
		case eState::eMoveDown:
			fallingWall->property._transform._translation._y += gravity * cnt;
			break;
		case eState::eMoveUp:
			fallingWall->property._transform._translation._y -= 3;
			break;
		}
	}
	if (m_eEvent == eEvent::eThrow){
		gravity = 19.6f;
		switch (m_eState)
		{
		case eState::eInterval:
			interval--;
			break;
		case eState::eMoveDown:
			fallingWall->property._transform._translation._y += gravity * cnt;
			break;
		case eState::eMoveUp:
			fallingWall->property._transform._translation._y -= 1.5f;
			break;
		}
		m_countDown--;
	}
	if (m_countDown < 0){
		m_eEvent = eEvent::eNomal;
		m_countDown = 150;
	}
}

bool FallingWallUpdater::HittingProcessor(const shared_ptr<ModelBase>& player, const shared_ptr<ModelBase>& other)
{
	if (!aetherFunction::CollideBoxOBB(*player, *other))
	{
		return false;
	}

	return true;
}