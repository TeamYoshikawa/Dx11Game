#include "Cube.h"

namespace DxModel{
	Cube::Cube()
	{
		m_vertexBuffer = nullptr;
		m_indexBuffer = nullptr;
	}

	Cube::Cube(const Cube& other){
	}


	Cube::~Cube()
	{
	}

	bool Cube::InitializeBuffers(){
		ModelProperty::VertexType* vertices;
		unsigned long* indices;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;


		// Set the number of vertices in the vertex array.
		m_vertexCount = 8;

		// Set the number of indices in the index array.
		m_indexCount = 20;

		// Create the vertex array.
		vertices = new ModelProperty::VertexType[m_vertexCount];
		if (!vertices)
		{
			return false;
		}

		// Create the index array.
		indices = new unsigned long[m_indexCount];
		if (!indices)
		{
			return false;
		}

		// Load the vertex array with data.
		vertices[0]._position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);  // Bottom left.
//		vertices[0]._color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

		vertices[1]._position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);  // Top middle.
//		vertices[1]._color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[2]._position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);  // Bottom right.
//		vertices[2]._color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);

		vertices[3]._position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);  // Bottom right.
//		vertices[3]._color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[4]._position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);  // back bottom.
//		vertices[4]._color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

		vertices[5]._position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);  // back top
//		vertices[5]._color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[6]._position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);  // back bottom.
//		vertices[6]._color = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

		vertices[7]._position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);  // back top
//		vertices[7]._color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);


		// Load the index array with data.
		indices[0] = 0;  // Bottom left.
		indices[1] = 1;  // Top middle.
		indices[2] = 2;  // Bottom right.
		indices[3] = 3;
		indices[4] = 4;  // Bottom right.
		indices[5] = 5;
		indices[6] = 6;
		indices[7] = 7;
		indices[8] = 0;
		indices[9] = 1;
		indices[10] = 1;
		indices[11] = 7;
		indices[12] = 3;
		indices[13] = 5;
		indices[14] = 5;
		indices[15] = 4;
		indices[16] = 4;
		indices[17] = 6;
		indices[18] = 2;
		indices[19] = 0;




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


	void Cube::ShutdownBuffers(){
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

	void Cube::RenderBuffers(){
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