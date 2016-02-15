#include "SpearRender.h"

using namespace aetherClass;
using namespace n_Spear;

SpearRender::SpearRender(){}

SpearRender::SpearRender(SpearRender& other){}

SpearRender::~SpearRender()
{
}


void SpearRender::Renderring(ModelBase* model, std::shared_ptr<ShaderBase>shaderBase)
{
	model->Render(shaderBase.get());
	
}