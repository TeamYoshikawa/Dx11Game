#pragma once
#include <ShaderBase.h>
#include <memory>
#include "FallingWall.h"

class FallingWallRender
{
private:
	FallingWallRender(const FallingWallRender&) = default;
	void operator = (const FallingWallRender&){};

public:
	FallingWallRender() = default;
	~FallingWallRender() = default;

	void Render(aetherClass::ModelBase* model, std::shared_ptr<aetherClass::ShaderBase> shader);

};

