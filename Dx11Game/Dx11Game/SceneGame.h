#ifndef _SCENEGAME_H
#define _SCENEGAME_H
#include <Cube.h>
#include <FbxStaticMesh.h>
#include <ColorShader.h>
#include <Cube.h>
#include "SceneBase.h"
#include "PlayerManager.h"
#include "CameraMAnager.h"
#include"LightShader.h"
#include"Light.h"


class SceneGame :
	public SceneBase
{
	public:
		SceneGame(SceneManager*);
		~SceneGame();

		void Initialize(Dx11::Direct3DManager*, HWND)override;
		void Updata()override;
		void Render()override;
		void Shutdown()override;

	public:
		static const std::string m_thisName;
		std::shared_ptr<PlayerManager> m_player;
		std::shared_ptr<CameraManager> m_camera;
		std::shared_ptr<DxShader::ShaderBase> m_shader;
		std::shared_ptr<DxShader::LightShader> m_lightshader;

		std::shared_ptr<DxLight::Light>m_light;
		std::shared_ptr<DxModel::FbxStaticMesh> m_stage;
};

#endif