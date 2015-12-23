#pragma once

#include"PitFall.h"
#include"PitFallLib.h"
#include"PitFallUpdater.h"
#include"PitFallRender.h"
#include"ShaderBase.h"
#include"GameController.h"

#include<memory>


#include"ViewCamera.h"

class PitFallManager
{
	const unsigned int M_PITLIB = 2;
private:
	std::shared_ptr<Pitfall::PitFall>m_pitfall;
	std::shared_ptr<Pitfall::PitFallLib> m_pitfalllib[2];
	
	std::shared_ptr<Pitfall::PitFallUpdater>m_updater;
	std::shared_ptr<Pitfall::PitFallRender>m_render;

public:
	PitFallManager() = default;
	~PitFallManager() = default;

	bool Initialize(DxCamera::ViewCamera* camera,DxMath::Vector3 origin);
	void Render(std::shared_ptr<DxShader::ShaderBase>shader, DxModel::eRenderWay);
	void Update();
	void Shutdown();
	void ChangeCamera(DxCamera::ViewCamera* camera);
};

