#include "Sphere.h"
#include <fstream>
#include <iostream>
#include "Vector3.h"
#include "Vector2.h"

using namespace std;
namespace DxModel
{
	Sphere::Sphere()
	{
	}

	Sphere::Sphere(const Sphere&)
	{
	}

	Sphere::~Sphere()
	{
	}

	bool Sphere::InitializeBuffers(){
		ModelProperty::VertexType* vertices;
		unsigned long* indices;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;
		
		LoadFile("ModelData/sphere.txt");
		
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
		// Load the index array with data.
		for (int i = 0; i < m_vertexCount; i++)
		{
			vertices[i]._position = DxMath::Vector3(m_model[i].x, m_model[i].y, m_model[i].z);
			vertices[i]._uv = DxMath::Vector2(m_model[i].tu, m_model[i].tv);
			vertices[i]._normal = DxMath::Vector3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

			indices[i] = i;
		}

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
			MessageBox(NULL, L"fuck", NULL, NULL);
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

		delete[] m_model;
		m_model = 0;
		return true;

	}


	void Sphere::ShutdownBuffers(){
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

	void Sphere::RenderBuffers(){
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

	bool Sphere::LoadFile(char* filename)
	{
		fstream ifs;
		char input;
		int i;

		ifs.open(filename);
		if (ifs.fail())return false;

		ifs.get(input);
		while (input != ':')
		{
			ifs.get(input);
		}

		ifs >> m_vertexCount;

		m_indexCount = m_vertexCount;

		m_model = new Model[m_vertexCount];

		if (!m_model)
		{
			return false;
		}

		ifs.get(input);
		while (input != ':')
		{
			ifs.get(input);
		}

		ifs.get(input);
		ifs.get(input);

		for (i = 0; i < m_vertexCount; i++)
		{
			ifs >> m_model[i].x >> m_model[i].y >> m_model[i].z;
			ifs >> m_model[i].tu >> m_model[i].tv;
			ifs >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
		}

		ifs.close();
		return true;
	}
}

