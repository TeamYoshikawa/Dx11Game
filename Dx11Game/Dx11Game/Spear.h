#pragma once

#include "Cube.h"
#include"Direct3DManager.h"

class Spear :
	public DxModel::Cube
{
public:
	Spear() = default;
	~Spear() = default;

	/*bool InitializeBuffers()override;
	void ShutdownBuffers()override;
	void RenderBuffers()override;*/
};

