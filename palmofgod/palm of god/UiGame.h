#ifndef _GAMEUI_H
#define _GAMEUI_H

#include"UiRender.h"
#include"GameController.h"

#include <Cube.h>
#include <memory>
#include<iostream>


#include"PixelShader.h"
#include"ViewCamera.h"
#include"UiCamera.h"


#define ON 1
#define OFF 0
static int flag;

class UiGame
{
private:

	std::shared_ptr<aetherClass::Cube>goal;
	std::shared_ptr<aetherClass::Cube>start;
	std::shared_ptr<aetherClass::Cube>road;
	std::shared_ptr<aetherClass::Cube>location;
	std::shared_ptr<aetherClass::Cube>heart;
	std::shared_ptr<aetherClass::Cube>heart1;
	std::shared_ptr<aetherClass::Cube>heart2;

	std::shared_ptr<aetherClass::ViewCamera>m_uicamera;

	std::shared_ptr<aetherClass::PixelShader> m_shader;

	std::shared_ptr<UiRender>m_render;



public:
	UiGame() = default;
	~UiGame() = default;

	bool Initialize();
	void Render();
	void Update();
	void Shutdown();
	void Paint();
};
#endif