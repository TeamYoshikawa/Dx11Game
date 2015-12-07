#include "SceneGame.h"
#include "FbxBase.h"
const std::string SceneGame::m_thisName = "Game";

SceneGame::SceneGame(SceneManager* manager) :
SceneBase(m_thisName,*manager){
	
	
}


SceneGame::~SceneGame()
{
}

void SceneGame::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	std::cout << "Start game" << std::endl;


	m_camera = std::make_shared<DxCamera::ViewCamera>();
	m_camera->Translation(Dx11Math::Vector3(0, 0, -50));

	m_color = std::make_shared<DxShader::ColorShader>();
	m_color->Initialize(direct3d->GetDevice(), hWnd, L"Shader/color.vs", L"Shader/color.ps");


	m_static = std::make_shared<DxModel::FbxStaticMesh>();
	m_static->LoadFBX("Box_Sample.fbx", DxFbx::FbxLoader::eAxisSystem::eAxisOpenGL);
	m_static->Initialize(m_camera.get());

	m_cube = std::make_shared<DxModel::Cube>();
	m_cube->Initialize(m_camera.get());
	return;
}


void SceneGame::Updata(){

	return;
}


void SceneGame::Render(){
	m_camera->Render();
	m_static->AllNodeRender(m_color, DxModel::eRenderWay::eColor);
	return;
}

void SceneGame::Shutdown(){

	return;
}