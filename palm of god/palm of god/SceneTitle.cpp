#include "SceneTitle.h"
#include "SceneGame.h"
#include "GamesController.h"
#include "Vector3.h"
using namespace aetherClass;
const std::string SceneTitle::m_thisName = "Title";
SceneTitle::SceneTitle(SceneManager* manager) :
SceneBase(m_thisName, *manager)
{
}


SceneTitle::~SceneTitle()
{
}


void SceneTitle::Initialize(Direct3DManager* direct3d, HWND hWnd){
	std::cout << "Start title" << std::endl;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	m_camera.Translation(Vector3(-5,10, 0));
	m_camera.Rotation(Vector3(45.0f,90.0f,0.0f));
	Gamescontroller::Gamescontroller::Create(hInstance,hWnd);
	Gamescontroller::Gamescontroller::GetPointer()->SetCamera(&m_camera);
	Gamescontroller::Gamescontroller::GetPointer()->CopyManagerAddress(direct3d);
	sphere.Initialize(&m_camera, "yaju.jpg");
	m_texture = std::make_shared<Texture>();
	m_texture->Load(direct3d->GetDevice(), "Shader/texture.vs","Shader/texture.ps");
	return;
}


void SceneTitle::Updata(){
    Gamescontroller::Gamescontroller::GetPointer()->Frame();
	if (Gamescontroller::Gamescontroller::GetPointer()->IsLeftButtonTrigger()){
	DxMath::Vector3 rayOrigin, rayDirection;
	Gamescontroller::Gamescontroller::GetPointer()->Intersection(rayOrigin,rayDirection);
	if (sphere.RayIntersect(rayOrigin, rayDirection, 100.0f)){
		/*�Ȃ񂩂��������ɏ����������݂����ł��B�F���܂����͂��肪�Ƃ��������܂���*/
		sphere.Rotation()._y += 30.0f;
	}
  }
	return;
}


void SceneTitle::Render(){
	m_camera.Render();
	sphere.Render(texshader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneTitle::Shutdown(){

	return;
}