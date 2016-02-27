#include "SceneEnd.h"
#include "SceneTitle.h"
#include "Rectangle.h"
#include <iostream>

using namespace aetherClass;

const std::string SceneEnd::m_thisName = "End";

SceneEnd::SceneEnd() :
GameScene(m_thisName, GetManager())
{
}

SceneEnd::~SceneEnd()
{
}

bool SceneEnd::Initialize()
{
	std::cout << "initialize" << std::endl;

	// シェーダー作成時の情報の設定
	m_shader = std::make_shared<PixelShader>();
	ShaderDesc textureDesc;
	textureDesc._vertex._entryName = "vs_main";
	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";

	// シェーダーの作成
	textureDesc._pixel._entryName = "ps_main";
	textureDesc._pixel._srcFile = L"Shader/ColorTexture.ps";
	m_shader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	// ライトの作成
	m_lightmanager = std::make_shared<LightManager>();
	m_lightmanager->Initialize();

	// カメラの初期化
	m_camera = std::make_shared<aetherClass::ViewCamera>();
	m_camera->Translation() = Vector3(-260, -350, 447);
	m_camera->Rotation() = Vector3(-160.0f, 0.0f, 1.0f);

	// テクスチャの初期化
	m_texture = std::make_shared<aetherClass::Texture>();
	m_texture->Load("ModelData/textures/GameOver.png");

	// ゲームオーバーの初期化
	m_gameover = std::make_shared<aetherClass::Rectangle>();
	m_gameover->Initialize();
	m_gameover->SetCamera(m_camera.get());
	m_gameover->SetTexture(m_texture.get());
	m_gameover->GetTransform()._translation = m_camera->Translation();
	m_gameover->GetTransform()._translation._z -= 200;
	m_gameover->GetTransform()._translation._y += 75;
	m_gameover->GetTransform()._scale._x = 100;
	m_gameover->GetTransform()._scale._y = 100;
	m_gameover->GetTransform()._rotation._x = 180;

	// フェードインの初期化
	feedin = std::make_shared<aetherClass::Rectangle>();
	feedin->Initialize();
	feedin->SetCamera(m_camera.get());
	feedin->GetTransform()._translation = m_camera->Translation();
	feedin->GetTransform()._translation._z -= 10;
	feedin->GetTransform()._translation._y += 1000;
	feedin->GetColor()._alpha = 1;
	feedin->GetTransform()._scale._x = 10000;
	feedin->GetTransform()._scale._y = 10000;

	// シーンの初期化
	GameScene *Scene = new SceneTitle();
	RegisterScene(Scene);

	return true;
}

void SceneEnd::Render()
{
	m_camera->Render();
	m_gameover->Render(m_shader.get());

}

bool SceneEnd::Updater()
{
	SceneChange();
	return true;
}

void SceneEnd::Finalize()
{
	std::cout << "Finalize" << std::endl;
}

void SceneEnd::SceneChange()
{
	if (GameController::GetMouse().IsLeftButtonTrigger())
	{
		ChangeScene("Title",false);
	}
}

bool SceneEnd::TransitionIn()
{
	m_camera->Render();

	feedin->GetColor()._alpha -= 0.007;
	feedin->Render(m_shader.get());

	if (feedin->GetColor()._alpha < 0)
	{
		return kTransitionEnd;
	}
	else if (feedin->GetColor()._alpha > 1)
	{
		return kTransitionning;
	}

	return kTransitionning;
}