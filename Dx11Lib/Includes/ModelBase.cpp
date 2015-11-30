////////////////////////////////////////////////////////////////////////////////
// Filename: ModelBase.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ModelBase.h"
#include <iostream>
namespace DxModel{

	Dx11::Direct3DManager* ModelBase::m_direct3d = nullptr;
	ModelBase::ModelBase()
	{
		
	}


	ModelBase::ModelBase(const ModelBase& other)
	{
	}

	void ModelBase::CopyManagerAddress(Dx11::Direct3DManager* d3d){
		// ƒAƒhƒŒƒX‚Ì‘ã“ü
		m_direct3d = &(*d3d);
		return;
	}

	bool ModelBase::Initialize(std::string textureFileName)
	{
		
		m_vertexBuffer = nullptr;
		m_indexBuffer = nullptr;
		m_texture = nullptr;
		m_vertexCount = 0;
		m_indexCount = 0;
		bool result = true;
		// Initialize the vertex and index buffers.
		result = InitializeBuffers();
		if (!result)
		{
			return false;
		}

		if (textureFileName != "null")
		{
			result = LoadTexture(textureFileName);
		}
		else
		{
			result = LoadTexture("texture.jpg");
		}
		if (!result)
		{
			return false;
		}
		
		return true;
	}


	void ModelBase::Shutdown()
	{
		ReleaseTexture();

		// Shutdown the vertex and index buffers.
		ShutdownBuffers();


		if (m_indexBuffer)
		{
			m_indexBuffer = nullptr;
		}

		if (m_vertexBuffer)
		{
			m_vertexBuffer = nullptr;
		}

		if (m_texture)
		{
			m_texture = nullptr;
		}

		if (m_direct3d)
		{
			m_direct3d = nullptr;
		}

		return;
	}


	void ModelBase::Render(const std::shared_ptr<Shader::TextureShader> shader, const std::shared_ptr<DxCamera::ViewCamera> camera){
		// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
		RenderBuffers();
		D3DXMATRIX projection;
		D3DXMATRIX view;
		D3DXMATRIX world;
		camera->GetViewMatrix(view);
		m_direct3d->GetProjectionMatrix(projection);
		shader->Render(m_direct3d->GetDeviceContext(), GetIndexCount(),
			GetTransform(), view, projection, GetTexture());

		D3DXMatrixIdentity(&m_transform);

		return;
	}


	int ModelBase::GetIndexCount(){
		return m_indexCount;
	}

	ID3D11ShaderResourceView* ModelBase::GetTexture(){
		return m_texture->GetTexture();
	}

	bool ModelBase::LoadTexture(std::string fileName){
		bool result;

		// Create the texture object
		m_texture = std::make_shared<Texture>();
		if (!m_texture)
		{
			return false;
		}

		// Initialize the texture obeject
		result = m_texture->Initialize(m_direct3d->GetDevice(), fileName);
	
		if (!result)
		{
			return false;
		}

		return true;
	}


	void ModelBase::ReleaseTexture()
	{
		// Release the texture object
		if (m_texture)
		{
			m_texture->Shutdown();
			m_texture.reset();
			m_texture = nullptr;
		}
		return;
	}

	void ModelBase::Translation(D3DXVECTOR3 transform){
		D3DXMATRIX transmatrix;
		D3DXMatrixTranslation(&transmatrix, transform.x, transform.y, transform.z);
		D3DXMatrixMultiply(&m_transform, &transmatrix, &m_transform);
		return;
	}
	void ModelBase::Rotation(D3DXVECTOR3 transform, float rad = 0){
		D3DXMATRIX rotematrix;
		D3DXMatrixRotationAxis(&rotematrix, &transform, rad);
		D3DXMatrixMultiply(&m_transform, &rotematrix, &m_transform);
		return;
	}
	void ModelBase::Scaling(D3DXVECTOR3 transform){
		D3DXMATRIX scalimatrix;
		D3DXMatrixScaling(&scalimatrix, transform.x, transform.y, transform.z);
		D3DXMatrixMultiply(&m_transform, &scalimatrix, &m_transform);
		return;
	}
	D3DMATRIX ModelBase::GetTransform(){
		return m_transform;
	}

}// !namespace