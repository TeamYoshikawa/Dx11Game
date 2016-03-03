#include "NavigationManager.h"

using namespace aetherClass;


bool NavigationManager::Initialize(ViewCamera* camera){


	m_navigationTexture = std::make_shared<Texture>();
	m_navigationTexture->Load("texture/location.png");


	m_clearbox = std::make_shared<Cube>();
	m_clearbox->Initialize();

	for (int i = 0; i < navi_max; i++){
		m_naviObj[i].m_navigation = std::make_shared<Cube>();
		if (!m_naviObj[i].m_navigation->Initialize()){
			return false;
		}
	}


	m_clearbox->SetCamera(camera);
	m_clearbox->SetTexture(m_navigationTexture.get());
	for (int i = 0; i < navi_max; i++){
		m_naviObj[i].m_navigation->SetCamera(camera);
		m_naviObj[i].m_navigation->SetTexture(m_navigationTexture.get());
	}

	for (int i = 0; i < navi_max; i++){
		m_naviObj[i].m_isRunEnd = false;
		m_naviObj[i].naviid = i;
	}

	m_naviObj[0].m_navigation->property._transform._translation = Vector3(1900.0f, 140.0f, 580.0f);
	m_naviObj[0].m_navigation->property._transform._scale = Vector3(260.0f, 40.0f, 350.0f);

	m_naviObj[1].m_navigation->property._transform._translation = Vector3(4050.0f, 140.0f, 2200.0f);
	m_naviObj[1].m_navigation->property._transform._scale = Vector3(260.0f, 20.0f, 180.0f);

	m_naviObj[2].m_navigation->property._transform._translation = Vector3(5244.0f, 140.0f, 2225.0f);
	m_naviObj[2].m_navigation->property._transform._scale = Vector3(350.0f, 20.0f, 310.0f);

	m_naviObj[3].m_navigation->property._transform._translation = Vector3(5630.0f, 140.0f, 667.0f);
	m_naviObj[3].m_navigation->property._transform._scale = Vector3(260.0f, 20.0f, 410.0f);

	m_naviObj[4].m_navigation->property._transform._translation = Vector3(8645.0f, 140.0f, 697.0f);
	m_naviObj[4].m_navigation->property._transform._scale = Vector3(260.0f, 20.0f, 380.0f); 

	m_clearbox->property._transform._translation = Vector3(9600.0f, 140.0f, 2200.0f);
	m_clearbox->property._transform._scale = Vector3(300, 300, 300);
	return true;
}

void NavigationManager::Render(std::shared_ptr<ShaderBase>shader){

	for (int i = 0; i < navi_max; i++){
		m_naviObj[i].m_navigation->Render(shader.get());
	}
	m_clearbox->Render(shader.get());
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

std::shared_ptr<aetherClass::ModelBase> NavigationManager::Clear_Get(){
	return m_clearbox;
}

int NavigationManager::NaviCnt(){
	return navi_max;
}