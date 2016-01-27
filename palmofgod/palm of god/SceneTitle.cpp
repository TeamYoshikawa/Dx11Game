#include "SceneTitle.h"
#include <Rectangle.h>
using namespace aetherClass;
using namespace std;

const std::string SceneTitle::m_thisName = "Title";

SceneTitle::SceneTitle() :
GameScene(m_thisName,GetManager())
{
}

SceneTitle::~SceneTitle()
{

}
bool SceneTitle::Initialize()
{
	cout << "Init SceneTitle" << endl;
	InitCamera();
	InitLight();
	InitPixelShader();
	InitMaterialShader();
	InitStage();


	
	
	title = std::make_shared<aetherClass::Rectangle>();
	title->Initialize();

	Texture *title_tex = new Texture();/*テクスチャ―用*/

	title_tex->Load("Titlelogo.png");	/*画像の読み込み*/

	title->SetTexture(title_tex);
	title->SetCamera(m_camera.get());
	title->GetTransform()._translation = m_camera->Translation();
	title->GetTransform()._translation._z -= 200;
	title->GetTransform()._translation._y += 35;
	title->GetTransform()._rotation._x = 180;
	title->GetTransform()._scale._x = 88;
	title->GetTransform()._scale._y = 53;

	/*
	title->GetTransform()._scale = Vector3(0.8f, 0.8f, 0.0f);
	title->GetTransform()._translation = Vector3(20.0f, -8.2f, 45.0f) + m_uicamera->Translation();
	title->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);
	*/
	return true;
}

bool SceneTitle::Updater()
{
	GameController::GetPointer()->Frame();
	SceneChange();

	if (GameController::GetPointer()->IsKeyDown(DIK_A))
	{
		m_camera->Translation()._x += 1;
	}
	if (GameController::GetPointer()->IsKeyDown(DIK_D))
	{
		m_camera->Translation()._x -= 1;
	}
	if (GameController::GetPointer()->IsKeyDown(DIK_W))
	{
		m_camera->Translation()._z += 1;

	}
	if (GameController::GetPointer()->IsKeyDown(DIK_S))
	{
		m_camera->Translation()._z -= 1;
	}

	if (GameController::GetPointer()->IsKeyDown(DIK_Q))
	{
		m_camera->Translation()._y += 1;

	}
	if (GameController::GetPointer()->IsKeyDown(DIK_E))
	{
		m_camera->Translation()._y -= 1;
	}

	cout << "X:" <<  m_camera->Translation()._x;
	cout << "	Y:"<< m_camera->Translation()._y;
	cout << "	Z:"<< m_camera->Translation()._z << endl;


//m_camera->Rotation()._y += 1;

	return true;
}

void SceneTitle::Render()
{

	
	m_camera->Render();
	m_lightmanager->Render();
	m_stage->Render(m_materialShader.get());
	title->Render(m_pixelShader.get());
	return;
}

void SceneTitle::Finalize()
{
	return;
}

void SceneTitle::InitPixelShader()
{
	ShaderDesc textureDesc;
	textureDesc._pixel._srcFile = L"Shader/texture.ps";
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

	cout << "Initialized PixelShader" << endl;
}

void SceneTitle::InitMaterialShader()
{
	ShaderDesc materialDesc;
	materialDesc._vertex._entryName = "vs_main";
	materialDesc._vertex._srcFile = L"Shader/MaterialVS.hlsl";
	materialDesc._pixel._entryName = "ps_main";
	materialDesc._pixel._srcFile = L"Shader/MaterialPS.hlsl";

	m_materialShader = std::make_shared<MaterialShader>();
	m_materialShader->Initialize(materialDesc, ShaderType::eVertex | ShaderType::ePixel);
	m_materialShader->SetLight(m_lightmanager->GetLight().get());
	m_materialShader->SetCamera(m_camera.get());

	cout << "Initialized MaterialShader" << endl;
}

void SceneTitle::InitStage()
{
	m_stage = std::make_shared<FbxModel>();
	m_stage->LoadFBX("ModelData/models/STAGEMODEL.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera.get());
	m_stage->GetTransform()._scale = Vector3(1.0f, 1.0f, -1.0f);

	m_stage->SetModelMaterialColor(Color(0.2, 0.0, 0.2, 1), eMatrerialType::eAmbient);
	m_stage->SetModelMaterialColor(Color(1, 1, 1, 1.0), eMatrerialType::eDiffuse);
	m_stage->SetModelMaterialColor(Color(1, 0, 0, 1.0), eMatrerialType::eSpecular);

	cout << "Initialized Stage" << endl;
}

void SceneTitle::InitLight()
{
	m_lightmanager = std::make_shared<LightManager>();
	m_lightmanager->Initialize();
	m_lightmanager->GetLight()->Translation() = m_camera->Translation();
	
	cout << "Initialized Light" << endl;
}

void SceneTitle::InitCamera()
{
	m_camera = std::make_shared<ViewCamera>();
	m_camera->Translation() = Vector3(-260, -350, 447);
	m_camera->Rotation() = Vector3(-160.0f, 0.0f, 1.0f);
	
	cout << "Initialized Camera" << endl;
}

void SceneTitle::InitKeyObject()
{
	m_keyObject = make_shared<FbxModel>();
}


void SceneTitle::SceneChange()
{
	if (GameController::GetPointer()->IsRightButtonTrigger())
	{
		cout << "Called NextScene!" << endl;
		ChangeScene("Game");
	}
}