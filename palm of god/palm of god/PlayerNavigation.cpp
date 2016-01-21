#include "PlayerNavigation.h"
#include <assert.h>
#include <iostream>
using namespace aetherClass;
std::shared_ptr<Cube> PlayerNavigation::m_navigationBox = nullptr;
std::shared_ptr<aetherClass::Texture> PlayerNavigation::m_texture = nullptr;
int PlayerNavigation::m_navigationID = 0;
// ナビげーション用の位置
Vector3 PlayerNavigation::m_navigationBoxPosition[] = {
	{ Vector3(320.0f, -100.f, 200.0f) },
	{ Vector3(1265.0f, -100.f, 251.0f) },
	{ Vector3(2200.0f, -100.f, 100.0f) },
	{ Vector3(2555.0f, -100.f, 100.0f) }
};

PlayerNavigation::PlayerNavigation()
{
}


PlayerNavigation::~PlayerNavigation()
{
}

void PlayerNavigation::Initialize(std::shared_ptr<ViewCamera> camera){

	m_texture->Load("ModelData/textures/cylinder_template.jpg");
	m_navigationBox = std::make_shared<Cube>();
	m_navigationBox->Initialize();
	m_navigationBox->SetTexture(m_texture.get());
	m_navigationBox->SetCamera(camera.get());
	
	// 配列の要素数を求める
	m_navigationArrayElement = sizeof(m_navigationBoxPosition) / sizeof(m_navigationBoxPosition[0]);
	std::cout << m_navigationArrayElement << std::endl;
	Vector3 initilaizePosition = m_navigationBoxPosition[0];

	// 初期位置は配列の0番目

	m_navigationBox->GetTransform()._translation = initilaizePosition;
	m_navigationBox->GetTransform()._rotation = Vector3(50, 50, 50);
	

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

std::shared_ptr<Cube> PlayerNavigation::GetNavigationBox(){

	m_navigationBox->GetTransform()._translation = m_navigationBoxPosition[m_navigationID];
	return m_navigationBox;
}


void PlayerNavigation::Render(std::shared_ptr<ShaderBase> shader){
	m_navigationBox->Render(shader.get());
}

int PlayerNavigation::GetNavigationID()const{
	return m_navigationID;
}