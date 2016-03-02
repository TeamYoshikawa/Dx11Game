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
	//トラップイベント
	enum class eTrapState{
		eRockEvent,
		eSpearEvent,
		efallwall,
		ePitFall,
		eNull
	};
	//ナビイベント
	enum class eNaviState{
		eNaviEvent,
		eNull
	};

private:
	//イベント
	eTrapState m_trapState;
	eNaviState m_naviState;

	
	std::shared_ptr<aetherClass::Skybox> m_skybox;

	std::shared_ptr<aetherClass::Texture> m_texture;

	//ライト
	std::shared_ptr<LightManager> m_lightmanager;
	std::shared_ptr<aetherClass::Light>m_light;

	//走馬灯
	std::shared_ptr<SoumatouManager> m_soumatou;


	//壁
	std::shared_ptr<WallManager> m_wall;
	//ステージ
	std::shared_ptr<aetherClass::FbxModel> m_stage;

	//プレイヤー
	std::shared_ptr<PlayerManager> m_player;

	//トラップ
	std::shared_ptr<PitFallManager> m_pitfall;
	std::shared_ptr<SpearManager> m_spear;
	std::shared_ptr<RockManager> m_rock;
	std::shared_ptr<FallingWallManager> m_fallwall;

	//UI
	std::shared_ptr<TextManager> m_text;
	std::shared_ptr<NavigationManager> m_navigation;
	std::shared_ptr<UiGame> m_ui;

	//シェーダー
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::ShaderBase> m_shader;
	std::shared_ptr<aetherClass::MaterialShader> m_materialShader;

	//サウンド
	std::shared_ptr<aetherClass::GameSound> m_sound;
	std::shared_ptr<aetherClass::ViewCamera> m_camera;

};

#endif