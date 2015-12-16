#include "SpearRender.h"


SpearRender::SpearRender(){}

SpearRender::SpearRender(SpearRender& other){}

SpearRender::~SpearRender()
{
}


void SpearRender::Renderring(DxModel::Cube *model, std::shared_ptr<DxShader::ShaderBase>shaderBase, DxModel::eRenderWay eRen)
{
	model->Render(shaderBase, eRen);
	
}