#ifndef _SCENEEND_H
#define _SCENEEND_H

#include <Cube.h>
#include <iostream>
#include <GameScene.h>
#include "ViewCamera.h"
#include "Texture.h"
#include "MaterialShader.h"
#include "LightManager.h"
#include "PixelShader.h"

class SceneEnd
	: public aetherClass::GameScene
{
public:
	SceneEnd();
	~SceneEnd();

	bool Initialize()override;
	bool Updater()override;
	void Render()override;
	void Finalize()override;
	bool TransitionIn()override;
	static const std::string m_thisName;

private:

	void SceneChange();

	std::shared_ptr<aetherClass::ModelBase> m_gameover;
	std::shared_ptr<aetherClass::ModelBase>feedin;
	std::shared_ptr<aetherClass::ViewCamera> m_camera;
	std::shared_ptr<aetherClass::Texture> m_texture;
	std::shared_ptr<aetherClass::PixelShader> m_shader;
	std::shared_ptr<aetherClass::MaterialShader> m_materialShader;
	std::shared_ptr<LightManager> m_lightmanager;

};

#endif