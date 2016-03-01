#pragma once
#include <memory>
#include <ModelBase.h>
#include "Rectangle2D.h"

class SoumatouManager
{
public:

	bool Initialize();
	void Render();
	void Update();

	SoumatouManager();
	~SoumatouManager();


private:
	std::shared_ptr<aetherClass::Texture> m_soumaTexture;
	std::shared_ptr<aetherClass::Rectangle2D> m_soumatou;
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::ShaderBase> m_colorShader;
	


};

