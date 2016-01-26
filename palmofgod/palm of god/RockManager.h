#pragma once

#include"RockUpdater.h"
#include"RockRender.h"

#include <GameController.h>
#include <Sphere.h>
#include <memory>
#include <Texture.h>
#include <ViewCamera.h>


class RockManager
{
private:
	std::shared_ptr<aetherClass::Sphere>m_Rock;
	std::shared_ptr<aetherClass::Sphere>m_switch;

	std::shared_ptr<aetherClass::Texture> m_rockTexture;
	std::shared_ptr<n_Rock::RockUpdater>m_updater;
	std::shared_ptr<n_Rock::RockRender>m_render;

	

public:
	RockManager() = default;
	~RockManager() = default;

	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();
	void Shutdown();
};
