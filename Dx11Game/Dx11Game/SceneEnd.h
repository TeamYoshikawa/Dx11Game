#ifndef _SCENEEND_H
#define _SCENEEND_H

#include "SceneBase.h"
#include "SceneGame.h"
#include <Windows.h>
#include <Cube.h>
class SceneEnd:
	public SceneBase
{
	public:
		SceneEnd(SceneManager* manager);
		~SceneEnd();

		void Initialize(Dx11::Direct3DManager*, HWND)override;
		void Updata()override;
		void Render()override;
		void Shutdown()override;

		void Paint();
	
		static const std::string m_thisName;

	private:
		
		DxCamera::ViewCamera m_camera;
		DxModel::Cube cube;
		std::shared_ptr<DxShader::TextureShader>texshader;;
};
#endif
