#include "FallingWallUpdater.h"

using namespace std;
using namespace aetherClass;

FallingWallUpdater::FallingWallUpdater()
{
	isFallflg = true;
}

void FallingWallUpdater::Update(ModelBase* fallingWall)
{
	if (!fallingWall){ cout << "Not Found FallingWall" << endl; return; }

	if (fallingWall->GetTransform()._translation._y >= -30)
	{
		isFallflg = false;
	}
	if (fallingWall->GetTransform()._translation._y <= -470)
	{
		isFallflg = true;
	}



	if (isFallflg)
	{
		cout << fallingWall->GetTransform()._translation._y << endl;
		cout << isFallflg << endl;
		fallingWall->GetTransform()._translation._y += 1;
	}
	else
	{
		fallingWall->GetTransform()._translation._y -= 1;
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