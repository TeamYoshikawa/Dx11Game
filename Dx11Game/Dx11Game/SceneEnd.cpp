#include "SceneEnd.h"
#include "SceneGame.h"
#include "SceneTitle.h"
using namespace DxMath;

const std::string SceneEnd::m_thisName = "End";

SceneEnd::SceneEnd(SceneManager* manager):
SceneBase(m_thisName, *manager)
{
}


SceneEnd::~SceneEnd()
{
}

void SceneEnd::Initialize(Dx11::Direct3DManager* direct3d, HWND hWnd){
	std::cout << "GameOver" << std::endl;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	m_camera.Translation(Vector3(0, 0, -0.5));
	m_camera.Rotation(Vector3(0.0f, 0.0f, 0.0f));

	cube.Initialize(&m_camera, "yaju.jpg");
	texshader = std::make_shared<DxShader::TextureShader>();
	texshader->Initialize(direct3d->GetDevice(), hWnd, L"Shader/texture.vs", L"Shader/texture.ps");

}

void SceneEnd::Updata()
{
	if (GetKeyState('X') & 0x8000)
	{
		std::cout << "‰Ÿ‚³‚ê‚½‚æ" << std::endl;
		//ƒ^ƒCƒgƒ‹‚É–ß‚éˆ—
		SetChangeScene(SceneGame::m_thisName);
	}
	return;
}


void SceneEnd::Render(){
	m_camera.Render();
	Paint();
	cube.Render(texshader, DxModel::eRenderWay::eTexture);
	return;
}

void SceneEnd::Shutdown(){

	return;
}
void SceneEnd::Paint(){
	HDC hdc = GetDC(NULL);

	LPCWSTR text = TEXT("GameOver");
	
	TextOut(hdc, 700, 700, text, lstrlen(text)); 
	

}