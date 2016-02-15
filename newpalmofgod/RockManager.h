#pragma once

#include"RockUpdater.h"
#include"RockRender.h"
#include "PlayerManager.h"

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
		eCheckingInput,
		eStart,
		eNull
	};
private:
	std::shared_ptr<aetherClass::ModelBase>m_Rock[2];

	std::shared_ptr<aetherClass::ModelBase>m_switch;

	std::shared_ptr<aetherClass::Texture> m_rockTexture;
	std::shared_ptr<aetherClass::Texture> m_switchTexture;

	std::shared_ptr<n_Rock::RockUpdater>m_updater;
	std::shared_ptr<n_Rock::RockRender>m_render;

	std::shared_ptr<n_Rock::RockUpdater> m_player;
	
	int i;

	bool m_isButton;
	
	int m_cnt;

	eEvent m_rockEvent;
	
	
public:
	RockManager() = default;
	~RockManager() = default;


	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();


	bool GetIsPushButton();

	int FlagGet();

	std::shared_ptr<aetherClass::ModelBase> Get();
};
