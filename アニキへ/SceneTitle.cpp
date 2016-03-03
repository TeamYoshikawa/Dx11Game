#include "SceneTitle.h"
#include <Rectangle3D.h>
#include "SceneGame.h"
#include "Rectangle2D.h"
#include "Rectangle3D.h"
using namespace aetherClass;
using namespace std;

const std::string SceneTitle::m_thisName = "Title";

SceneTitle::SceneTitle() :
GameScene(m_thisName, GetManager())
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

	m_flag = 0;

	Texture *title_tex = new Texture();/*テクスチャ―用*/
	title_tex->Load("image/Title06.png");	/*画像の読み込み*/

	Texture *press_tex = new Texture();/*press any hogehoge*/
	press_tex->Load("image/pushspacekey2.png");

	Texture *wall_tex = new Texture();
	wall_tex->Load("image/kabe2.png");


	feedin = std::make_shared<aetherClass::Rectangle2D>();
	feedin->Initialize();
	feedin->property._transform._translation._z = 0;
	feedin->property._color._alpha = 0;
	feedin->property._transform._scale._x = 1000;
	feedin->property._transform._scale._y = 1000;

	for (int i = 0; i < 5; i++)
	{
		m_wall[i] = std::make_shared<aetherClass::Cube>();
		m_wall[i]->Initialize();
		m_wall[i]->SetCamera(m_camera.get());
		m_wall[i]->SetTexture(wall_tex);
	}

	m_wall[5] = std::make_shared<aetherClass::Cube>();
	m_wall[5]->Initialize();
	m_wall[5]->SetCamera(m_camera.get());
	m_wall[5]->SetTexture(wall_tex);



	m_wall[0]->property._transform._translation = Vector3(-178.0, 100, 0);
	m_wall[0]->property._transform._scale = Vector3(1500, 300, 10);
	m_wall[0]->property._transform._rotation._y = 90;

	//窓側
	m_wall[1]->property._transform._translation = Vector3(14.0, 100, 10);
	m_wall[1]->property._transform._scale = Vector3(180, 300, 10);

	m_wall[2]->property._transform._translation = Vector3(800.0, 100, 10);
	m_wall[2]->property._transform._scale = Vector3(300, 300, 10);

	m_wall[5]->property._transform._translation = Vector3(400.0, 275, 10);
	m_wall[5]->property._transform._scale = Vector3(600, 300, 10);
	//m_wall[5]->property._transform._rotation._z = 180;

	m_wall[4]->property._transform._translation = Vector3(400.0, -200, 10);
	m_wall[4]->property._transform._scale = Vector3(600, 40, 10);

	m_wall[3]->property._transform._translation = Vector3(880.0, 100, 900);
	m_wall[3]->property._transform._scale = Vector3(1610, 300, 10);


	title = std::make_shared<aetherClass::Rectangle3D>();
	title->Initialize();
	title->SetCamera(m_camera.get());
	title->SetTexture(title_tex);
	//title->property._transform._translation = Vector3(400, 275, 20);
	//title->property._transform._scale = Vector3(100, 100, 5);
	title->property._transform._translation = m_camera->property._translation;
	title->property._transform._scale = Vector3(150, 150, 10);
	//title->property._transform._translation._y = 300;
	//title->property._transform._translation._x = 40;
	//title->property._transform._translation._z = 50;
	//title->property._transform._scale._x = 100;
	//title->property._transform._scale._y = 100;


	m_pressFlag = true;

	GameScene *Scene = new SceneGame();
	RegisterScene(Scene);

	//delete title_tex;
	//delete press_tex;
	//delete wall_tex;


	return true;
}


bool SceneTitle::TransitionIn()
{
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
	if (GameController::GetKey().IsKeyDown(DIK_D))
	{
		m_camera->property._translation._x += 1;
	}
	if (GameController::GetKey().IsKeyDown(DIK_A))
	{
		m_camera->property._translation._x -= 1;
	}
	if (GameController::GetKey().IsKeyDown(DIK_W))
	{
		m_camera->property._translation._z -= 1;
	}
	if (GameController::GetKey().IsKeyDown(DIK_S))
	{
		m_camera->property._translation._z += 1;
	}

	if (GameController::GetKey().IsKeyDown(DIK_ESCAPE)){
		return false;
	}

	if (GameController::GetKey().IsKeyDown(DIK_ESCAPE))
	{
		return false;
	}

	if (GameController::GetKey().IsKeyDown(DIK_SPACE)){
		m_flag = 1;
	}

	if (m_flag == 1){
		if (m_camera->property._rotation._y < 180){
			m_camera->property._rotation._y += 1.0;
		}
	}

	std::cout << "x:" << m_camera->property._translation._x << std::endl;
	std::cout << "y:" << m_camera->property._translation._y << std::endl;
	std::cout << "z:" << m_camera->property._translation._z << std::endl;

	//m_wall[0]->property._transform._translation = m_camera->property._translation;

	return true;
}

void SceneTitle::Render()
{
	m_camera->Render();
	m_lightmanager->Render();
	m_stage->Render(m_materialShader.get());
	title->Render(m_pixelShader.get());
	
	for (int i = 0; i < 6; i++)
	{
		m_wall[i]->Render(m_texShader.get());
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

	textureDesc._pixel._srcFile = L"Shader/texture.ps";
	m_texShader = std::make_shared<PixelShader>();
	m_texShader->Initialize(textureDesc, ShaderType::eVertex | ShaderType::ePixel);

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
	m_stage->LoadFBX("ModelData/models/Stage_ananashi2.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera.get());
	m_stage->property._transform._scale = Vector3(1.0f, 1.0f, -1.0f);

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
	m_lightmanager->GetLight()->property._translation = m_camera->property._translation;

	cout << "Initialized Light" << endl;
}

void SceneTitle::InitCamera()
{
	m_camera = std::make_shared<ViewCamera>();
	m_camera->property._translation = Vector3(220, -41, 433);
	m_camera->property._rotation = Vector3(-160.0f, 0.0f, 1.0f);

	cout << "Initialized Camera" << endl;
}

void SceneTitle::InitKeyObject()
{
	m_keyObject = make_shared<FbxModel>();
}


void SceneTitle::SceneChange()
{
	if (m_camera->property._rotation._y == 180){
		cout << "Called NextScene!" << endl;
		ChangeScene("Game", LoadState::eUse, LoadWaitState::eUse);
	}
}