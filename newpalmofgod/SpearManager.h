#pragma once
#ifndef _SPEARMANAGER_H_
#define _SPEARMANAGER_H_


//#include"Spear.h"
#include"SpearRender.h"
#include"SpearUpdater.h"
#include"SpearUpdaterScond.h"
#include"PlayerManager.h"
#include<memory>
#include<ViewCamera.h>
#include<GameController.h>
#include<Cube.h>
#include<Sphere.h>
#include<Texture.h>
#include<Physics.h>
#include<FbxModel.h>

#define spear_max 4
#define spear2_max 4

class SpearManager
{
private:
	enum class eSpearEvent{
		eChecking,
		eStart
	};
private:
	void UpdateColliderBox();
private:
	std::shared_ptr<aetherClass::FbxModel>m_spear[4];
	std::shared_ptr<aetherClass::FbxModel>m_spear2[4];

    std::shared_ptr<aetherClass::Texture>m_spearTexture;

	std::shared_ptr<n_Spear::SpearRender>m_spearRender;
	std::shared_ptr<n_Spear::SpearUpdater>m_spearUpdater;
	std::shared_ptr<n_Spear::SpearUpdaterScond>m_spearUpdaterScond;

    std::shared_ptr<aetherClass::ModelBase>m_switch;
	std::shared_ptr<aetherClass::ModelBase>m_switch2;
	std::shared_ptr<aetherClass::Texture>m_switchTexture;

	std::shared_ptr<aetherClass::Texture> m_collideTexture[4];
	std::shared_ptr<aetherClass::ModelBase> m_collideBox[4];
	std::shared_ptr<aetherClass::ShaderBase> m_collideBoxShader[4];

	std::shared_ptr<aetherClass::Texture> m_collideTexture2[4];
	std::shared_ptr<aetherClass::ModelBase> m_collideBox2[4];
	std::shared_ptr<aetherClass::ShaderBase> m_collideBoxShader2[4];
	
	aetherClass::Vector3 rayOrigin, rayDirection;
	aetherClass::ViewCamera *m_camera;

	eSpearEvent m_spearEvent;

public:
	SpearManager() = default;
	~SpearManager() = default;


	bool Initialize(aetherClass::ViewCamera*);
	void Render(std::shared_ptr<aetherClass::ShaderBase>);
	void Update();
	void Update2();
	void Shutdown();

	int FlagGet();

	bool HitMesh(std::shared_ptr<aetherClass::ModelBase>&, std::shared_ptr<aetherClass::ModelBase>&);
	bool HitMesh2(std::shared_ptr<aetherClass::ModelBase>&, std::shared_ptr<aetherClass::ModelBase>&);

	std::shared_ptr<aetherClass::ModelBase> Switch_Get();
	std::shared_ptr<aetherClass::ModelBase> Switch_Get2();

	std::shared_ptr<aetherClass::ModelBase> Get(int i);
	std::shared_ptr<aetherClass::ModelBase> Get2(int i);
	
	int SpearCnt();
	int SpearCnt2();
};

#endif