#pragma once
#include <GameScene.h>
#include "GameController.h"
#include "ViewCamera.h"
#include "LightManager.h"
#include "LightShader.h"
#include "Light.h"
#include <iostream>
#include "PixelShader.h"
#include "SpriteBase.h"

#define SCORE 8
class SceneClear:
	public aetherClass::GameScene
{
	
public:

	SceneClear();
	~SceneClear();

	bool Initialize()override;
	bool Updater()override;
	void Render()override;
	void Finalize()override;
	void UIRender()override;
	


	static const std::string m_thisName;
private:
	std::shared_ptr<aetherClass::ViewCamera> m_camera;
	std::shared_ptr<aetherClass::FbxModel> m_stage;
	std::shared_ptr<LightManager> m_lightmanager;
	std::shared_ptr<aetherClass::Light>m_light;
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::MaterialShader> m_materialShader;
	std::shared_ptr<aetherClass::FbxModel> m_keyObject;
	std::shared_ptr<aetherClass::ShaderBase> m_colorShader;

	std::shared_ptr<aetherClass::SpriteBase>clear;

	std::shared_ptr<aetherClass::SpriteBase>m_rankS;
	std::shared_ptr<aetherClass::SpriteBase>m_rankA;
	std::shared_ptr<aetherClass::SpriteBase>m_rankB;
	std::shared_ptr<aetherClass::SpriteBase>m_rankC;
	std::shared_ptr<aetherClass::SpriteBase>m_rankD;


	


	//std::shared_ptr<aetherClass::ModelBase>feedin;
	std::shared_ptr<aetherClass::ViewCamera>m_uicamera;
private:
	void SceneChange();
	void InitPixelShader();
	void InitMaterialShader();
	void InitStage();
	void InitCamera();
	void InitLight();
	void InitKeyObject();
	
};
