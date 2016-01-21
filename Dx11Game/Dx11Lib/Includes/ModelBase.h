#ifndef _ModelBase_H
#define _ModelBase_H
#include <D3D11.h>
#include <D3DX10math.h>
#include <memory>
#include "Texture.h"
#include"Vector3.h"
#include"Direct3DManager.h"
#include "TextureShader.h"
#include "ViewCamera.h"
#include "ModelProperty.h"

namespace DxModel{

	enum class eRenderWay{
		eColor,
		eTexture,
		eDiffuseLight
	};

	class ModelBase
	{
	private:
		DxMath::Vector3 m_scale;
		DxMath::Vector3 m_translation;
		DxMath::Vector3 m_rotation;
		void TransMatrix(D3DXMATRIX*);

	private:
		DxMath::Vector3 m_axisX;
		DxMath::Vector3 m_axisY;
		DxMath::Vector3 m_axisZ;

	public:
		DxMath::Vector3& Rotation();
		void Rotation(DxMath::Vector3 transform);

		DxMath::Vector3& Translation();
		void Translation(DxMath::Vector3 transform);

		DxMath::Vector3& Scaling();
		void Scaling(DxMath::Vector3 transform);

	public:
		bool RayPick(DxMath::Vector3&, ModelBase*, DxMath::Vector3);

		DxMath::Vector3& AxisX();
		void AxisX(DxMath::Vector3&);
		DxMath::Vector3& AxisY();
		void AxisY(DxMath::Vector3&);
		DxMath::Vector3& AxisZ();
		void AxisZ(DxMath::Vector3&);

	public:
		ModelBase();
		ModelBase(const ModelBase&);
		virtual ~ModelBase() = default;

		bool Initialize(DxCamera::ViewCamera*, std::string textureFileName = "null");
		void Shutdown();
		void Render(const std::shared_ptr<DxShader::ShaderBase>,const eRenderWay);
		void SetCamera(DxCamera::ViewCamera*);
		int GetIndexCount();

		D3DXMATRIX YawPitchRoll(float, float, float);
		void UpdateAxisAll();
		

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