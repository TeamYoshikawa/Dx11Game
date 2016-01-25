#pragma once
#ifndef _SPEARMANAGER_H_
#define _SPEARMANAGER_H_


//#include"Spear.h"
#include"SpearRender.h"
#include"SpearUpdater.h"
#include<memory>
#include<ViewCamera.h>
#include<GameController.h>
#include<Cube.h>
#include<Texture.h>

/*
   ‘„‚ÌŠÇ—ƒNƒ‰ƒX
   
   ŒÄ‚Ño‚µ•û
   m_spear->Initialize(m_camera.get())

   m_spear->Render(m_textureShader,DxModel::eRenderWay::eTexture)

   static bool switch = false;
   if (DxController::GameController::GetPointer()->IsLeftButtonTrigger()){
   button = !button;
   }
   m_spear->Update(switch)

*/


class SpearManager
{
private:
	std::shared_ptr<aetherClass::Cube>m_spear;
	//std::shared_ptr<Spear>m_floor;
	std::shared_ptr<aetherClass::Texture>m_spearTexture;

	std::shared_ptr<n_Spear::SpearRender>m_spearRender;
	std::shared_ptr<n_Spear::SpearUpdater>m_spearUpdater;


	
public:
	SpearManager() = default;
	~SpearManager() = default;


	bool Initialize(aetherClass::ViewCamera*);
	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update(bool);
	void Shutdown();

	
};

#endif