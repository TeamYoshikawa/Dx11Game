#include "PitFallRender.h"

using namespace Pitfall;
using namespace aetherClass;
void PitFallRender::Render(ModelBase* model, std::shared_ptr<ShaderBase>shader){
	model->Render(shader.get());

}

