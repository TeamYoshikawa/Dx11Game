#include "UiGame.h"
#include "Rectangle2D.h"
#include <iostream>

using namespace aetherClass;

bool UiGame::Initialize(){

	std::cout << "init" << std::endl;

	u_flag = OFF;

	h_max = 3;


	h_ui = std::make_shared<aetherClass::Rectangle2D>();

	for (i = 0; i < h_max; i++){
		heart[i] = std::make_shared<aetherClass::Rectangle2D>();
	}

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
	h_ui_tex->Load("Texture/UI_ba-3.png");



	for (i = 0; i < h_max; i++){
		heart[i]->SetTexture(heart_tex);		//テクスチャーのセット
	}
	h_ui->SetTexture(h_ui_tex);



	h_ui->property._transform._translation = Vector3(10.0f, 10.0f, 0.1f);
	h_ui->property._transform._scale = Vector3(220.0f, 70.0f, 0.0f);
	h_ui->property._transform._rotation = Vector3(0.0f, 0.0f, 0.0f);


	for (i = 0; i < h_max; i++){
		heart[i]->property._transform._scale = Vector3(38.0f, 38.0f, 0.0f);
		heart[i]->property._transform._translation = Vector3(40.0f + i* 60.0, 24.0f, 0.0f);
	}

	return true;

}

void UiGame::Update()
{
	return;
}

void UiGame::Life(){

	for (int i = 0; i < h_max; i++){
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

	h_ui->Render(m_shader.get());

	for (int i = 0; i < h_max; i++){
		if (heart[i]){
			heart[i]->Render(m_shader.get());
		}
	}



	return;
}


