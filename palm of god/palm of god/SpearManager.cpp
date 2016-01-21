#include"SpearManager.h"

using namespace aetherClass;
bool SpearManager::Initialize(ViewCamera *camera)
{
	// ‚¿‚å‚Á‚Æ‚æ‚­‚í‚©‚ñ‚È‚¢‚Ì‚Å•Û—¯
	for (int i = 0; i < 3; i++){
		/*m_spear[i] = std::make_shared<Spear>();
		m_spear[i]->Initialize(camera, "ModelData/textures/tex.png");
		m_spear[i]
		m_spear[i]->Scaling(DxMath::Vector3(50.0f, 65.5f, 0.0f));*/
	}
	
	//m_spear[0]->Translation(DxMath::Vector3(-280.0f, -100.f, 185.0f));
	//m_spear[1]->Translation(DxMath::Vector3(-290.0f, -100.f, 195.0f));
	//m_spear[2]->Translation(DxMath::Vector3(-300.0f, -100.f, 205.0f));

	if (!m_spear){
		return false;
	}



	m_spearRender = std::make_shared<SpearRender>();

	m_spearUpdater = std::make_shared<SpearUpdater>();

	

	

	
	return true;
}

void SpearManager::Render(const std::shared_ptr<aetherClass::ShaderBase>shader)
{
	//m_spearRender->Renderring(m_floor.get(), shader, eRen);

	for (int i = 0; i < 3; i++){
		//m_spearRender->Renderring(m_spear[i].get(), shader);
	}
	

	
}

void SpearManager::Update(bool m_switch)
{

	for (int i = 0; i < 3; i++){
//		m_spearUpdater->Updating(m_spear[i].get(), m_switch);
	}
	
}



void SpearManager::Shutdown()
{
	for (int i = 0; i < 3; i++){
		//m_spear[i].get()->Shutdown();
	}
}