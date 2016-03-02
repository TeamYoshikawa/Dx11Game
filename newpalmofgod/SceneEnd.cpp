#include "SceneEnd.h"
#include "SceneTitle.h"
#include "Rectangle2D.h"
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

	// �V�F�[�_�[�쐬���̏��̐ݒ�
	m_shader = std::make_shared<PixelShader>();
	ShaderDesc textureDesc;
	textureDesc._vertex._entryName = "vs_main";
	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";

	// �V�F�[�_�[�̍쐬
	textureDesc._pixel._entryName = "ps_main";
	textureDesc._pixel._srcFile = L"Shader/ColorTexture.ps";
	m_shader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	// �J�����̏�����
	m_camera = std::make_shared<ViewCamera>();
	m_camera->Translation() = Vector3(-260, -350, 447);
	m_camera->Rotation() = Vector3(-160.0f, 0.0f, 1.0f);

	// ���C�g�̍쐬
	m_lightmanager = std::make_shared<LightManager>();
	m_lightmanager->Initialize();
	m_lightmanager->GetLight()->Translation() = m_camera->Translation();

	// �e�N�X�`���̏�����
	Texture *gameover_tex = new Texture();/*press any hogehoge*/
	gameover_tex->Load("image/gameover.png");

	// �Q�[���I�[�o�[�̏�����
	m_gameover = std::make_shared<aetherClass::Rectangle2D>();
	m_gameover->Initialize();
	m_gameover->SetTexture(gameover_tex);
	m_gameover->property._transform._translation = Vector3(0, 0, 0.1);
	m_gameover->property._transform._scale._x = 800;
	m_gameover->property._transform._scale._y = 600;
	m_gameover->property._color._alpha = 1;

	// �t�F�[�h�C���̏�����
	feedin = std::make_shared<aetherClass::Rectangle2D>();
	feedin->Initialize();
	feedin->property._transform._translation = m_camera->Translation();
	feedin->property._transform._translation._z -= 10;
	feedin->property._transform._translation._y += 1000;
	feedin->property._color._alpha = 1;
	feedin->property._transform._scale._x = 800;
	feedin->property._transform._scale._y = 600;

	// �V�[���̏�����
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
	if (GameController::GetKey().IsKeyDown(DIK_R)){
		ChangeScene("Title", false);
	}
}

bool SceneEnd::TransitionIn()
{
	m_camera->Render();

	feedin->property._color._alpha -= 0.0007;
	feedin->Render(m_shader.get());

	if (feedin->property._color._alpha < 0)
	{
		return kTransitionEnd;
	}
	else if (feedin->property._color._alpha > 1)
	{
		return kTransitionning;
	}

	return kTransitionning;
}