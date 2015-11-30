#ifndef _ModelBase_H
#define _ModelBase_H
#include <D3D11.h>
#include <D3DX10math.h>
#include <memory>
#include "Texture.h"
#include"Direct3DManager.h"
#include "TextureShader.h"
#include "ViewCamera.h"
#include "ModelProperty.h"
namespace DxModel{

	class ModelBase
	{
	public:
		ModelBase();
		ModelBase(const ModelBase&);
		virtual ~ModelBase() = default;

		bool Initialize(std::string textureFileName = "null");
		void Shutdown();
		void Render(const std::shared_ptr<Shader::TextureShader>,const std::shared_ptr<DxCamera::ViewCamera>);

		void Rotation(D3DXVECTOR3 transform, float rad);
		void Translation(D3DXVECTOR3 transform);
		void Scaling(D3DXVECTOR3 transform);

		D3DMATRIX GetTransform();
		int GetIndexCount();
		ID3D11ShaderResourceView* GetTexture();
		static void CopyManagerAddress(Dx11::Direct3DManager*);
	protected:
		// ê‚ëŒÇ…åpè≥ÇµÇƒoverrideÇµÇƒÇ≠ÇæÇ≥Ç¢
		virtual bool InitializeBuffers() = 0;
		virtual void ShutdownBuffers() = 0;
		virtual void RenderBuffers() = 0;

	protected:
		bool LoadTexture(std::string);
		

	protected:
		ID3D11Buffer* m_vertexBuffer;
		ID3D11Buffer* m_indexBuffer;
		unsigned long m_vertexCount, m_indexCount;
		std::shared_ptr<Texture> m_texture;
		static Dx11::Direct3DManager* m_direct3d;
		D3DXMATRIX m_transform;

	private:
		
		void ReleaseTexture();
	};
}
#endif