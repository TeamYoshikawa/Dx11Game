#include "TextManager.h"
#include "PixelShader.h"
#include "Texture.h"
#include "DirectXEntity.h"

using namespace aetherClass;

bool TextManager::Initialize(ViewCamera* camera){

	m_isRender = false;
	m_color = new PixelShader();

	//ColorTexture�̍쐬
	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	desc._pixel._entryName = "ps_main";
	desc._pixel._srcFile = L"Shader/ColorTexture.ps";

	m_color->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);

	//font
	FontDesc fontDesc;
	fontDesc._fontSize = 30;
	//fontDesc._outputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc._clipPrecision = CLIP_DEFAULT_PRECIS;
	fontDesc._charSet = SHIFTJIS_CHARSET;
	fontDesc._fileName = L"font/onryou.ttf";
	//fontDesc._fontName = L"HG�޼��E";
	fontDesc._fontName = L"����";

	m_font = new Font();
	_ASSERT_EXPR(m_font->Load(fontDesc), "�t�H���g���Ȃ�������");

	m_text = new Text();
	m_text->Initialize();
	m_text->SetFont(m_font);
	m_text->property._color = Color(0.8, 0.0, 0.1, 1);

	// �e�L�X�`���̍쐬
	m_texture = new Texture;
	m_texture->Load("Texture/h_ui.png");

	// ���b�Z�[�W�{�b�N�X�̍쐬
	m_background = new Rectangle2D;
	m_background->Initialize();
	m_background->SetTexture(m_texture);
	m_background->property._transform._scale = Vector3(400, 80, 1);
	m_background->property._transform._translation = Vector3(0.0f, 770.0f, 0.0f);
	m_background->property._color._alpha = 0.3;

	// ���SE
	m_rock = new GameSound;
	m_rock->Load("Sound/Rock/Iwa_korogaru.wav");
	m_rock->SetValume(+3000);

	// ����SE
	m_spear = new GameSound;
	m_spear->Load("Sound/Environmental sound/ok.wav");
	m_spear->SetValume(+3000);

	// �K��������
	_ASSERT_EXPR(m_text->UpdateText(L"Score:"), "�ł��Ȃ�����");

	m_text->property._transform._translation = Vector3(40.0f, 800.0f, 0.0f);

	return true;
}

void TextManager::SetID(int id){

	m_id = id;
	m_isRender = true;

	if (m_id == 0){
		if (m_text->property._transform._translation._y > 150){
			m_text->property._transform._translation._y -= 4;
			m_background->property._transform._translation._y -= 4;
		}
		m_text->UpdateText(L"SPACE�������Ă�������");
	}

	if (m_id == 1){
		m_rock->PlayToOneTime();
		m_text->UpdateText(L"�������������H");
	}

	if (m_id == 2){
		m_spear->PlayToOneTime();
		m_text->UpdateText(L"�������������H");
	}

	if (m_id == 3){
		m_text->UpdateText(L"������");
	}

	if (m_id == 4){
		m_text->UpdateText(L"���蔲����");
	}

}

void TextManager::Render(ShaderBase *m_shader){

	if (!m_isRender){
		SetTime();
	}

	//false�ł͂Ȃ��ꍇ
	if (!m_isRender)return;

	if (m_waitTime > 150){
		m_isRender = false;
	}

	m_waitTime++;
	std::cout << m_waitTime << std::endl;
	m_background->Render(m_shader);
	DirectXEntity entity;
	entity.GetDirect3DManager()->Change2DMode();
	m_text->Render(m_color);
	entity.GetDirect3DManager()->Change3DMode();
}

void TextManager:: SetTime(){
	m_waitTime= 0;
}