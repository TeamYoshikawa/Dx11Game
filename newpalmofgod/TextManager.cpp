#include "TextManager.h"
#include "PixelShader.h"

using namespace aetherClass;

bool TextManager::Initialize(ViewCamera* camera){

	m_isRender = false;
	m_color = new PixelShader();

	//ColorTextureの作成
	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	desc._pixel._entryName = "ps_main";
	desc._pixel._srcFile = L"Shader/ColorTexture.ps";

	m_color->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);

	//font
	FontDesc fontDesc;
	fontDesc._fontSize = 50;
	//fontDesc._outputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc._clipPrecision = CLIP_DEFAULT_PRECIS;
	fontDesc._charSet = SHIFTJIS_CHARSET;
	//fontDesc._fileName = L"font/apj.ttf";
	fontDesc._fontName = L"メイリオ";

	m_font = new Font();
	_ASSERT_EXPR(m_font->Load(fontDesc), "フォント作れなかったぞ");

	m_text = new Text();
	m_text->Initialize();
	m_text->SetFont(m_font);
	m_text->property._color = Color(1, 0, 1, 1);


	_ASSERT_EXPR(m_text->UpdateText(L"Score:"), "できなかった");
	m_text->property._transform._translation = Vector3(30.0f, 150.0f, 0.0f);

	return true;
}

void TextManager::SetID(int id){
	m_id = id;
	m_isRender = true;

	if (m_id == 0){
		_ASSERT_EXPR(m_text->UpdateText(L"hiromu:"), "できなかった");
	}

	if (m_id == 1){
		_ASSERT_EXPR(m_text->UpdateText(L"hiromu1:"), "できなかった");
	}


}

void TextManager::Render(){

	//falseではない場合
	if (!m_isRender)return;

	if (m_waitTime > 100){
		m_isRender = false;
	}
	m_text->Render(m_color);
}
