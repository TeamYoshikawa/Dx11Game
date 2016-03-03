#include "TextManager.h"
#include "PixelShader.h"
#include "Texture.h"
#include "DirectXEntity.h"

using namespace aetherClass;

bool TextManager::Initialize(ViewCamera* camera){

	m_isRender = false;
	m_color = new PixelShader();

	//ColorTextureの作成
	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	desc._pixel._entryName = "ps_main";
	desc._pixel._srcFile = L"Shader/Transparent.ps";

	m_color->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);

	//font
	FontDesc fontDesc;
	fontDesc._fontSize = 30;
	//fontDesc._outputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc._clipPrecision = CLIP_DEFAULT_PRECIS;
	fontDesc._charSet = SHIFTJIS_CHARSET;
	fontDesc._fileName = L"font/onryou.ttf";
	//fontDesc._fontName = L"HGｺﾞｼｯｸE";
	fontDesc._fontName = L"怨霊";

	m_font = new Font();
	_ASSERT_EXPR(m_font->Load(fontDesc), "フォント作れなかったぞ");

	m_text = new Text();
	m_text->Initialize();
	m_text->SetFont(m_font);
	m_text->property._color = Color(0.8, 0.0, 0.1, 1);

	// テキスチャの作成
	m_texture = new Texture;
	m_texture->Load("Texture/UI_ba-3.png");

	// メッセージボックスの作成
	m_background = new Rectangle2D;
	m_background->Initialize();
	m_background->SetTexture(m_texture);
	m_background->property._transform._scale = Vector3(400, 80, 1);
	m_background->property._transform._translation = Vector3(-400.0f, 120.0f, 0.0f);
	m_background->property._color._alpha = 0.3;

	// 岩のSE
	m_rock = new GameSound;
	m_rock->Load("Sound/Rock/Iwa_korogaru.wav");
	m_rock->SetValume(+3000);

	// 槍のSE
	m_spear = new GameSound;
	m_spear->Load("Sound/Environmental sound/ok.wav");
	m_spear->SetValume(+3000);

	// 必ず初期化
	_ASSERT_EXPR(m_text->UpdateText(L"Score:"), "できなかった");

	m_text->property._transform._translation = Vector3(-400.0f, 150.0f, 0.0f);

	return true;
}

void TextManager::SetID(int id){

	m_id = id;
	m_flag = 0;
	m_isRender = true;

	if (m_id == 0){
		if (m_text->property._transform._translation._x < 50){
			m_text->property._transform._translation._x += 5;
		}

		if (m_background->property._transform._translation._x < 0){
			m_background->property._transform._translation._x += 5;
		}

		m_text->UpdateText(L"SPACEを押してください");
		m_spear->PlayToOneTime();
	}

	if (m_id == 1){
		if (m_text->property._transform._translation._x < 50){
			m_text->property._transform._translation._x += 5;
		}

		if (m_background->property._transform._translation._x < 0){
			m_background->property._transform._translation._x += 5;
		}

		m_rock->PlayToOneTime();
		m_text->UpdateText(L"何か音がする");
	}

	if (m_id == 2){
		if (m_text->property._transform._translation._x < 50){
			m_text->property._transform._translation._x += 5;
		}

		if (m_background->property._transform._translation._x < 0){
			m_background->property._transform._translation._x += 5;
		}
		m_spear->PlayToOneTime();
		m_text->UpdateText(L"何か音がする");
	}

	if (m_id == 3){
		if (m_text->property._transform._translation._x < 50){
			m_text->property._transform._translation._x += 5;
		}

		if (m_background->property._transform._translation._x < 0){
			m_background->property._transform._translation._x += 5;
		}
		m_text->UpdateText(L"避けろ");
	}

	if (m_id == 4){
		if (m_text->property._transform._translation._x < 50){
			m_text->property._transform._translation._x += 5;
		}

		if (m_background->property._transform._translation._x < 0){
			m_background->property._transform._translation._x += 5;
		}
		m_text->UpdateText(L"潜り抜けろ");
	}

}

void TextManager::Render(ShaderBase *m_shader){

	if (!m_isRender){
		m_background->property._transform._translation = Vector3(-400.0f, 120.0f, 0.0f);
		m_text->property._transform._translation = Vector3(-400.0f, 150.0f, 0.0f);
		SetTime();
	}

	if (!m_isRender){
		return; 
	}

	if(m_waitTime > 200){

		m_isRender = false;
		
	}

	m_waitTime++;
	//std::cout << m_waitTime << std::endl;
	DirectXEntity entity;
	entity.GetDirect3DManager()->Change2DMode();
	m_background->Render(m_shader);
	m_text->Render(m_color);
	entity.GetDirect3DManager()->Change3DMode();

	
}

void TextManager:: SetTime(){
	m_waitTime= 0;
}

int TextManager::GetTime(){
	return m_waitTime;
}

int TextManager::GetFlag(){
	return m_flag;
}

