#pragma once
#include <memory>
#include <ModelBase.h>
#include "Rectangle2D.h"

class SoumatouManager
{
private:
	enum class eEvent
	{
		eNomal,
		eThrow
	};
	eEvent m_eEvent;
public:

	bool Initialize();
	void Render();
	void Update();

	int SoumatouGet();
	void SoumatouSet(int);

	SoumatouManager();
	~SoumatouManager();


private:
	std::shared_ptr<aetherClass::Texture> m_soumaTexture;
	std::shared_ptr<aetherClass::Rectangle2D> m_soumatou;
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::ShaderBase> m_colorShader;
	
	int m_pressCount;
	int m_countDown;
	bool flag = false;
};

