#include "LoadObj.h"
#include <Rectangle3D.h>
#include<Rectangle2D.h>
#include "GameScene.h"
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
	m_flag = 0;
	InitCamera();
	InitPixelShader();
	

	load = std::make_shared<aetherClass::Rectangle3D>();
	load->Initialize();

	Texture *load_tex = new Texture();
	load_tex->Load("image/Load.jpg");
	load->SetTexture(load_tex);
	load->SetCamera(m_camera.get());
	load->property._transform._translation = m_camera->property._translation;
	load->property._transform._translation._z = 270;
	load->property._transform._rotation._x = 180;
	load->property._transform._scale._x = 100;
	load->property._transform._scale._y = 73;



	load02 = std::make_shared<aetherClass::Rectangle2D>();
	load02->Initialize();
    Texture *load_tex02 = new Texture();
	load_tex02->Load("image/Story02.png");
	load02->SetTexture(load_tex02);
	//load02->property._transform._camera._z =-1;
	load02->property._transform._scale._x = 800;
	load02->property._transform._scale._y = 600;

	//feed_out = std::make_shared<aetherClass::Rectangle2D>();
	//feed_out->Initialize();
	//feed_out->property._transform._scale._x = 1000;
	//feed_out->property._transform._scale._y = 1000;

	feed_in = std::make_shared<aetherClass::Rectangle2D>();
	feed_in->Initialize();
	feed_in->property._color._alpha = 1;
	feed_in->property._transform._scale._x = 800;
	feed_in->property._transform._scale._y = 600;

	m_pressFlag = true;
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
	m_camera->property._translation = Vector3(-260, -380, 447);
	m_camera->property._rotation = Vector3(-180.0f, 0.0f, 0.0f);
}


bool LoadObj::WaitRun(){

	feed_in->Render(m_pixelShader.get());
	load02->Render(m_pixelShader.get());

	std::cout << "”CˆÓ‚Ìˆ—‚Ü‚¿" << std::endl;
	GameController::GetKey().Read();

	if (feed_in->property._color._alpha < 0){
		
		m_pressFlag = true;
	}
	else if (feed_in->property._color._alpha == 1){
		m_pressFlag = false;
	}
	
	if (GameController::GetKey().IsKeyDown(DIK_SPACE))
	{
		m_flag = 1;
	}

	if (m_flag == 1){
		feed_in->property._color._alpha -= 0.01;
	}
		if (m_pressFlag){
			
			std::cout << "”CˆÓ‚Ìˆ—ŽÀs" << std::endl;
			return kWaitEnd;
		}
		else{	
			return kWaitting;
		}
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