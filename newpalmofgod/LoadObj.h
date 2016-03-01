#pragma once
#include"LoadScreen.h"
#include "GameController.h"
#include "ViewCamera.h"
#include "LightManager.h"
#include "LightShader.h"
#include "Light.h"
#include <iostream>
#include "PixelShader.h"
#include "SpriteBase.h"
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
	std::shared_ptr<aetherClass::SpriteBase>load02;
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::SpriteBase> feed_out;
	std::shared_ptr<aetherClass::SpriteBase> feed_in;
	std::shared_ptr<LightManager> m_lightmanager;
	bool m_pressFlag;
private:
	void SceneChange();
	void InitPixelShader();
	void InitMaterialShader();
	void InitStage();
	void InitCamera();
	void InitLight();
	void InitKeyObject();

};

