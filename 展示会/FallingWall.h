#pragma once

#include <Cube.h>

class FallingWall :
	public aetherClass::Cube
{
public:
	FallingWall() = default;
	FallingWall(const FallingWall&) = default;
	~FallingWall() = default;
};