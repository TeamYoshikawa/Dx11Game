#include "SpearRender.h"

using namespace aetherClass;
SpearRender::SpearRender(){}

SpearRender::SpearRender(SpearRender& other){}

SpearRender::~SpearRender()
{
}


void SpearRender::Renderring(ModelBase* model, std::shared_ptr<ShaderBase>shaderBase)
{
	model->Render(shaderBase.get());
	
}