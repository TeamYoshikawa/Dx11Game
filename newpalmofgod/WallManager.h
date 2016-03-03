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

#define r_max 22

class WallManager

{
private:
	enum class eEvent{
		eChecking,
		eStart,
		eNull
	};
private:
	std::shared_ptr<aetherClass::ModelBase>m_HitWall[21];
	std::shared_ptr<aetherClass::ModelBase>m_NoHitWall;

	std::shared_ptr<aetherClass::Texture> m_WallTexture;
	std::shared_ptr<aetherClass::Texture> m_HitWallTexture;
	std::shared_ptr<aetherClass::Texture> m_NoHitWallTexture;
	std::shared_ptr<aetherClass::Texture> m_hplayerTexture;

	std::shared_ptr<n_Wall::WallUpdater>m_updater;
	std::shared_ptr<n_Wall::WallRender>m_render;

	std::shared_ptr<aetherClass::ModelBase>m_descWall01;
	std::shared_ptr<aetherClass::ModelBase>m_descWall02;
	std::shared_ptr<aetherClass::ModelBase>m_descWall03;
	std::shared_ptr<aetherClass::Texture>m_descriptionWalltexture01;
	std::shared_ptr<aetherClass::Texture>m_descriptionWalltexture02;
	std::shared_ptr<aetherClass::Texture>m_descriptionWalltexture03;

	int i;

	eEvent m_WallEvent;

public:
	WallManager() = default;
	~WallManager() = default;

	bool Initialize(aetherClass::ViewCamera* camera);
	bool HitMesh(std::shared_ptr<aetherClass::ModelBase>&,std::shared_ptr<aetherClass::ViewCamera>);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();

	std::shared_ptr<aetherClass::ModelBase> Get(int);

	int WallCnt();

};

