#pragma once

#include"Rock.h"
#include"RockUpdater.h"
#include"RockRender.h"

#include"GameController.h"
#include"Sphere.h"
#include <memory>

#include"ViewCamera.h"

class RockManager
{
private:
	std::shared_ptr<DxModel::Sphere>m_Rock;

	std::shared_ptr<n_Rock::RockUpdater>m_updater;
	std::shared_ptr<n_Rock::RockRender>m_render;

public:
	RockManager() = default;
	~RockManager() = default;

	bool Initialize(DxCamera::ViewCamera* camera);
	void Render(const std::shared_ptr<DxShader::ShaderBase>, DxModel::eRenderWay);
	void Update();
	void Shutdown();
};
