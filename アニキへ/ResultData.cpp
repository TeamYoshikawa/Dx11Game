#include "ResultData.h"
#include "PlayerManager.h"
#include "PlayerUpdater.h"
#include "Singleton.h"
using namespace aetherClass;
using namespace std;


ResultData::ResultData()
{
}


ResultData::~ResultData()
{
}


int ResultData::LifePointGet()
{
	return LifePointCounter;
}
void ResultData::LifePointSet(int Set )
{
	LifePointCounter = Set;
}

int ResultData::SoumatouCountGet()
{
	return SoumatouCounter;
}
void ResultData::SoumatouCountSet(int Set)
{
	   SoumatouCounter=Set;
}

void ResultData::Reset(){
	LifePointCounter = 3;
	SoumatouCounter = 0;
}
