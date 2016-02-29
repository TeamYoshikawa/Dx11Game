#pragma once

#include "FallingWallUpdater.h"
#include "FallingWallRender.h"

#include <ViewCamera.h>

class FallingWallManager
{
public:
	FallingWallManager();
	~FallingWallManager();

	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();
	bool HitMesh(std::shared_ptr<aetherClass::ModelBase>& player, std::shared_ptr<aetherClass::ModelBase>& other);
	std::shared_ptr<aetherClass::ModelBase> GetFallingWall();

private:
	float m_size;

private:
	std::shared_ptr<aetherClass::ModelBase> m_fallingWall;
	std::shared_ptr<aetherClass::Texture> m_texture;
	std::shared_ptr<aetherClass::ModelBase> m_collider;

	std::shared_ptr<FallingWallRender> m_render;
	std::shared_ptr<FallingWallUpdater> m_updater;

};

