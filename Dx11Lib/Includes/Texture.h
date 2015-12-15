#ifndef _TEXTURE_H
#define _TEXTURE_H
#include <d3d11.h>
#include <d3dX11tex.h>
#include <string>

namespace DxModel{
	class Texture
	{
		public:
			Texture();
			Texture(Texture&);
			~Texture();
		
			bool Initialize(ID3D11Device*, std::string);
			void Shutdown();
			ID3D11ShaderResourceView* GetTexture();

		private:
			ID3D11ShaderResourceView* m_texture;
	};
}


#endif