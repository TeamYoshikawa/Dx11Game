#include "FallingWallUpdater.h"

using namespace std;
using namespace aetherClass;

FallingWallUpdater::FallingWallUpdater()
{
	isFallflg = true;
	m_eState = eState::eInterval;
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

bool FallingWallUpdater::HittingProcessor(const shared_ptr<ModelBase>& player, const shared_ptr<ModelBase>& other)
{
	if (!aetherFunction::CollideBoxOBB(*player, *other))
	{
		return false;
	}

	return true;
}