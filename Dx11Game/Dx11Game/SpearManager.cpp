#include"SpearManager.h"


bool SpearManager::Initialize(DxCamera::ViewCamera *camera)
{
	for (int i = 0; i < 3; i++){
		m_spear[i] = std::make_shared<Spear>();
		m_spear[i]->Initialize(camera, "tex.jpg");
		m_spear[i]->Scaling(DxMath::Vector3(0.1f, 1.5f, 0.0f));
	}
	
	m_spear[0]->Translation(DxMath::Vector3(0.0f, -1.5f, 0.0f));
	m_spear[1]->Translation(DxMath::Vector3(2.0f, -1.5f, 0.0f));
	m_spear[2]->Translation(DxMath::Vector3(-2.0f, -1.5f, 0.0f));

	if (!m_spear){
		return false;
	}

	

	m_floor = std::make_shared<Spear>();
	m_floor->Initialize(camera, "tex.jpg");
	m_floor->Scaling(DxMath::Vector3(2.5f,0.05f,0.0f));


	m_spearRender = std::make_shared<SpearRender>();
	

	m_spearUpdater = std::make_shared<SpearUpdater>();

	

	

	
	return true;
}

void SpearManager::Render(const std::shared_ptr<DxShader::ShaderBase>shader,const DxModel::eRenderWay eRen)
{
	m_spearRender->Renderring(m_floor.get(), shader, eRen);

	for (int i = 0; i < 3; i++){
		m_spearRender->Renderring(m_spear[i].get(), shader, eRen);
	}
	

	
}

void SpearManager::Update(bool &m_switch)
{

	for (int i = 0; i < 3; i++){
		m_spearUpdater->Updating(m_spear[i].get(), m_switch);
	}
	
}



void SpearManager::Shutdown()
{
	for (int i = 0; i < 3; i++){
		m_spear[i].get()->Shutdown();
	}
}