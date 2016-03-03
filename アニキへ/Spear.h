#pragma once

#include "Cube.h"
#include"Direct3DManager.h"

class Spear:
	public aetherClass::Cube
{
public:
	Spear(){};
	virtual ~Spear() = default;

	/*bool InitializeBuffers()override;
	void ShutdownBuffers()override;
	void RenderBuffers()override;*/
};

