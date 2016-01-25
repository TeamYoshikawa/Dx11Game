#include "UiGame.h"

using namespace aetherClass;


bool UiGame::Initialize(){

	flag = OFF;
	std::cout << "init" << std::endl;

	location = std::make_shared<Cube>();
	goal = std::make_shared<Cube>();
	start = std::make_shared<Cube>();
	road = std::make_shared<Cube>();
	heart = std::make_shared<Cube>();
	heart1 = std::make_shared<Cube>();
	heart2 = std::make_shared<Cube>();
	m_uicamera = std::make_shared<ViewCamera>();

	location->Initialize();
	goal->Initialize();
	start->Initialize();
	road->Initialize();
	heart->Initialize();
	heart1->Initialize();
	heart2->Initialize();


	ShaderDesc  shaderdesc;
	shaderdesc._pixel._srcFile = L"Shader/texture.ps";
	shaderdesc._pixel._entryName = "ps_main";

	shaderdesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	shaderdesc._vertex._entryName = "vs_main";


	Texture *heart_tex = new Texture();	//テクスチャー用
	Texture *start_tex = new Texture();	//テクスチャー用
	Texture *location_tex = new Texture();	//テクスチャー用
	Texture *road_tex = new Texture();	//テクスチャー用


	heart_tex->Load("Heart.png");	//画像の読み込み
	start_tex->Load("goal.png");	//画像の読み込み
	location_tex->Load("location.png");	//画像の読み込み
	road_tex->Load("road.png");	//画像の読み込み

	location->SetTexture(location_tex);
	start->SetTexture(start_tex);
	goal->SetTexture(start_tex);
	road->SetTexture(road_tex);
	heart->SetTexture(heart_tex);		//テクスチャーのセット
	heart1->SetTexture(heart_tex);		//テクスチャーのセット
	heart2->SetTexture(heart_tex);		//テクスチャーのセット
	//location->GetColor() = Color(0.5f,0.7f,0.2f,1);


	m_shader = std::make_shared<PixelShader>();
	m_shader->Initialize(shaderdesc, ShaderType::ePixel | ShaderType::eVertex);


	m_uicamera->Translation() = Vector3(900.0f, 900.0f, -900.0f);


	location->GetTransform()._scale = Vector3(0.8f, 0.8f, 0.0f);
	location->GetTransform()._translation = Vector3(20.0f, -8.2f, 45.0f) + m_uicamera->Translation();
	location->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	goal->GetTransform()._scale = Vector3(1.0f, 1.0f, 0.0f);
	goal->GetTransform()._translation = Vector3(20.0f, 10.0f, 45.0f) + m_uicamera->Translation();
	goal->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	start->GetTransform()._scale = Vector3(1.0f, 1.0f, 0.0f);
	start->GetTransform()._translation = Vector3(20.0f, -10.0f, 45.0f) + m_uicamera->Translation();
	start->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	road->GetTransform()._scale = Vector3(0.8f, 9.0f, 0.0f);
	road->GetTransform()._translation = Vector3(20.0f, -0.0f, 45.0f) + m_uicamera->Translation();
	road->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);


	heart->GetTransform()._scale = Vector3(1.0f, 1.0f, 0.0f);
	heart->GetTransform()._translation = Vector3(-25.0f, 20.0f, 60.0f) + m_uicamera->Translation();

	heart1->GetTransform()._scale = Vector3(1.0f, 1.0f, 0.0f);
	heart1->GetTransform()._translation = Vector3(-22.5f, 20.0f, 60.0f) + m_uicamera->Translation();


	heart2->GetTransform()._scale = Vector3(1.0f, 1.0f, 0.0f);
	heart2->GetTransform()._translation = Vector3(-20.0f, 20.0f, 60.0f) + m_uicamera->Translation();

	road->SetCamera(m_uicamera.get());
	location->SetCamera(m_uicamera.get());
	goal->SetCamera(m_uicamera.get());
	start->SetCamera(m_uicamera.get());

	heart->SetCamera(m_uicamera.get());
	heart1->SetCamera(m_uicamera.get());
	heart2->SetCamera(m_uicamera.get());


	return true;

}

void UiGame::Update()
{

	std::cout <<  "ごみ:"<< location->GetTransform()._translation._y << std::endl;

	if (location->GetTransform()._translation._y > 907.0f){

		//heart->Finalize();
		//heart.reset();
		flag = ON;


	}
	if (flag == OFF){
		location->GetTransform()._translation._y += 0.1f;
	}


	return;
}

void UiGame::Render(){

	m_uicamera->Render();

	location->Render(m_shader.get());
	start->Render(m_shader.get());
	goal->Render(m_shader.get());
	road->Render(m_shader.get());
	if (heart){
		std::cout << "呼ばれた\n";
		heart->Render(m_shader.get());
	}
	heart1->Render(m_shader.get());
	heart2->Render(m_shader.get());

	return;
}

	
