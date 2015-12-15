#ifndef _FBXBASE_H
#define _FBXBASE_H
#include "ShaderBase.h"
#include "ModelBase.h"
#include "FbxModelProperty.h"
#include "FbxLoader.h"
#include <memory>

namespace DxModel{
	class FbxBase
	{
	public:
		FbxBase();
		FbxBase(const FbxBase&);
		virtual ~FbxBase() = default;
		virtual void LoadFBX(std::string, DxFbx::FbxLoader::eAxisSystem);
		virtual bool Initialize(DxCamera::ViewCamera*, std::string textureFileName = "null");
		virtual void Shutdown();
		virtual void AllNodeRender(const std::shared_ptr<DxShader::ShaderBase>,const eRenderWay);
		virtual void NodeRender(const std::shared_ptr<DxShader::ShaderBase>, const eRenderWay,int);
		virtual void SetCamera(DxCamera::ViewCamera*);

		virtual unsigned long GetIndexCount(int id);

		virtual ID3D11ShaderResourceView* GetTexture();

		virtual int GetMeshNodeCount()const;

		static void CopyManagerAddressToFbx(Dx11::Direct3DManager*);

		virtual DxMath::Transform& Transform();
		virtual void Transform(DxMath::Transform);
	private:
		// ê‚ëŒÇ…åpè≥ÇµÇƒoverrideÇµÇƒÇ≠ÇæÇ≥Ç¢
		virtual bool InitializeBuffers() = 0;
		virtual void ShutdownBuffers() = 0;
		virtual void NodeRenderBuffers(int id) = 0;
	protected:
		virtual bool LoadTexture(std::string);
		virtual bool LoadMeshNodeTexture(DxModel::Texture*, std::string);

	protected:
		static Dx11::Direct3DManager* m_direct3d;

		FbxModelProperty::FbxMeshBuffer* m_meshBuffer;
		ModelProperty::MeshElements* m_meshElements;
		std::shared_ptr<DxModel::Texture> m_texture;
		std::unique_ptr<DxFbx::FbxLoader> m_fbxLoader;
		

	private:
		virtual void ReleaseTexture();
		virtual void TransMatrix(D3DXMATRIX*,int);

	private:

		DxCamera::ViewCamera* m_camera;

		DxMath::Transform m_transform;
		
		
	};

}

#endif