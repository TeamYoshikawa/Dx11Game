#pragma once
#include"LoadScreen.h"
#include "GameController.h"
#include "ViewCamera.h"
#include "LightManager.h"
#include "LightShader.h"
#include "Light.h"
#include <iostream>
#include "PixelShader.h"
class LoadObj:public aetherClass::LoadScreen
{
	
public:

	LoadObj();
	~LoadObj();
	void Initialize()override;
	void Finalize()override;
	void Run()override;
	bool WaitRun()override;
private:
	std::shared_ptr<aetherClass::ViewCamera> m_camera;
	std::shared_ptr<aetherClass::ModelBase>load;
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<LightManager> m_lightmanager;
private:
	void SceneChange();
	void InitPixelShader();
	void InitMaterialShader();
	void InitStage();
	void InitCamera();
	void InitLight();
	void InitKeyObject();

};

