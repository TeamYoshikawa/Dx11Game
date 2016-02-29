#include "SceneTitle.h"
#include <Rectangle.h>
#include "SceneGame.h"
#include "Rectangle2D.h"
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


	feedin = std::make_shared<aetherClass::Rectangle2D>();
	feedin->Initialize();
	feedin->property._transform._translation._z = 0;
	feedin->property._color._alpha = 0;
	feedin->property._transform._scale._x = 1000;
	feedin->property._transform._scale._y = 1000;
	
	Texture *title_tex = new Texture();/*テクスチャ―用*/
	title_tex->Load("image/TitleTest.png");	/*画像の読み込み*/

	Texture *press_tex = new Texture();/*press any hogehoge*/
	press_tex->Load("image/Title02.png");

	title = std::make_shared<aetherClass::Rectangle2D>();
	title->Initialize();
	title->SetTexture(title_tex);
	title->property._transform._translation._y= 35;
	title->property._transform._translation._x = 25;
	title->property._transform._translation._z = 0.1;

	title->property._transform._scale._x= 750;
	title->property._transform._scale._y= 250;
	

	press = std::make_shared<aetherClass::Rectangle2D>();
	press->Initialize();
	press->SetTexture(press_tex);
	press->property._transform._translation._y = 350;
	press->property._transform._translation._x = 250;
	press->property._transform._translation._z = 0.1;

	press->property._transform._scale._x = 300;
	press->property._transform._scale._y = 200;
	press->property._color._alpha = 1;


	m_pressFlag = true;

	GameScene *Scene = new SceneGame();
	RegisterScene(Scene);


	/*
	title->GetTransform()._scale = Vector3(0.8f, 0.8f, 0.0f);
	title->GetTransform()._translation = Vector3(20.0f, -8.2f, 45.0f) + m_uicamera->Translation();
	title->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);
	*/
	return true;
}


bool SceneTitle::TransitionIn()
{
	m_camera->Render();
	
	feedin->property._color._alpha += 0.007;
	feedin->Render(m_colorShader.get());
	if (feedin->property._color._alpha < 0){
		return kTransitionning;
	}
	else if (feedin->property._color._alpha > 1){
		
		return kTransitionEnd;

	
	}

	return kTransitionning;
}


bool SceneTitle::Updater()
{
	SceneChange();
	if (GameController::GetKey().IsKeyDown(DIK_ESCAPE)){
		return false;
	}

	if (GameController::GetKey().IsKeyDown(DIK_ESCAPE))
	{
		return false;
	}

	
	
		
	return true;
}

void SceneTitle::Render()
{
	m_camera->Render();
	m_lightmanager->Render();
	m_stage->Render(m_materialShader.get());
	title->Render(m_pixelShader.get());
	
	press->Render(m_pixelShader.get());



	if (press->property._color._alpha == 1.0){
		m_pressFlag = true;
	}
	else if (press->property._color._alpha < 0){
		m_pressFlag = false;
	}
	
	if (m_pressFlag){
		press->property._color._alpha -= 0.01;
		
	}
	else{
		press->property._color._alpha += 0.01;
	
	}

	return;
}

void SceneTitle::Finalize()
{
	return;
}

void SceneTitle::InitPixelShader()
{
	ShaderDesc textureDesc;
	textureDesc._pixel._srcFile = L"Shader/Transparent.ps";
	textureDesc._pixel._entryName = "ps_main";

	textureDesc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	textureDesc._vertex._entryName = "vs_main";
	
	m_pixelShader = std::make_shared<PixelShader>();
	m_pixelShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

	textureDesc._pixel._srcFile = L"Shader/BasicColor.ps";
	m_colorShader = std::make_shared<PixelShader>();
	m_colorShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

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

	m_stage->SetModelMaterialColor(Color(0.0, 0.1, 0.1, 1), eMatrerialType::eAmbient);
	m_stage->SetModelMaterialColor(Color(0.7, 0.6, 0.6, 0.0), eMatrerialType::eDiffuse);
	m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 1.0), eMatrerialType::eSpecular);
	//m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 0.0), eMatrerialType::eEmissive);

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
	if (GameController::GetMouse().IsLeftButtonTrigger())
	{
		cout << "Called NextScene!" << endl;
		ChangeScene("Game",true);
		
	}
	
}