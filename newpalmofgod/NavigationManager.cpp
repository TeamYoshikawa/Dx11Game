#include "NavigationManager.h"

using namespace aetherClass;


bool NavigationManager::Initialize(ViewCamera* camera){

	m_color = new PixelShader();

	//color
	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	desc._pixel._entryName = "ps_main";
	desc._pixel._srcFile = L"Shader/ColorTexture.ps";

	m_color->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);


	//font
	FontDesc fontDesc;
	fontDesc._fontSize = 50;
	fontDesc._outputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc._clipPrecision = CLIP_DEFAULT_PRECIS;
	fontDesc._charSet = SHIFTJIS_CHARSET;
	fontDesc._fileName = L"font/apj.ttf";
	fontDesc._fontName = L"‚ ‚ñ‚¸‚à‚¶";

	m_font = new Font();
	_ASSERT_EXPR(m_font->Load(fontDesc), "ƒtƒHƒ“ƒgì‚ê‚È‚©‚Á‚½‚¼");

	m_text = new Text();
	m_text->Initialize();
	m_text->SetFont(m_font);
	m_text->GetColor() = Color(1, 1, 1, 1);
	m_text->UpdateText(L"Score:");


	m_navigationTexture = std::make_shared<Texture>();
	m_navigationTexture->Load("location.png");

	for (int i = 0; i < navi_max; i++){
		m_navigation[i] = std::make_shared<Cube>();
		if (!m_navigation[i]->Initialize()){
			return false;
		}
	}

	for (int i = 0; i < navi_max; i++){
		m_navigation[i]->SetCamera(camera);
		m_navigation[i]->SetTexture(m_navigationTexture.get());
	}


	m_navigation[0]->GetTransform()._translation = Vector3(2800.0f, 140.0f, 1050.0f);
	m_navigation[0]->GetTransform()._scale = Vector3(260.0f, 20.0f, 180.0f);

	m_text->GetTransform()._translation = Vector3(30.0f, 150.0f, 0.0f);

	return true;
}

void NavigationManager::Render(std::shared_ptr<ShaderBase>shader){

	m_text->Render(m_color);
	m_navigation[0]->Render(shader.get());
	
}

void NavigationManager::Update()
{

	if (GameController::GetKey().IsKeyDown(DIK_UP)){
		m_score += 100;
		std::wstring str = L"Score:" + std::to_wstring(m_score);
		m_text->UpdateText(str);
		m_text->UpdateText(L"Score:");
	}

	m_updater->Update(m_navigation[0].get());

}

void NavigationManager::Finalize()
{

	return;
}