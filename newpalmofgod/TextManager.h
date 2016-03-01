#pragma once
#include "ViewCamera.h"
#include "ShaderBase.h"
#include <iostream>
#include <memory>
#include <Font.h>
#include <Text.h>
#include <Rectangle2D.h>
#include <Texture.h>
#include "GameSound.h"

class TextManager
{
public:
	TextManager()=default;
	~TextManager()=default;


	bool Initialize(aetherClass::ViewCamera* camera);
	void SetID(int);
	void Render(aetherClass::ShaderBase *);
	void SetTime();

private:
	aetherClass::Text *m_text;
	aetherClass::Font *m_font;
	aetherClass::ShaderBase  *m_color;
	aetherClass::Rectangle2D *m_background;
	aetherClass::Texture *m_texture;
	aetherClass::GameSound *m_rock;
	aetherClass::GameSound *m_spear;

	bool m_isRender;	//レンダーするかどうか
	int m_id;	//ナビゲーションのID
	int m_waitTime;	//表示時間
	

};

