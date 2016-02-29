#include "NavigationManager.h"

using namespace aetherClass;


bool NavigationManager::Initialize(ViewCamera* camera){


	m_navigationTexture = std::make_shared<Texture>();
	m_navigationTexture->Load("location.png");

	for (int i = 0; i < navi_max; i++){
		m_naviObj[i].m_navigation = std::make_shared<Cube>();
		if (!m_naviObj[i].m_navigation->Initialize()){
			return false;
		}
	}

	for (int i = 0; i < navi_max; i++){
		m_naviObj[i].m_navigation->SetCamera(camera);
		m_naviObj[i].m_navigation->SetTexture(m_navigationTexture.get());
	}

	for (int i = 0; i < navi_max; i++){
		m_naviObj[i].m_isRunEnd = false;
		m_naviObj[i].naviid = i;
	}

	m_naviObj[0].m_navigation->GetTransform()._translation = Vector3(1300.0f, 140.0f, 580.0f);
	m_naviObj[0].m_navigation->GetTransform()._scale = Vector3(260.0f, 40.0f, 350.0f);

	m_naviObj[1].m_navigation->GetTransform()._translation = Vector3(2000.0f, 140.0f, 580.0f);
	m_naviObj[1].m_navigation->GetTransform()._scale = Vector3(260.0f, 40.0f, 350.0f);

	return true;
}

void NavigationManager::Render(std::shared_ptr<ShaderBase>shader){

	m_naviObj[0].m_navigation->Render(shader.get());
	m_naviObj[1].m_navigation->Render(shader.get());
}

void NavigationManager::Update(int id)
{
	if (m_naviObj[id].m_isRunEnd)return;
		
	m_nowNaviID = m_naviObj[id].naviid;
	m_naviObj[id].m_isRunEnd = true;

}

void NavigationManager::Finalize()
{

	return;
}

bool NavigationManager::HitMesh(std::shared_ptr<ModelBase>& player, std::shared_ptr<ModelBase>& other){
	
	if (!m_updater->HittingProcessor(player, other))
	{
		return false;
	}

	return true;
}

int NavigationManager::Navi_IDGet(){
	return m_nowNaviID;
}

std::shared_ptr<aetherClass::ModelBase> NavigationManager::Navi_Get(int i){
	return m_naviObj[i].m_navigation;
}


int NavigationManager::NaviCnt(){
	return navi_max;
}