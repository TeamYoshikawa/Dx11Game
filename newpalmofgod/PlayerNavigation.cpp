#include "PlayerNavigation.h"
#include <assert.h>
#include <iostream>
using namespace aetherClass;

// ナビげーション用の位置
Vector3 PlayerNavigation::m_navigationBoxPosition[] = {
	{ Vector3(700.0f, 100.f, 750.0f) },
	{ Vector3(1265.0f, 100.f, 700.0f) },
	{ Vector3(2200.0f, 100.f, 650.0f) },
	{ Vector3(2400.0f, 100.f, 650.0f) },
	{ Vector3(2850.0f, 100.f, 700.0f) },
	{ Vector3(2800.0f, 100.f, 2200.0f) },
	{ Vector3(3400.0f, 100.f, 2200.0f) },
	{ Vector3(4100.0f, 100.f, 2200.0f) },
	{ Vector3(5500.0f, 100.f, 2200.0f) },
	{ Vector3(5500.0f, 100.f, 650.0f) },
	{ Vector3(7200.0f, 100.f, 650.0f) },
	{ Vector3(8750.0f, 100.f, 700.0f) },
	{ Vector3(8750.0f, 100.f, 2150.0f) },
	{ Vector3(9300.0f, 100.f, 2150.0f) }
	
};

PlayerNavigation::PlayerNavigation()
{
}


PlayerNavigation::~PlayerNavigation()
{
}

void PlayerNavigation::Initialize(std::shared_ptr<ViewCamera> camera){

	m_texture = std::make_shared <Texture>();
	m_texture->Load("ModelData/textures/cylinder_template.jpg");
	m_navigationBox = std::make_shared<Cube>();
	m_navigationBox->Initialize();
	m_navigationBox->SetTexture(m_texture.get());
	m_navigationBox->SetCamera(camera.get());
	m_navigationBox->GetTransform()._scale *= 3;
	
	// 配列の要素数を求める
	m_navigationArrayElement = sizeof(m_navigationBoxPosition) / sizeof(m_navigationBoxPosition[0]);
	std::cout << m_navigationArrayElement << std::endl;
	Vector3 initilaizePosition = m_navigationBoxPosition[0];

	// 初期位置は配列の0番目

	m_navigationBox->GetTransform()._translation = initilaizePosition;
	m_navigationBox->GetTransform()._rotation = Vector3(80, 80, 80);
	
	m_navigationID = 0;
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