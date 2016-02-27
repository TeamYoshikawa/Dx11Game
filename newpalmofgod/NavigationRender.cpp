#include "NavigationRender.h"


using namespace aetherClass;
void NavigationRender::Render(ModelBase* model, std::shared_ptr<ShaderBase>shaderBase){
	model->Render(shaderBase.get());


}