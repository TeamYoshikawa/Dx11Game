#pragma once

#include"NavigationUpdater.h"
#include"NavigationRender.h"
#include <Cube.h>
#include <memory>
#include <iostream>
#include <ViewCamera.h>
#include "PixelShader.h"
#include "GameController.h"

#include "Text.h"
#include "Font.h"
#include "Physics.h"

#define navi_max 10

class NavigationManager
{
public:
	NavigationManager() =default;
	~NavigationManager() =default;;

	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update();
	void Finalize();

private:

	std::shared_ptr<aetherClass::ModelBase> m_navigation[10];
	std::shared_ptr<aetherClass::Texture> m_navigationTexture;

	std::shared_ptr<NavigationUpdater> m_updater;
	std::shared_ptr<NavigationRender> m_render;


	aetherClass::Text *m_text;
	aetherClass::Font *m_font;
	aetherClass::ShaderBase  *m_color;

	int m_score;

};


