#include "PlayerNavigation.h"
#include <assert.h>
#include <iostream>
using namespace DxModel;
using namespace DxMath;
std::shared_ptr<Cube> PlayerNavigation::m_navigationBox = nullptr;

int PlayerNavigation::m_navigationID = 0;
// ナビげーション用の位置
Vector3 PlayerNavigation::m_navigationBoxPosition[] = {
	{ DxMath::Vector3(320.0f, -100.f, 200.0f) },
	{ DxMath::Vector3(1265.0f, -100.f, 251.0f) },
	{ DxMath::Vector3(2200.0f, -100.f, 100.0f) },
	{ DxMath::Vector3(2555.0f, -100.f, 100.0f) }
};

PlayerNavigation::PlayerNavigation()
{
}


PlayerNavigation::~PlayerNavigation()
{
}

void PlayerNavigation::Initialize(std::shared_ptr<DxCamera::ViewCamera> camera){


	m_navigationBox = std::make_shared<DxModel::Cube>();
	m_navigationBox->Initialize(camera.get(), "ModelData/textures/cylinder_template.jpg");
	// 配列の要素数を求める
	m_navigationArrayElement = sizeof(m_navigationBoxPosition) / sizeof(m_navigationBoxPosition[0]);
	std::cout << m_navigationArrayElement << std::endl;
	Vector3 initilaizePosition = m_navigationBoxPosition[0];

	// 初期位置は配列の0番目
	m_navigationBox->Translation(initilaizePosition);
	m_navigationBox->Scaling(Vector3(50, 50, 50));
	

	return;
}

void PlayerNavigation::NextSet(){
	m_navigationID += 1;
	std::cout << m_navigationID << std::endl;
	if (m_navigationID > m_navigationArrayElement)
	{
		m_navigationID = m_navigationArrayElement - 1;
	}

	return;
}

std::shared_ptr<DxModel::Cube> PlayerNavigation::GetNavigationBox(){

	m_navigationBox->Translation(m_navigationBoxPosition[m_navigationID]);
	return m_navigationBox;
}


void PlayerNavigation::Render(std::shared_ptr<DxShader::ShaderBase> shader){
	m_navigationBox->Render(shader, DxModel::eRenderWay::eTexture);
}

int PlayerNavigation::GetNavigationID()const{
	return m_navigationID;
}