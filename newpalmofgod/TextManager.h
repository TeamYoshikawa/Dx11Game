#pragma once
#include "ViewCamera.h"
#include "ShaderBase.h"
#include <iostream>
#include <memory>
#include <Font.h>
#include <Text.h>

class TextManager
{
public:
	TextManager()=default;
	~TextManager()=default;


	bool Initialize(aetherClass::ViewCamera* camera);
	void SetID(int);
	void Render();

private:
	aetherClass::Text *m_text;
	aetherClass::Font *m_font;
	aetherClass::ShaderBase  *m_color;


	bool m_isRender;	//レンダーするかどうか
	int m_id;	//ナビゲーションのID
	int m_waitTime;	//表示時間
	

};

