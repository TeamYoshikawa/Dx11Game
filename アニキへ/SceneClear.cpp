#include "SceneClear.h"
#include <Rectangle3D.h>
#include "SceneGame.h"
#include "Singleton.h"
#include "ResultData.h"
using namespace aetherClass;
using namespace std;

const std::string SceneClear::m_thisName = "Clear";

SceneClear::SceneClear():
GameScene(m_thisName, GetManager())
{
}

SceneClear::~SceneClear()
{

}
bool SceneClear::Initialize()
{

	std::cout << Singleton<ResultData>::GetInstance().LifePointGet() << std::endl;
	std::cout << Singleton<ResultData>::GetInstance().SoumatouCountGet() << std::endl;


	cout << "Init SceneClear" << endl;
	InitCamera();
	InitLight();
	InitPixelShader();
	InitMaterialShader();
	InitStage();

	clear = std::make_shared<aetherClass::Rectangle2D>();
	clear->Initialize();

	Texture *clear_tex = new Texture();/*テクスチャ―用*/
	clear_tex->Load("image/clear2.png");	/*画像の読み込み*/
	clear->SetTexture(clear_tex);
	clear->property._transform._scale._x = 800;
	clear->property._transform._scale._y = 600;

	m_rankS = std::make_shared<aetherClass::Rectangle2D>();
	m_rankS->Initialize();

	m_rankA = std::make_shared<aetherClass::Rectangle2D>();
	m_rankA->Initialize();

	m_rankB = std::make_shared<aetherClass::Rectangle2D>();
	m_rankB->Initialize();

	m_rankB = std::make_shared<aetherClass::Rectangle2D>();
	m_rankB->Initialize();

	m_rankC = std::make_shared<aetherClass::Rectangle2D>();
	m_rankC->Initialize();

	m_rankD = std::make_shared<aetherClass::Rectangle2D>();
	m_rankD->Initialize();

	Texture *rankS_tex = new Texture();/*テクスチャ―用*/
	rankS_tex->Load("image/clear_S.png");	/*画像の読み込み*/
	m_rankS->SetTexture(rankS_tex);
	m_rankS->property._transform._scale._x = 147;
	m_rankS->property._transform._scale._y = 216;
	m_rankS->property._transform._translation._x = 225;
	m_rankS->property._transform._translation._y = 200;
	Texture *rankA_tex = new Texture();/*テクスチャ―用*/
	rankA_tex->Load("image/clear_A.png");	/*画像の読み込み*/
	m_rankA->SetTexture(rankA_tex);
	m_rankA->property._transform._scale._x = 147;
	m_rankA->property._transform._scale._y = 216;
	m_rankA->property._transform._translation._x = 225;
	m_rankA->property._transform._translation._y = 200;
	Texture *rankB_tex = new Texture();/*テクスチャ―用*/
	rankB_tex->Load("image/clear_B.png");	/*画像の読み込み*/
	m_rankB->SetTexture(rankB_tex);
	m_rankB->property._transform._scale._x = 147;
	m_rankB->property._transform._scale._y = 216;
	m_rankB->property._transform._translation._x = 225;
	m_rankB->property._transform._translation._y = 200;
	
	Texture *rankC_tex = new Texture();/*テクスチャ―用*/
	rankC_tex->Load("image/clear_C.png");	/*画像の読み込み*/
	m_rankC->SetTexture(rankB_tex);
	m_rankC->property._transform._scale._x = 147;
	m_rankC->property._transform._scale._y = 216;
	m_rankC->property._transform._translation._x = 225;
	m_rankC->property._transform._translation._y = 200;

	Texture *rankD_tex = new Texture();/*テクスチャ―用*/
	rankD_tex->Load("image/clear_D.png");	/*画像の読み込み*/
	m_rankD->SetTexture(rankC_tex);
	m_rankD->property._transform._scale._x = 147;
	m_rankD->property._transform._scale._y = 216;
	m_rankD->property._transform._translation._x = 225;
	m_rankD->property._transform._translation._y = 200;

	GameScene *Scene = new SceneGame();
	RegisterScene(Scene);
	/*
	clear->GetTransform()._scale = Vector3(0.8f, 0.8f, 0.0f);
	clear->GetTransform()._translation = Vector3(20.0f, -8.2f, 45.0f) + m_uicamera->Translation();
	clear->GetTransform()._rotation = Vector3(0.0f, 0.0f, 0.0f);
	*/
	return true;
}

bool SceneClear::Updater()
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

void SceneClear::Render()
{
	m_camera->Render();
	m_lightmanager->Render();
	
	


	if ((SCORE + Singleton<ResultData>::GetInstance().LifePointGet())- Singleton<ResultData>::GetInstance().SoumatouCountGet() >= 8){ //S
		m_rankS->Render(m_pixelShader.get());
	}

	if ((SCORE + Singleton<ResultData>::GetInstance().LifePointGet()) - Singleton<ResultData>::GetInstance().SoumatouCountGet() >= 6){ //A
		m_rankA->Render(m_pixelShader.get());
	}

	if ((SCORE + Singleton<ResultData>::GetInstance().LifePointGet()) - Singleton<ResultData>::GetInstance().SoumatouCountGet() >= 5){ //B
		m_rankB->Render(m_pixelShader.get());
	}

	if ((SCORE + Singleton<ResultData>::GetInstance().LifePointGet()) - Singleton<ResultData>::GetInstance().SoumatouCountGet() >= 3){ //C
		m_rankC->Render(m_pixelShader.get());
	}
	if ((SCORE + Singleton<ResultData>::GetInstance().LifePointGet()) - Singleton<ResultData>::GetInstance().SoumatouCountGet() <= 2){ //D
		m_rankD->Render(m_pixelShader.get());
	}
	clear->Render(m_pixelShader.get());
	return;
}

void SceneClear::Finalize()
{
	return;
}

void SceneClear::InitPixelShader()
{
	ShaderDesc textureDesc;
	textureDesc._pixel._srcFile = L"Shader/Transparent.ps";
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

void SceneClear::InitMaterialShader()
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

void SceneClear::InitStage()
{
	m_stage = std::make_shared<FbxModel>();
	m_stage->LoadFBX("ModelData/models/STAGEMODEL.fbx", eAxisSystem::eAxisOpenGL);
	m_stage->SetCamera(m_camera.get());
	//m_stage->GetTransform()._scale = Vector3(1.0f, 1.0f, -1.0f);

	m_stage->SetModelMaterialColor(Color(0.0, 0.1, 0.1, 1), eMatrerialType::eAmbient);
	m_stage->SetModelMaterialColor(Color(0.7, 0.6, 0.6, 0.0), eMatrerialType::eDiffuse);
	m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 1.0), eMatrerialType::eSpecular);
	//m_stage->SetModelMaterialColor(Color(1.0, 1.0, 1.0, 0.0), eMatrerialType::eEmissive);

	cout << "Initialized Stage" << endl;
}

void SceneClear::InitLight()
{
	m_lightmanager = std::make_shared<LightManager>();
	m_lightmanager->Initialize();
	m_lightmanager->GetLight()->property._translation = m_camera->property._translation;

	cout << "Initialized Light" << endl;
}

void SceneClear::InitCamera()
{
	m_camera = std::make_shared<ViewCamera>();
	//m_camera->Translation() = Vector3(-260, -350, 447);
	//m_camera->Rotation() = Vector3(-160.0f, 0.0f, 1.0f);

	cout << "Initialized Camera" << endl;
}

void SceneClear::InitKeyObject()
{
	m_keyObject = make_shared<FbxModel>();
}


void SceneClear::SceneChange()
{
	if (GameController::GetMouse().IsLeftButtonTrigger())
	{
		cout << "Called NextScene!" << endl;
		ChangeScene("Game", LoadState::eUnuse, LoadWaitState::eUnuse);

	}

}