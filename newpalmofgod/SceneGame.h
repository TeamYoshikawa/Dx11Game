#ifndef _SCENEGAME_H
#define _SCENEGAME_H
#include <Cube.h>
#include <FbxModel.h>
#include <Color.h>
#include <Cube.h>
#include <GameScene.h>
#include "PlayerManager.h"
#include "NavigationManager.h"
#include "FallingWallManager.h"
#include "SoumatouManager.h"
#include "Skybox.h"
#include "SceneEnd.h"
#include "TextManager.h"
#include "WallManager.h"
#include "LightManager.h"
#include "SpearManager.h"
#include "PitFallManager.h"
#include "RockManager.h"
#include "LightShader.h"
#include "Light.h"
#include "UiGame.h"
#include "GameSound.h"


class SceneGame :
	public aetherClass::GameScene
{
public:
	SceneGame();
	~SceneGame();

	bool Initialize()override;
	bool Updater()override;
	void Render()override;
	void Finalize()override;
	static const std::string m_thisName;

private:
	//�g���b�v�C�x���g
	enum class eTrapState{
		eRockEvent,
		eSpearEvent,
		efallwall,
		ePitFall,
		eNull
	};
	//�i�r�C�x���g
	enum class eNaviState{
		eNaviEvent,
		eNull
	};

private:
	//�C�x���g
	eTrapState m_trapState;
	eNaviState m_naviState;

	
	std::shared_ptr<aetherClass::Skybox> m_skybox;

	std::shared_ptr<aetherClass::Texture> m_texture;

	//���C�g
	std::shared_ptr<LightManager> m_lightmanager;
	std::shared_ptr<aetherClass::Light>m_light;

	//���n��
	std::shared_ptr<SoumatouManager> m_soumatou;


	//��
	std::shared_ptr<WallManager> m_wall;
	//�X�e�[�W
	std::shared_ptr<aetherClass::FbxModel> m_stage;

	//�v���C���[
	std::shared_ptr<PlayerManager> m_player;

	//�g���b�v
	std::shared_ptr<PitFallManager> m_pitfall;
	std::shared_ptr<SpearManager> m_spear;
	std::shared_ptr<RockManager> m_rock;
	std::shared_ptr<FallingWallManager> m_fallwall;

	//UI
	std::shared_ptr<TextManager> m_text;
	std::shared_ptr<NavigationManager> m_navigation;
	std::shared_ptr<UiGame> m_ui;

	//�V�F�[�_�[
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::ShaderBase> m_shader;
	std::shared_ptr<aetherClass::MaterialShader> m_materialShader;

	//�T�E���h
	std::shared_ptr<aetherClass::GameSound> m_sound;
	std::shared_ptr<aetherClass::ViewCamera> m_camera;

};

#endif