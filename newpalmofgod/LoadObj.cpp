#include "LoadObj.h"
#include <Rectangle.h>
using namespace aetherClass;
using namespace std;
LoadObj::LoadObj()
{
}


LoadObj::~LoadObj()
{
}




void LoadObj::Initialize()
{

	InitCamera();
	InitPixelShader();
	

	load = std::make_shared<aetherClass::Rectangle>();
	load->Initialize();

	Texture *load_tex = new Texture();
	load_tex->Load("image/Load.jpg");

	load->SetTexture(load_tex);
	load->SetCamera(m_camera.get());
	load->GetTransform()._translation = m_camera->Translation();
	load->GetTransform()._translation._z = 270;
	
	load->GetTransform()._rotation._x = 180;
	load->GetTransform()._scale._x = 100;
	load->GetTransform()._scale._y = 73;

}

void LoadObj::InitPixelShader()
{
	ShaderDesc textureDesc;
	textureDesc._pixel._srcFile = L"Shader/ColorTexture.ps";
	textureDesc._pixel._entryName = "ps_main";

	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	textureDesc._vertex._entryName = "vs_main";

	m_pixelShader = std::make_shared<PixelShader>();
	m_pixelShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	Material material;
	material._ambient._color = Color(1, 0, 0, 1);
	material._diffuse._color = Color(1, 0, 0, 1);
	material._specular._color = Color(1, 0, 0, 1);
	material._specularPower = 4;
}


void LoadObj::InitCamera()
{
	m_camera = std::make_shared<ViewCamera>();
	m_camera->Translation() = Vector3(-260, -380, 447);
	m_camera->Rotation() = Vector3(-180.0f, 0.0f, 0.0f);
}


void LoadObj::Run()
{
	m_camera->Render();

	load->Render(m_pixelShader.get());
	return;

}
void LoadObj::Finalize()
{
	return;

}