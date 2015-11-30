#include "Rectangle.h"

namespace DxModel{
	Rectangle::Rectangle()
	{
		m_vertexBuffer = nullptr;
		m_indexBuffer = nullptr;
	}

	Rectangle::Rectangle(const Rectangle& other){
	}


	Rectangle::~Rectangle()
	{
	}

	bool Rectangle::InitializeBuffers(){
		ModelProperty::VertexType* vertices = nullptr;
		unsigned long* indices = nullptr;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;

		m_vertexCount = 4;
		m_indexCount = 4;

		vertices = new ModelProperty::VertexType[m_vertexCount];
		if (!vertices){
			return false;
		}

		indices = new unsigned long[m_indexCount];
		if (!indices){
			return false;
		}

		// Load the vertex array with data.
		vertices[0]._position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Buttom left
//		vertices[0]._color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

		vertices[1]._position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left.
	//	vertices[1]._color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);

		vertices[2]._position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	//	vertices[2]._color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

		vertices[3]._position = D3DXVECTOR3(2.0f, -2.0f, 0.0f);  // top right.
	//	vertices[3]._color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 3;	//top right

		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(ModelProperty::VertexType) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now create the vertex buffer.
		result = m_direct3d->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
		if (FAILED(result))
		{
			return false;
		}

		// Set up the description of the static index buffer.
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the index data.
		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		result = m_direct3d->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
		if (FAILED(result))
		{
			return false;
		}

		// Release the arrays now that the vertex and index buffers have been created and loaded.
		delete[] vertices;
		vertices = 0;

		delete[] indices;
		indices = 0;

		return true;

	}


	void Rectangle::ShutdownBuffers(){
		if (m_indexBuffer)
		{
			m_indexBuffer->Release();
			m_indexBuffer = 0;
		}

		// Release the vertex buffer.
		if (m_vertexBuffer)
		{
			m_vertexBuffer->Release();
			m_vertexBuffer = 0;
		}

		return;
	}

	void Rectangle::RenderBuffers(){
		unsigned int stride;
		unsigned int offset;


		// Set vertex buffer stride and offset.
		stride = sizeof(ModelProperty::VertexType);
		offset = 0;

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		m_direct3d->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		m_direct3d->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		m_direct3d->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		return;
	}
}