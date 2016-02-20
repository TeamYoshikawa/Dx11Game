#pragma once

#include"WallUpdater.h"
#include"WallRender.h"
#include "PlayerManager.h"
//#include "TrapNavigation.h"
#include <GameController.h>
#include <Sphere.h>
#include <Cube.h>
#include <memory>
#include <Texture.h>
#include <ViewCamera.h>
#include <stdio.h>

#define r_max 13

class WallManager

{
private:
	enum class eEvent{
		eChecking,
		eStart,
		eNull
	};
private:
	std::shared_ptr<aetherClass::ModelBase>m_Wall[2];
	
	std::shared_ptr<aetherClass::ModelBase>m_HitWall[13];
	

	std::shared_ptr<aetherClass::ModelBase>m_hplayer;

	std::shared_ptr<aetherClass::Texture> m_WallTexture;
	std::shared_ptr<aetherClass::Texture> m_HitWallTexture;
	std::shared_ptr<aetherClass::Texture> m_hplayerTexture;

	std::shared_ptr<n_Wall::WallUpdater>m_updater;
	std::shared_ptr<n_Wall::WallRender>m_render;

	std::shared_ptr<n_Wall::WallUpdater> m_player;

	//std::shared_ptr<TrapNavigation> m_navigation;

	int i;

	eEvent m_WallEvent;


public:
	WallManager() = default;
	~WallManager() = default;

	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();

	std::shared_ptr<aetherClass::ModelBase> Get();
};

