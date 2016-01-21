#include "RockRender.h"

using namespace n_Rock;
using namespace aetherClass;
void RockRender::Render(ModelBase* model, std::shared_ptr<ShaderBase>shader){
	model->Render(shader.get());

	return;
}