#pragma once
#include <memory>
#include <ModelBase.h>
#include "Rectangle2D.h"
#include "GameSound.h"


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
	void DamageFlagTrue();
	void DamageFlagFalse();


	int SoumatouGet();
	void SoumatouSet(int);

	int DamageGet();
	void DamageSet(int);

	SoumatouManager();
	~SoumatouManager();


private:
	std::shared_ptr<aetherClass::GameSound> m_sound;
	std::shared_ptr<aetherClass::Texture> m_soumaTexture;
	std::shared_ptr<aetherClass::Rectangle2D> m_soumatou;
	std::shared_ptr<aetherClass::Rectangle2D> m_damage;
	std::shared_ptr<aetherClass::ShaderBase> m_pixelShader;
	std::shared_ptr<aetherClass::ShaderBase> m_colorShader;
	
	int m_pressCount;
	int m_countDown;
	int m_damageCount;
	bool flag = false;
	bool damage_flag;
};

