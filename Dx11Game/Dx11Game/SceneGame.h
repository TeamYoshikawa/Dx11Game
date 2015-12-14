#ifndef _SCENEGAME_H
#define _SCENEGAME_H
#include <Cube.h>
#include <FbxStaticMesh.h>
#include <ColorShader.h>

#include "SceneBase.h"
#include "PlayerManager.h"

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
		std::shared_ptr<DxCamera::ViewCamera> m_camera;
		std::shared_ptr<DxShader::ShaderBase> m_shader;
};

#endif