#ifndef _UIGAME_H
#define _UIGAME_H

#include "PlayerManager.h"
#include"GameController.h"

#include <Cube.h>
#include <Sphere.h>
#include <memory>
#include<iostream>


#include"PixelShader.h"
#include"ViewCamera.h"

#define ON 1
#define OFF 0
static int flag;

class UiGame
{
private:

	std::shared_ptr<aetherClass::ModelBase>goal;
	std::shared_ptr<aetherClass::ModelBase>start;
	std::shared_ptr<aetherClass::ModelBase>road;
	std::shared_ptr<aetherClass::ModelBase>location;
	
	std::shared_ptr<aetherClass::ModelBase>heart1;
	std::shared_ptr<aetherClass::ModelBase>heart2;

	std::shared_ptr<aetherClass::ViewCamera>m_uicamera;

	std::shared_ptr<PlayerManager>m_player;

	std::shared_ptr<aetherClass::PixelShader> m_shader;


public:
	UiGame() = default;
	~UiGame() = default;

	
	std::shared_ptr<aetherClass::Cube>heart;
	bool Initialize();
	void Render();
	void Update();
	void Life();
};
#endif