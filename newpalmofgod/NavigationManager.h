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

#define navi_max 5

class NavigationManager
{
public:
	NavigationManager() =default;
	~NavigationManager() =default;;

	bool Initialize(aetherClass::ViewCamera* camera);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update(int);
	void Finalize();

	int Navi_IDGet();

	std::shared_ptr<aetherClass::ModelBase> Navi_Get(int);


	int NaviCnt();

	bool HitMesh(std::shared_ptr<aetherClass::ModelBase>&, std::shared_ptr<aetherClass::ModelBase>&);

private:
	
	std::shared_ptr<aetherClass::Texture> m_navigationTexture;

	std::shared_ptr<NavigationUpdater> m_updater;
	std::shared_ptr<NavigationRender> m_render;

	struct NaviObject{
		std::shared_ptr<aetherClass::ModelBase> m_navigation;
		bool m_isRunEnd;
		int naviid;
	};

	NaviObject m_naviObj[5];
	int m_nowNaviID;

};


