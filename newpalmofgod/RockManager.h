#pragma once

#include"RockUpdater.h"
#include"RockRender.h"
#include "PlayerManager.h"
#include <Physics.h>
#include <GameController.h>
#include <Sphere.h>
#include <Cube.h>
#include <memory>
#include <Texture.h>
#include <ViewCamera.h>
#include <stdio.h>

#define r_max 2

class RockManager
{
private:
	enum class eEvent{
		eChecking,
		eStart,
		eNull
	};
private:
	std::shared_ptr<aetherClass::ModelBase>m_Rock[2];
	std::shared_ptr<aetherClass::ModelBase>m_switch;
	std::shared_ptr<aetherClass::ModelBase>m_hplayer;

	std::shared_ptr<aetherClass::Texture> m_rockTexture;
	std::shared_ptr<aetherClass::Texture> m_switchTexture;
	std::shared_ptr<aetherClass::Texture> m_hplayerTexture;

	std::shared_ptr<n_Rock::RockUpdater>m_updater;
	std::shared_ptr<n_Rock::RockRender>m_render;

	std::shared_ptr<n_Rock::RockUpdater> m_player;
	
	int i;

	eEvent m_rockEvent;
	
	
public:
	RockManager() = default;
	~RockManager() = default;

	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();

	std::shared_ptr<aetherClass::ModelBase> Get();
};
