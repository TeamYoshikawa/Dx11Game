#include "PitFall.h"
#include<iostream>
#include <VertexType.h>
	using namespace Pitfall;
	using namespace aetherClass;
	bool PitFall::InitializeBuffers(){
		VertexType* vertices;
		unsigned long* indices;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;


		// Set the number of vertices in the vertex array.
		m_vertexCount = 16;

		// Set the number of indices in the index array.
		m_indexCount = 16;

		// Create the vertex array.
		vertices = new VertexType[m_vertexCount];
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

		Vector4 WHITE(0.5, 0.5, 0.5, 1);
		Vector4 BLACK(0, 0, 0, 1);

		Vector3 origin(0, -1, 0);
		// Load the vertex array with data.
		//Fore
		vertices[3]._position = Vector3(-1.0f, origin._y + -1.0f, -1.0f);
		vertices[3]._uv = Vector2(0.0f, 1.0f);
	
		vertices[2]._position = Vector3(-1.0f, origin._y + 1.0f, -1.0f);
		vertices[2]._uv = Vector2(0.0f, 0.0f);
	
		vertices[1]._position = Vector3(1.0f, origin._y + -1.0f, -1.0f);
		vertices[1]._uv = Vector2(1.0f, 1.0f);
	
		vertices[0]._position = Vector3(1.0f, origin._y + 1.0f, -1.0f);
		vertices[0]._uv = Vector2(1.0f, 0.0f);
		
		//Side left
		vertices[7]._position = Vector3(-1.0f, origin._y + -1.0f, 1.0f);
		vertices[7]._uv = Vector2(0.0f, 1.0f);
		
		vertices[6]._position = Vector3(-1.0f, origin._y, 1.0f);
		vertices[6]._uv = Vector2(0.0f, 0.0f);
		
		vertices[5]._position = Vector3(-1.0f, origin._y + -1.0f, -1.0f);
		vertices[5]._uv = Vector2(1.0f, 1.0f);
		
		vertices[4]._position = Vector3(-1.0f, origin._y, -1.0f);
		vertices[4]._uv = Vector2(1.0f, 0.0f);
	
		//Back
		vertices[11]._position = Vector3(1.0f, origin._y + -1.0f, 1.0f);
		vertices[11]._uv = Vector2(0.0f, 1.0f);
	
		vertices[10]._position = Vector3(1.0f, origin._y + 1.0f, 1.0f);
		vertices[10]._uv = Vector2(0.0f, 0.0f);
	
		vertices[9]._position = Vector3(-1.0f, origin._y + -1.0f, 1.0f);
		vertices[9]._uv = Vector2(1.0f, 1.0f);
	
		vertices[8]._position = Vector3(-1.0f, origin._y + 1.0f, 1.0f);
		vertices[8]._uv = Vector2(1.0f, 0.0f);
		

		//Side right
		vertices[15]._position = Vector3(1.0f, origin._y + -1.0f, -1.0f);
		vertices[15]._uv = Vector2(0.0f, 1.0f);
		
		vertices[14]._position = Vector3(1.0f, origin._y, -1.0f);
		vertices[14]._uv = Vector2(0.0f, 0.0f);
	
		vertices[13]._position = Vector3(1.0f, origin._y + -1.0f, 1.0f);
		vertices[13]._uv = Vector2(1.0f, 1.0f);
		
		vertices[12]._position = Vector3(1.0f, origin._y, 1.0f);
		vertices[12]._uv = Vector2(1.0f, 0.0f);


		// Load the index array with data.
		for (int i = 0; i < m_indexCount; i++)
		{
			indices[i] = i;
		}



		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now create the vertex buffer.
		result = GetDirect3DManager()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
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
		result = GetDirect3DManager()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
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


	void PitFall::FinalizeBuffers(){
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

	void PitFall::RenderBuffers(){
		unsigned int stride;
		unsigned int offset;



		// Set vertex buffer stride and offset.
		stride = sizeof(VertexType);
		offset = 0;

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		GetDirect3DManager()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		GetDirect3DManager()->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		GetDirect3DManager()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		return;
	}

	bool PitFall::GroundDecision(ModelBase &other){


		float rayVector = -1;

		float rayEnd = rayVector + other.property._transform._translation._y;

		//		printf("Cube = %f\n", Translation().y);
		//		printf("Other = %f\nrayEnd = %f\n\n", other.Translation().y, rayEnd);

		Vector2 origin(property._transform._translation._x - (property._transform._scale._x), property._transform._translation._z + (property._transform._scale._z));
		Vector2 uv(property._transform._translation._x + (property._transform._scale._x), property._transform._translation._z - (property._transform._scale._z));

		Vector2 other_origin(other.property._transform._translation._x, other.property._transform._translation._z);

		std::cout << origin._y << other_origin._y << std::endl;

		if (origin._x < other_origin._x && other_origin._x < uv._x && uv._y < other_origin._y && other_origin._y < origin._y){
			if (property._transform._translation._y > other.property._transform._translation._y){
				//				std::cout << "\n///Falling?///\n";
				return true;
			}
		}
		return false;
	}

