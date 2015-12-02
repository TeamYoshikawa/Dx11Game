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

	enum class eRenderWay{
		eColor,
		eTexture,
	};

	class ModelBase
	{
	private:
		D3DXVECTOR3 scale;
		D3DXVECTOR3 translation;
		D3DXVECTOR3 rotation;
		void TransMatrix(D3DXMATRIX*);
	public:
		D3DXVECTOR3& Rotation();
		void Rotation(D3DXVECTOR3 transform);

		D3DXVECTOR3& Translation();
		void Translation(D3DXVECTOR3 transform);

		D3DXVECTOR3& Scaling();
		void Scaling(D3DXVECTOR3 transform);

	public:
		ModelBase();
		ModelBase(const ModelBase&);
		virtual ~ModelBase() = default;

		bool Initialize(DxCamera::ViewCamera*,std::string textureFileName = "null");
		void Shutdown();
		void Render(DxShader::ShaderBase*,const eRenderWay);

		void SetCamera(DxCamera::ViewCamera*);
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

	private:
		
		void ReleaseTexture();

	private:
		DxCamera::ViewCamera* m_camera;
	};
}
#endif