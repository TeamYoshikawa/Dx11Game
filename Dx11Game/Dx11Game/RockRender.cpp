#include "RockRender.h"

using namespace n_Rock;

void RockRender::Render(DxModel::Sphere* model, std::shared_ptr<DxShader::ShaderBase>shader, DxModel::eRenderWay eRen){
	model->Render(shader, eRen);

	return;
}