#include"SpearManager.h"
#include"PlayerManager.h"
#include<iostream>
#include<PixelShader.h>

using namespace aetherClass;
using namespace n_Spear;



bool SpearManager::Initialize(ViewCamera *camera)
{
	m_camera = camera;

	
	m_spearTexture = std::make_shared<Texture>();
	m_spearTexture->Load("ModelData/Textures/tex.png");
	for (int i = 0; i < 4; i++){
		
		m_spear[i] = std::make_shared<FbxModel>();
		
		m_spear[i]->SetCamera(camera);
		m_spear[i]->LoadFBX("ModelData/models/Lanca_model_m.fbx", eAxisSystem::eAxisOpenGL);
		
		m_spear[i]->property._transform._scale = Vector3(25.3f, 5.3f, 30.0f);
		m_spear[i]->property._transform._rotation = Vector3(180.0f, 0.0f, 0.0f);

		m_collideTexture[i] = std::make_shared<Texture>();
		m_collideTexture[i]->Load("ModelData/textures/Chips_Cover.jpg");
		m_collideBox[i] = std::make_shared<Cube>();
		m_collideBox[i]->Initialize();
		m_collideBox[i]->SetTexture(m_collideTexture[i].get());
		m_collideBox[i]->SetCamera(m_camera);
		const Vector3 translation = m_spear[i]->property._transform._translation;
		m_collideBox[i]->property._transform._translation = translation;
		m_collideBox[i]->property._transform._scale = Vector3(10.0f, 350.0f, 20.0f);

		ShaderDesc desc[4];
		desc[i]._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
		desc[i]._vertex._entryName = "vs_main";
		desc[i]._pixel._srcFile = L"Shader/ColorTextureAdd2.ps";
		desc[i]._pixel._entryName = "ps_main";


		m_collideBoxShader[i] = std::make_shared <aetherClass::PixelShader>();
		m_collideBoxShader[i]->Initialize(desc[i], ShaderType::eVertex | ShaderType::ePixel);
	}

	m_spear[0]->property._transform._translation = Vector3(2500.0f, 640.0f, 850.0f);
	m_spear[1]->property._transform._translation = Vector3(2500.0f, 640.0f, 700.0f);
	m_spear[2]->property._transform._translation = Vector3(2500.0f, 640.0f, 550.0f);
	m_spear[3]->property._transform._translation = Vector3(2500.0f, 640.0f, 420.0f);
	

	for (int i = 0; i < 4; i++){

		m_spear2[i] = std::make_shared<FbxModel>();

		m_spear2[i]->SetCamera(camera);
		m_spear2[i]->LoadFBX("ModelData/models/Lanca_model_m.fbx", eAxisSystem::eAxisOpenGL);

		m_spear2[i]->property._transform._scale = Vector3(25.3f, 5.3f, 30.0f);
		m_spear2[i]->property._transform._rotation = Vector3(-92.0f, 0.0f, 0.0f);

		m_collideTexture2[i] = std::make_shared<Texture>();
		m_collideTexture2[i]->Load("ModelData/textures/Chips_Cover.jpg");
		m_collideBox2[i] = std::make_shared<Cube>();
		m_collideBox2[i]->Initialize();
		m_collideBox2[i]->SetTexture(m_collideTexture2[i].get());
		m_collideBox2[i]->SetCamera(m_camera);
		const Vector3 translation = m_spear2[i]->property._transform._translation;
		m_collideBox2[i]->property._transform._translation = translation;
		m_collideBox2[i]->property._transform._scale = Vector3(10.0f, 350.0f, 20.0f);

		ShaderDesc desc[4];
		desc[i]._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
		desc[i]._vertex._entryName = "vs_main";
		desc[i]._pixel._srcFile = L"Shader/ColorTextureAdd2.ps";
		desc[i]._pixel._entryName = "ps_main";


		m_collideBoxShader2[i] = std::make_shared <aetherClass::PixelShader>();
		m_collideBoxShader2[i]->Initialize(desc[i], ShaderType::eVertex | ShaderType::ePixel);
	}

	m_spear2[0]->property._transform._translation = Vector3(6500.0f, 80.0f, 1500.0f);
	m_spear2[1]->property._transform._translation = Vector3(7000.0f, 80.0f, 1500.0f);
	m_spear2[2]->property._transform._translation = Vector3(7250.0f, 80.0f, 1500.0f);
	m_spear2[3]->property._transform._translation = Vector3(6750.0f, 80.0f, 1500.0f);
	

	m_spearRender = std::make_shared<SpearRender>();

	m_spearUpdater = std::make_shared<SpearUpdater>();
	m_spearUpdaterScond = std::make_shared<SpearUpdaterScond>();
	
	m_switchTexture = std::make_shared<Texture>();
	m_switchTexture->Load("ModelData/Textures/button.jpg");
	m_switch = std::make_shared<Cube>();
	m_switch->Initialize();
	if (!m_switch->Initialize()){
		return false;
	}
	m_switch->SetCamera(camera);
	m_switch->SetTexture(m_switchTexture.get());
	m_switch->property._transform._translation = Vector3(1150.0f, 140.0f, 620.0f);
	m_switch->property._transform._scale = Vector3(100.0f, 20.0f, 220.0f);

	m_switch2 = std::make_shared<Cube>();
	m_switch2->Initialize();
	if (!m_switch2->Initialize()){
		return false;
	}
	m_switch2->SetCamera(camera);
	m_switch2->SetTexture(m_switchTexture.get());
	m_switch2->property._transform._translation = Vector3(5800.0f, 140.0f, 620.0f);
	m_switch2->property._transform._scale = Vector3(100.0f, 20.0f, 220.0f);

	m_spearEvent = eSpearEvent::eChecking;
	return true;
}

void SpearManager::Render(const std::shared_ptr<aetherClass::ShaderBase>shader)
{	

	for (int i = 0; i < 4; i++){
		m_spearRender->Renderring(m_spear[i], shader);
		//m_collideBox[i]->Render(m_collideBoxShader[i].get());
	}
	
	for (int i = 0; i < 4; i++){
		m_spearRender->Renderring(m_spear2[i], shader);
		//m_collideBox2[i]->Render(m_collideBoxShader2[i].get());
	}

	//m_spearRender->Renderring(m_switch.get(), shader);
	//m_switch->Render(shader.get());
	//m_switch2->Render(shader.get());

}

void SpearManager::Update()
{	
	spear_flag = m_spearUpdater->FlagGet();

	if (m_spearEvent == eSpearEvent::eChecking){
	
			m_spearEvent = eSpearEvent::eStart;
			m_spearUpdater->FlagOn();
			m_spearUpdaterScond->FlagOn();
	}
	else{
			for (int i = 0; i < 4; i++){
				m_spearUpdater->Updating(m_spear[i]);
			}
	}
	UpdateColliderBox();
}


void SpearManager::Update2()
{
	spear_flag = m_spearUpdater->FlagGet();

	if (m_spearEvent == eSpearEvent::eChecking){

		m_spearEvent = eSpearEvent::eStart;
		m_spearUpdaterScond->FlagOn();
	}
	else{
		for (int i = 0; i < 4; i++){
			m_spearUpdaterScond->Updating(m_spear2[i]);
		}

	}
	UpdateColliderBox();
}

void SpearManager::UpdateColliderBox()
{
	for (int i = 0; i < 4; i++){
		const Vector3 translation = m_spear[i]->property._transform._translation;
		m_collideBox[i]->property._transform._translation = translation;
		const Vector3 rotation = m_spear[i]->property._transform._rotation;
		m_collideBox[i]->property._transform._rotation = rotation;
	}

	for (int i = 0; i < 4; i++){
		const Vector3 translation = m_spear2[i]->property._transform._translation;
		m_collideBox2[i]->property._transform._translation = translation;
		const Vector3 rotation = m_spear2[i]->property._transform._rotation;
		m_collideBox2[i]->property._transform._rotation = rotation;
	}
}

void SpearManager::Shutdown()
{
	for (int i = 0; i < 10; i++){
		m_spear[i].get()->Finalize();
	}
	for (int i = 0; i < 6; i++){
		m_spear2[i].get()->Finalize();
	}
	m_switch.get()->Finalize();
	m_switch2.get()->Finalize();
}

std::shared_ptr<ModelBase>SpearManager::Get(int i)
{
	return m_collideBox[i];
}

std::shared_ptr<ModelBase>SpearManager::Get2(int i)
{
	return m_collideBox2[i];
}

std::shared_ptr<aetherClass::ModelBase> SpearManager::Switch_Get(){

	return m_switch;
}

std::shared_ptr<aetherClass::ModelBase> SpearManager::Switch_Get2(){

	return m_switch2;
}

bool SpearManager::HitMesh(std::shared_ptr<ModelBase>& player, std::shared_ptr<ModelBase>& other){

	if (!m_spearUpdater->HittingProcessor(player, other))
	{
		return false;
	}

	return true;
}

bool SpearManager::HitMesh2(std::shared_ptr<ModelBase>& player, std::shared_ptr<ModelBase>& other){

	if (!m_spearUpdater->HittingProcessor(player, other))
	{
		return false;
	}

	return true;
}

int SpearManager::SpearCnt()
{
	return spear_max;
}

int SpearManager::SpearCnt2()
{
	return spear2_max;
}

int SpearManager::FlagGet()
{
	return m_spearUpdater->FlagGet();
}