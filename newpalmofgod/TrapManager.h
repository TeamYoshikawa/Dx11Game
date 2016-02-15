#pragma once

#include "RockManager.h"

#include <Physics.h>
#include <GameController.h>
#include <Sphere.h>
#include <Cube.h>
#include <memory>
#include <Texture.h>
#include <ViewCamera.h>
#include <stdio.h>


class TrapManager
{

private:
	std::shared_ptr<aetherClass::ModelBase>m_switch;

	std::shared_ptr<aetherClass::ModelBase>m_player;
	
	std::shared_ptr<aetherClass::Texture> m_switchTexture;

	std::shared_ptr<aetherClass::Texture> m_playerTexture;


	std::shared_ptr<RockManager>m_rock;

	

public:
	TrapManager() = default;
	~TrapManager() = default;


	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();

};

