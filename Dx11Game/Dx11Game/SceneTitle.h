#ifndef _SCENETITLE_H
#define _SCENETITLE_H
#include "SceneBase.h"
#include"Sphere.h"
#include"ViewCamera.h"
#include"TextureShader.h"
#include"memory"
class SceneTitle :
	public SceneBase
{
	public:
		SceneTitle(SceneManager* manager);
		~SceneTitle();

		void Initialize(Dx11::Direct3DManager*, HWND)override;
		void Updata()override;
		void Render()override;
		void Shutdown()override;

	public:
		static const std::string m_thisName;
		DxCamera::ViewCamera m_camera;
		DxModel::Sphere sphere;
		std::shared_ptr<DxShader::TextureShader>texshader;
};

#endif