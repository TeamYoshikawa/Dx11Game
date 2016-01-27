#pragma once

#include <iostream>

#include <GameScene.h>
#include <FbxModel.h>
#include <Cube.h>
#include "ViewCamera.h"
#include "LightManager.h"
#include "LightShader.h"
#include "Light.h"

#include "PixelShader.h"

#include "GameController.h"

class SceneTitle :
	public aetherClass::GameScene	
{
public:
	SceneTitle();
	~SceneTitle();

	bool Initialize()override;
	bool Updater()override;
	void Render()override;
	void Finalize()override;

	static const std::string m_thisName;

private:
	std::shared_ptr<aetherClass::ViewCamera> m_camera;
	std::shared_ptr<aetherClass::FbxModel> m_stage;
	std::shared_ptr<LightManager> m_lightmanager;
	std::shared_ptr<aetherClass::Light>m_light;
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::MaterialShader> m_materialShader;
	std::shared_ptr<aetherClass::FbxModel> m_keyObject;


	std::shared_ptr<aetherClass::ModelBase>title;
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