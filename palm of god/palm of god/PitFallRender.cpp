#include "PitFallRender.h"

using namespace Pitfall;

void PitFallRender::Render(DxModel::ModelBase* model, std::shared_ptr<DxShader::ShaderBase>shader, DxModel::eRenderWay eRen){
	model->Render(shader, eRen);

}

