#ifndef _SCENEGAME_H
#define _SCENEGAME_H
#include <Cube.h>
#include <FbxModel.h>
#include <Color.h>
#include <Cube.h>
#include <GameScene.h>
#include "PlayerManager.h"
#include "WallManager.h"
#include "CameraMAnager.h"
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
	enum class eGameState{
		eRockEvent,
		eRockEvent2,
		eSpearEvent,
		ePitFall,
		eNull
	};
private:

	void FirstSpearEvent();
	void FirstPitFallEvent();
	eGameState GetGameState();

private:

	eGameState m_gameState;

	std::shared_ptr<PlayerManager> m_player;
	std::shared_ptr<CameraManager> m_camera;
	std::shared_ptr<LightManager> m_lightmanager;
	std::shared_ptr<PitFallManager> m_pitfall;

	std::shared_ptr<SpearManager> m_spear;
	std::shared_ptr<RockManager> m_rock;

	std::shared_ptr<WallManager> m_wall;

	std::shared_ptr<UiGame> m_ui;

	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;

	std::shared_ptr<aetherClass::ShaderBase> m_shader;

	std::shared_ptr<aetherClass::GameSound> m_sound;

	std::shared_ptr<aetherClass::MaterialShader> m_materialShader;

	std::shared_ptr<aetherClass::Light>m_light;
	std::shared_ptr<aetherClass::FbxModel> m_stage;

	std::shared_ptr<aetherClass::ModelBase> m_positionCheck;
	std::shared_ptr<aetherClass::Texture> m_positionCheckBoxTexture;
};

#endif