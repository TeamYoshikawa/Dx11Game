#include "RockManager.h"

using namespace DxCamera;
using namespace n_Rock;
using namespace DxMath;
using namespace DxController;

bool RockManager::Initialize(ViewCamera* camera){

	m_Rock = std::make_shared<DxModel::Cube>();
	if (!m_Rock->Initialize(camera,"ModelData/textures/seafloor.dds")){
		return false;
	}

	m_Rock->Translation(DxMath::Vector3(2620.0f, -412.f, 2030.0f));
	m_Rock->Scaling(DxMath::Vector3(100.0f, 100.0f, 100.0f));

	m_updater = std::make_shared<RockUpdater>();
	m_render = std::make_shared<RockRender>();

	return true;
}

void RockManager::Update(){
	static bool button = false;
	button = GetKeyState('X') & 0x8000 ? true : false;

	m_updater->Update(m_Rock.get(), button);
	
}

void RockManager::Shutdown(){
	m_Rock->Shutdown();
}

void RockManager::Render(std::shared_ptr<DxShader::ShaderBase>shader, DxModel::eRenderWay eRen){
	m_render->Render(m_Rock.get(), shader, eRen);
}
