#include "Triangle.h"

namespace DxModel{
	Triangle::Triangle()
	{
	
	}

	Triangle::Triangle(Triangle& other){}

	Triangle::~Triangle(){
	}

	bool Triangle::InitializeBuffers(){

		ModelProperty::VertexType* vertices = nullptr;
		unsigned long* indices = nullptr;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;

		m_vertexCount = 3;
		m_indexCount = 3;

		vertices = new ModelProperty::VertexType[m_vertexCount];
		if (!vertices)
		{
			return false;
		}

		indices = new unsigned long[m_indexCount];
		if (!indices)
		{
			return false;
		}

		// BottomLeft
		vertices[0]._position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		vertices[0]._uv._buffer = D3DXVECTOR2(0.0f, 1.0f);

		// Top middle
		vertices[1]._position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertices[1]._uv._buffer = D3DXVECTOR2(0.5f, 0.0f);

		// BottomRight
		vertices[2]._position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		vertices[2]._uv._buffer = D3DXVECTOR2(1.0f, 1.0f);

		// Load the index array with data
		indices[0] = 0; // Bottom left
		indices[1] = 1; // Top middle
		indices[2] = 2; // Bottom right

		// Set up the description of the static vertex buffer
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(ModelProperty::VertexType)*m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now create the vertex buffer
		result = m_direct3d->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
		if (FAILED(result))
		{
			return false;
		}

		// Set up description of the static index buffer
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the index data
		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer
		result = m_direct3d->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
		if (FAILED(result))
		{
			return false;
		}

		// Relese the arrays now that the vertex and index buffers have been created and loaded
		ARRAY_RELEASE(vertices);
		ARRAY_RELEASE(indices);

		return true;
	}


	void Triangle::ShutdownBuffers(){
		// Release the index buffer
		if (m_indexBuffer)
		{
			DX_RELEASE(m_indexBuffer);
		}
		// Release the vertex buffer
		if (m_vertexBuffer)
		{
			DX_RELEASE(m_vertexBuffer);
		}
		return;
	}


	void Triangle::RenderBuffers(){
		unsigned int stride;
		unsigned int offset;

		// Set vertex buffer stride and offset
		stride = sizeof(ModelProperty::VertexType);
		offset = 0;

		// Set the vertex buffer to active in the input assembler so it can be rendered
		m_direct3d->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered
		m_direct3d->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer,in this case triangle
		m_direct3d->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}

