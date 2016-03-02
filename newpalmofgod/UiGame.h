#ifndef _UIGAME_H
#define _UIGAME_H

#include "PlayerManager.h"
#include"GameController.h"

#include <Cube.h>
#include <Sphere.h>
#include <SpriteBase.h>
#include <memory>
#include<iostream>


#include"PixelShader.h"
#include"ViewCamera.h"

#define ON 1
#define OFF 0


class UiGame
{
private:

	int i=0;

	int u_flag;

	std::shared_ptr<aetherClass::SpriteBase>h_ui;
	std::shared_ptr<aetherClass::SpriteBase>heart[3];

	std::shared_ptr<PlayerManager>m_player;

	std::shared_ptr<aetherClass::ShaderBase> m_shader;


public:
	UiGame() = default;
	~UiGame() = default;

	int h_max;
	int h_player;

	bool Initialize();
	void Render();
	void Update();
	void Life();
	int Set(int h_player);


};
#endif