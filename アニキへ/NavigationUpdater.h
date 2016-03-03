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

	

	bool HittingProcessor(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);

private:
	NavigationUpdater(const NavigationUpdater&) = default;
	void operator =(const NavigationUpdater &);

	
};

