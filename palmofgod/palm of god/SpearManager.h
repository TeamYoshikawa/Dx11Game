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
#include<Sphere.h>
#include<Physics.h>
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
	std::shared_ptr<aetherClass::ModelBase>m_spear[3];
    std::shared_ptr<aetherClass::Texture>m_spearTexture;

	std::shared_ptr<n_Spear::SpearRender>m_spearRender;
	std::shared_ptr<n_Spear::SpearUpdater>m_spearUpdater;

    std::shared_ptr<aetherClass::ModelBase>m_switch;
	std::shared_ptr<aetherClass::Texture>m_switchTexture;

	bool m_switchType;
	
	aetherClass::Vector3 rayOrigin, rayDirection;
	aetherClass::ViewCamera *m_camera;

public:
	SpearManager() = default;
	~SpearManager() = default;


	bool Initialize(aetherClass::ViewCamera*);
	void Render(std::shared_ptr<aetherClass::ShaderBase>);
	void Update();
	void Shutdown();

	int FlagGet();

	std::shared_ptr<aetherClass::ModelBase> Get();
	
};

#endif