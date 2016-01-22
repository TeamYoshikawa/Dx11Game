#include "RockManager.h"

using namespace aetherClass;
using namespace n_Rock;


bool RockManager::Initialize(ViewCamera* camera){
	m_rockTexture = std::make_shared<Texture>();
	m_rockTexture->Load("ModelData/textures/seafloor.dds");
	m_Rock = std::make_shared<Sphere>(10,10,10);
	if (!m_Rock->Initialize()){
		return false;
	}
	m_Rock->SetCamera(camera);
	m_Rock->SetTexture(m_rockTexture.get());
	m_Rock->GetTransform()._translation = Vector3(2620.0f, -412.f, 2030.0f);
	m_Rock->GetTransform()._scale= Vector3(100.0f, 100.0f, 100.0f);

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
	m_Rock->Finalize();
}

void RockManager::Render(std::shared_ptr<ShaderBase>shader){
	m_render->Render(m_Rock.get(), shader);
}
