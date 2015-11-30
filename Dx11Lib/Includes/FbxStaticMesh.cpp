#include "FbxStaticMesh.h"
#include <iostream>
namespace DxModel
{
	FbxStaticMesh::FbxStaticMesh()
	{
	}


	FbxStaticMesh::~FbxStaticMesh()
	{
	}

	void FbxStaticMesh::LoadFBX(std::string file, MyFbx::FbxLoader::eAxisSystem axis){

		bool result;
		m_fbxLoader = std::make_unique<MyFbx::FbxLoader>();
		m_fbxLoader->FileOpen(file, axis);

		return;
	}

	bool FbxStaticMesh::InitializeBuffers(){
		ModelProperty::MeshElements meshElements;
		ModelProperty::VertexType* vertices = nullptr;
		unsigned long* indices = nullptr;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;
		
		m_fbxLoader->GetMeshElements(meshElements);
		m_indexCount = meshElements._indexCount;
		vertices = m_fbxLoader->GetVertex();
		indices = m_fbxLoader->GetIndex();
		
		std::cout<<vertices<<std::endl;

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(ModelProperty::VertexType) * meshElements._vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		result = m_direct3d->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
		if (FAILED(result))
		{
			MessageBox(NULL, L"Could not created vertexBuffer", L"Error", MB_OK);
			return false;
		}

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long)*meshElements._indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		result = m_direct3d->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	
		delete[] vertices;
		vertices = nullptr;
		delete[] indices;
		indices = nullptr;
		return true;
	}

	void FbxStaticMesh::ShutdownBuffers(){
		if (m_fbxLoader)
		{
			m_fbxLoader->Release();
			m_fbxLoader.release();
			m_fbxLoader = nullptr;
		}
		return;
	}
	void FbxStaticMesh::RenderBuffers(){
		unsigned int stride;
		unsigned int offset;

		stride = sizeof(ModelProperty::VertexType);
		offset = 0;

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		m_direct3d->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		m_direct3d->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		m_direct3d->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return;
	}

}