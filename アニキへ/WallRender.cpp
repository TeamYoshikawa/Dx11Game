#include "WallRender.h"

using namespace n_Wall;
using namespace aetherClass;
void WallRender::Render(ModelBase* model, std::shared_ptr<ShaderBase>shaderBase){
	model->Render(shaderBase.get());


}