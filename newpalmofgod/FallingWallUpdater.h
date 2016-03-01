#pragma once
#include <ModelBase.h>
#include <Physics.h>

#include <iostream>

class FallingWallUpdater
{
private:
	enum class eState
	{
		eMoveDown,
		eMoveUp,
		eInterval,
		eStop,
	};

	eState m_eState;
private:
	FallingWallUpdater(const FallingWallUpdater&) = default;
	void operator = (const FallingWallUpdater &);

public:
	FallingWallUpdater();
	~FallingWallUpdater() = default;

	void Update(aetherClass::ModelBase* model);
	bool HittingProcessor(const std::shared_ptr<aetherClass::ModelBase>& player, const std::shared_ptr<aetherClass::ModelBase>& other);

private:
	bool isFallflg;
};

