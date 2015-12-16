#include "PlayerNavigation.h"
#include <assert.h>
using namespace DxModel;
using namespace DxMath;
std::shared_ptr<Cube> PlayerNavigation::m_navigationBox = nullptr;

int PlayerNavigation::m_navigationNumber = 0;
// ナビげーション用の位置
Vector3 PlayerNavigation::m_navigationBoxPosition[] = {
	{ DxMath::Vector3(320.0f, -100.f, 200.0f) },
	{ DxMath::Vector3(1265.0f, -100.f, 251.0f) }
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
	m_navigationArrayElement = sizeof(m_navigationBoxPosition[0]) / sizeof(Vector3);

	Vector3 initilaizePosition = m_navigationBoxPosition[0];

	// 初期位置は配列の0番目
	m_navigationBox->Translation(initilaizePosition);
	m_navigationBox->Scaling(Vector3(100, 100, 100));
	

	return;
}

void PlayerNavigation::NextSet(){
	m_navigationNumber += 1;
	if (m_navigationNumber > m_navigationArrayElement)
	{
		assert(!"out of renge");
	}

	return;
}

std::shared_ptr<DxModel::Cube> PlayerNavigation::GetNavigationBox(){

	m_navigationBox->Translation(m_navigationBoxPosition[m_navigationNumber]);
	return m_navigationBox;
}


void PlayerNavigation::Render(std::shared_ptr<DxShader::ShaderBase> shader){
	m_navigationBox->Render(shader, DxModel::eRenderWay::eTexture);
}