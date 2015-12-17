#include "PitFallManager.h"

using namespace DxCamera;
using namespace Pitfall;
using namespace DxMath;
using namespace DxController;


bool PitFallManager::Initialize(ViewCamera* camera ,Vector3 origin){

	
	m_pitfalllib[0] = std::make_shared<PitFallLib>();
	if (!m_pitfalllib[0]->Initialize(camera)){
		return false;
	}

	m_pitfalllib[0]->Translation(origin);
	m_pitfalllib[0]->Translation()._x += 1;

	m_pitfalllib[1] = std::make_shared<PitFallLib>();
	if (!m_pitfalllib[1]->Initialize(camera)){
		return false;
	}
	m_pitfalllib[1]->Translation(origin);
	m_pitfalllib[1]->Translation()._x -= 1;
	m_pitfalllib[1]->Rotation()._y = 180;
	
	m_pitfall = std::make_shared<PitFall>();
	if (!m_pitfall->Initialize(camera)){
		return false;
	}
	m_pitfall->Translation(origin);

	m_updater = std::make_shared<PitFallUpdater>();
	m_render = std::make_shared<PitFallRender>();
	return true;
}

void PitFallManager::Shutdown(){
	for (int i = 0; i < 2; i++)
	{
		m_pitfalllib[i]->Shutdown();
	}
	m_pitfall->Shutdown();
	return;
}

void PitFallManager::Update(){
	static bool button = false;
		button = GameController::GetPointer()->IsKeyDown(DIK_X) ? true : false;
		for (int i = 0; i < 2; i++)
		{
			m_updater->Update(m_pitfalllib[i].get(), button);
		}
		return;
}


void PitFallManager::Render(std::shared_ptr<DxShader::ShaderBase>shader,DxModel::eRenderWay eRen){
	for (int i = 0; i < M_PITLIB; i++)
	{
		m_render->Render(m_pitfalllib[i].get(), shader, eRen);
	}
	m_render->Render(m_pitfall.get(), shader, eRen);
	return;
}


void PitFallManager::ChangeCamera(ViewCamera *camera){
	for (int i = 0; i < M_PITLIB; i++)
	{
		m_pitfalllib[i]->SetCamera(camera);
	}
	m_pitfall->SetCamera(camera);
	return;
}
