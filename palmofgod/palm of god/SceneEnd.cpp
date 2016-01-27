#include "SceneEnd.h"
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
	textureDesc._pixel._srcFile = L"Shader/ColorTextureAdd2.ps";
	m_shader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	// ���C�g�̍쐬
	m_lightmanager = std::make_shared<LightManager>();
	m_lightmanager->Initialize();

	// �J�����̏�����
	m_camera = std::make_shared<aetherClass::ViewCamera>();
	m_camera->Translation() = Vector3(0, 0, -10000000);
	m_camera->Rotation() = Vector3(1.0f, 1.0f, 1.0f);

	// �e�N�X�`���̏�����
	m_texture = std::make_shared<aetherClass::Texture>();
	m_texture->Load("ModelData/textures/GameOver.png");

	// �Q�[���I�[�o�[�̏�����
	m_gameover = std::make_shared<aetherClass::Cube>();
	m_gameover->Initialize();
	m_gameover->SetCamera(m_camera.get());
	m_gameover->SetTexture(m_texture.get());
	m_gameover->GetTransform()._translation = m_camera->Translation();
	m_gameover->GetTransform()._scale = Vector3(1.0f, 1.0f, -1.0f);

	return true;
}

void SceneEnd::Render()
{
	//std::cout << "Render" << std::endl;
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
	if (GameController::GetPointer()->IsRightButtonTrigger())
	{
		ChangeScene("Title");
	}
}