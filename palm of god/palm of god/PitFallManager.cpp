#include "PitFallManager.h"

using namespace aetherClass;
using namespace Pitfall;


bool PitFallManager::Initialize(ViewCamera* camera ,Vector3 origin){

	
	m_pitfalllib[0] = std::make_shared<PitFallLib>();
	if (!m_pitfalllib[0]->Initialize()){
		return false;
	}
	m_pitfalllib[0]->SetCamera(camera);
	m_pitfalllib[0]->GetTransform()._translation = origin;
	m_pitfalllib[0]->GetTransform()._translation._x += 1;

	m_pitfalllib[1] = std::make_shared<PitFallLib>();
	if (!m_pitfalllib[1]->Initialize()){
		return false;
	}
	m_pitfalllib[1]->SetCamera(camera);
	m_pitfalllib[1]->GetTransform()._translation = origin;
	m_pitfalllib[1]->GetTransform()._translation._x -= 1;
	m_pitfalllib[1]->GetTransform()._rotation._y = 180;
	
	m_pitfall = std::make_shared<PitFall>();
	if (!m_pitfall->Initialize()){
		return false;
	}
	m_pitfall->SetCamera(camera);
	m_pitfall->GetTransform()._translation = origin;

	m_updater = std::make_shared<PitFallUpdater>();
	m_render = std::make_shared<PitFallRender>();
	return true;
}

void PitFallManager::Shutdown(){
	for (int i = 0; i < 2; i++)
	{
		m_pitfalllib[i]->Finalize();
	}
	m_pitfall->Finalize();
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


void PitFallManager::Render(std::shared_ptr<ShaderBase>shader){
	for (int i = 0; i < M_PITLIB; i++)
	{
		m_render->Render(m_pitfalllib[i].get(), shader);
	}
	m_render->Render(m_pitfall.get(), shader);
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
