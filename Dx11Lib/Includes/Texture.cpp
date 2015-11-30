#include "Texture.h"

#define DX_RELEASE(x) {x->Release(); x = nullptr;}
#define ERROR_MESSAGE(x){MessageBox(NULL,x, L"Error", MB_OK);}

namespace DxModel{
	Texture::Texture()
	{
		m_texture = nullptr;
	}
	Texture::Texture(Texture& other){}

	Texture::~Texture()
	{
		m_texture = nullptr;
	}

	bool Texture::Initialize(ID3D11Device* device, std::string filename){

		HRESULT result;

		// Load the texture
		result = D3DX11CreateShaderResourceViewFromFileA(device, filename.c_str(), NULL, NULL, &m_texture, NULL);

		if(FAILED(result))
		{
			return false;
		}
		return true;
	}

	void Texture::Shutdown(){
		// Release the vertex texture resource
		if (m_texture)
		{
			DX_RELEASE(m_texture);
		}

		return;
	}

	ID3D11ShaderResourceView* Texture::GetTexture(){
		if (!m_texture)
		{
			ERROR_MESSAGE(L"Not created Texture Object");
			return nullptr;
		}
		return m_texture;
	}

}

