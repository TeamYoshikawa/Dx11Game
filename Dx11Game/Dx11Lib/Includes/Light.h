#pragma once
#include"Vector4.h"
namespace DxLight{
	class Light
	{
	private:
		DxMath::Vector4 m_translation;
	public:
		Light();
		~Light();

		DxMath::Vector4& Translation();
		void Translation(DxMath::Vector4);

	};

}