#pragma once
#include "ModelBase.h"
#include <Physics.h>
#include "GameSound.h"



class NavigationUpdater
{
public:
	NavigationUpdater();
	~NavigationUpdater();
	void Update(aetherClass::ModelBase*model);

private:
	NavigationUpdater(const NavigationUpdater&) = default;
	void operator =(const NavigationUpdater &);

	
};

