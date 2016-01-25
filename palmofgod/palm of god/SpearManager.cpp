#include"SpearManager.h"

using namespace aetherClass;
using namespace n_Spear;

bool SpearManager::Initialize(ViewCamera *camera)
{
	
	// ‚¿‚å‚Á‚Æ‚æ‚­‚í‚©‚ñ‚È‚¢‚Ì‚Å•Û—¯
	/*for (int i = 0; i < 3; i++){
		m_spearTexture[i] = std::make_shared<Texture>();
		m_spearTexture[i]->Load("ModelData/Textures/tex.jpg");
		m_spear[i] = std::make_shared<Cube>();
		m_spear[i]->Initialize();
		m_spear[i]->SetTexture(m_spearTexture[i].get());
		//m_spear[i]
		m_spear[i]->GetTransform()._scale = Vector3(50.0f, 65.5f, 0.0f);
	}
	
	m_spear[0]->GetTransform()._translation = Vector3(-280.0f, -100.0f, 185.0f);
	m_spear[1]->GetTransform()._translation = Vector3(-290.0f, -100.f, 195.0f);
	m_spear[2]->GetTransform()._translation = Vector3(-300.0f, -100.f, 205.0f);*/

	m_spearTexture = std::make_shared<Texture>();
	m_spearTexture->Load("ModelData/textures/tex.png");

	m_spear = std::make_shared<Cube>();
	m_spear->Initialize();
	m_spear->SetCamera(camera);
	m_spear->SetTexture(m_spearTexture.get());
	m_spear->GetTransform()._scale = Vector3(50.0f, 65.5f, 0.0f);
	m_spear->GetTransform()._translation = Vector3(150.0f, 200.0f, 30.0f);


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

	//for (int i = 0; i < 3; i++){
		m_spearRender->Renderring(m_spear.get(), shader);
	//}
	

	
}

void SpearManager::Update(bool m_switch)
{

	//for (int i = 0; i < 3; i++){
		m_spearUpdater->Updating(m_spear.get(), m_switch);
	//}
	
}



void SpearManager::Shutdown()
{
	//for (int i = 0; i < 3; i++){
		m_spear.get()->Finalize();
	//}
}