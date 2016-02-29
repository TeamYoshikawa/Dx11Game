 #include "UiGame.h"

using namespace aetherClass;

bool UiGame::Initialize(){

	std::cout << "init" << std::endl;

	u_flag = OFF;
	
	h_max = 3;

	location = std::make_shared<aetherClass::Rectangle>();
	goal = std::make_shared<aetherClass::Rectangle>();
	start = std::make_shared<aetherClass::Rectangle>();
	road = std::make_shared<aetherClass::Rectangle>();
	m_uicamera = std::make_shared<ViewCamera>();
	h_ui = std::make_shared<Cube>();

	for (i = 0; i < h_max; i++){
		heart[i] = std::make_shared<aetherClass::Rectangle>();
	}
	

	location->Initialize();
	goal->Initialize();
	start->Initialize();
	road->Initialize();

	for (i = 0; i < h_max; i++){
		heart[i]->Initialize();
	}
	h_ui->Initialize();


	ShaderDesc  shaderdesc;
	shaderdesc._pixel._srcFile = L"Shader/texture.ps";
	shaderdesc._pixel._entryName = "ps_main";

	shaderdesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	shaderdesc._vertex._entryName = "vs_main";

	m_shader = std::make_shared<PixelShader>();
	m_shader->Initialize(shaderdesc, ShaderType::eVertex | ShaderType::ePixel);


	Texture *h_ui_tex = new Texture();
	Texture *heart_tex = new Texture();	//テクスチャー用
	Texture *start_tex = new Texture();	//テクスチャー用
	Texture *location_tex = new Texture();	//テクスチャー用
	Texture *road_tex = new Texture();	//テクスチャー用
	Texture *goal_tex = new Texture();	//テクスチャー用
	

	heart_tex->Load("Texture/Heart.png");	//画像の読み込み
	start_tex->Load("Texture/goal.png");	//画像の読み込み
	goal_tex->Load("Texture/start.png");	//画像の読み込み
	location_tex->Load("Texture/location.png");	//画像の読み込み
	road_tex->Load("Texture/road.png");	//画像の読み込み
	h_ui_tex->Load("Texture/h_ui.png");

	
	location->SetTexture(location_tex);
	start->SetTexture(start_tex);
	goal->SetTexture(goal_tex);
	road->SetTexture(road_tex);
	for (i = 0; i < h_max; i++){
		heart[i]->SetTexture(heart_tex);		//テクスチャーのセット
	}
	h_ui->SetTexture(h_ui_tex);

	m_uicamera->Translation() = Vector3(900.0f, 900.0f, -900.0f);

	h_ui->GetTransform()._scale = Vector3(4.0f, 1.0f, 0.0f);
	h_ui->GetTransform()._translation = Vector3(-19.0f, 16.0f, 45.0f) + m_uicamera->Translation();
	h_ui->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	location->GetTransform()._scale = Vector3(1.0f, 1.0f, 0.0f);
	location->GetTransform()._translation = Vector3(22.5f, -8.2f, 45.0f) + m_uicamera->Translation();
	location->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	goal->GetTransform()._scale = Vector3(1.4f, 1.4f, 0.0f);
	goal->GetTransform()._translation = Vector3(22.5f, 10.0f, 45.0f) + m_uicamera->Translation();
	goal->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	start->GetTransform()._scale = Vector3(1.4f, 1.4f, 0.0f);
	start->GetTransform()._translation = Vector3(22.5f, -10.0f, 45.0f) + m_uicamera->Translation();
	start->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	road->GetTransform()._scale = Vector3(1.3f, 9.0f, 0.0f);
	road->GetTransform()._translation = Vector3(22.5f, -0.0f, 45.0f) + m_uicamera->Translation();
	road->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);

	for (i = 0; i < h_max; i++){
		heart[i]->GetTransform()._scale = Vector3(0.6f, 0.6f, 0.0f);
		heart[i]->GetTransform()._translation = Vector3(-21.5f +i* 2.5 , 16.0f, 45.0f) + m_uicamera->Translation();
	}

	
	road->SetCamera(m_uicamera.get());
	location->SetCamera(m_uicamera.get());
	goal->SetCamera(m_uicamera.get());
	start->SetCamera(m_uicamera.get());
	for (i = 0; i < h_max; i++){
		heart[i]->SetCamera(m_uicamera.get());
	}
	h_ui->SetCamera(m_uicamera.get());

	return true;

}

void UiGame::Update()
{
	
	if (location->GetTransform()._translation._y > 908.5f){
		u_flag = ON;
	}


	if (u_flag == OFF){
		location->GetTransform()._translation._y += 1.43f;
	}


	return;
}

void UiGame::Life(){

	for (int i=0; i < h_max; i++){
		if (heart[i]){
			heart[i]->Finalize();
			heart[i].reset();
		}
	}
}


int UiGame::Set(int h_player){

	h_max = h_player;

	return 0;
}


void UiGame::Render(){

	m_uicamera->Render();

	for (int i = 0; i < h_max; i++){
		if (heart[i]){
			heart[i]->Render(m_shader.get());
		}
	}

	h_ui->Render(m_shader.get());

	/*location->Render(m_shader.get());
	start->Render(m_shader.get());
	goal->Render(m_shader.get());
	road->Render(m_shader.get());*/


	return;
}

	
