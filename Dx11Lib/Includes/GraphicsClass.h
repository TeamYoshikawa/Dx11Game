#ifndef _GRAPHICSCLASS_H
#define _GRAPHICSCLASS_H
#include "Direct3DManager.h"
#include "ViewCamera.h"
#include "Triangle.h"
#include "ColorShader.h"
#include <memory>
#include "TextureShader.h"
#include "FbxStaticMesh.h"
#include "MaterialShader.h"
#include "Cube.h"
#include "Rectangle.h"
#include "Line.h"
namespace{
	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;
}
const int HOGE = 500;
class GraphicsClass
{
	public:
		GraphicsClass();
		
		GraphicsClass(const GraphicsClass&);
		~GraphicsClass();

		bool Initialize(POINT,const HWND);
		void Shutdown();
		bool Frame();

	private:

		bool Render(float);

	private:

		std::shared_ptr<Dx11::Direct3DManager> m_d3d;
		std::shared_ptr<DxCamera::ViewCamera> m_camera;
		std::shared_ptr<DxModel::Triangle> m_triangle;
		std::shared_ptr<DxShader::ColorShader> m_colorShader;
		std::shared_ptr<DxShader::TextureShader> m_textureShader;
		std::shared_ptr<DxShader::MaterialShader> m_materialShader;
		std::shared_ptr<DxModel::FbxStaticMesh> m_staticMesh;
		std::shared_ptr<DxModel::Cube> m_cube;
		std::shared_ptr<DxModel::Line> m_line;
};

#endif