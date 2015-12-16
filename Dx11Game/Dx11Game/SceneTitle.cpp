#include "SceneTitle.h"
#include "SceneGame.h"
#include "GamesController.h"
#include "Vector3.h"
using namespace DxMath;
const std::string SceneTitle::m_thisName = "Title";
SceneTitle::SceneTitle(SceneManager* manager) :
SceneBase(m_thisName, *manager)
{
}


SceneTitle::~SceneTitle()
{
}


void SceneTitle::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	std::cout << "Start title" << std::endl;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	m_camera.Translation(Vector3(-5,10, 0));
	m_camera.Rotation(Vector3(45.0f,90.0f,0.0f));
	Gamescontroller::Gamescontroller::Create(hInstance,hWnd);
	Gamescontroller::Gamescontroller::GetPointer()->SetCamera(&m_camera);
	Gamescontroller::Gamescontroller::GetPointer()->CopyManagerAddress(direct3d);
	sphere.Initialize(&m_camera, "yaju.jpg");
	texshader = std::make_shared<DxShader::TextureShader>();
	texshader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs",L"Shader/texture.ps");
	return;
}


void SceneTitle::Updata(){
    Gamescontroller::Gamescontroller::GetPointer()->Frame();
	if (Gamescontroller::Gamescontroller::GetPointer()->IsLeftButtonTrigger()){
	DxMath::Vector3 rayOrigin, rayDirection;
	Gamescontroller::Gamescontroller::GetPointer()->Intersection(rayOrigin,rayDirection);
	if (sphere.RayIntersect(rayOrigin, rayDirection, 100.0f)){
		/*‚È‚ñ‚©‚±ª‚±«‚Éˆ—‚ğ‘‚­‚İ‚½‚¢‚Å‚·BŠF‚³‚Ü‚²‹¦—Í‚ ‚è‚ª‚Æ‚¤‚²‚´‚¢‚Ü‚µ‚½*/
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