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
	m_fallWall = std::make_shared<GameSound>();
	m_fallWall->Load("Sound/FallWall/door02.wav");
	m_fallWall->SetValume(-2000);
}

void FallingWallUpdater::Update(ModelBase* fallingWall)
{
	if (!fallingWall){ cout << "Not Found FallingWall" << endl; return; }
	if (m_eState == eState::eStop)return;

	float gravity = 9.8f;
	static float cnt = 1;
	static float interval = 120;
	static bool isFalled = false;


	if (fallingWall->property._transform._translation._y >= -30)
	{
		if (isFalled){ m_eState = eState::eMoveUp; }
		else m_eState = eState::eFalled;
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
			isFalled = false;
			break;
		case eState::eFalled:
			isFalled = true;
			m_fallWall->PlayToOneTime();
			break;
		case eState::eMoveUp:
			fallingWall->property._transform._translation._y -= 3;

			break;
		}
	}
	if (m_eEvent == eEvent::eThrow){
		gravity = 2.0f;
		switch (m_eState)
		{
		case eState::eInterval:
			interval--;
			break;
		case eState::eMoveDown:
			fallingWall->property._transform._translation._y += gravity * cnt;
			isFalled = false;
			break;
		case eState::eFalled:
			isFalled = true;
			m_fallWall->SetSpeed(eSoundSpeed::eSecondSpeed);
			m_fallWall->PlayToOneTime();
			break;
		case eState::eMoveUp:
			fallingWall->property._transform._translation._y -= 1.5;

			break;
		}
		m_countDown--;
	}
	if (m_countDown < 0){
		m_eEvent = eEvent::eNomal;
		m_countDown = 150;
		m_fallWall->Stop();
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