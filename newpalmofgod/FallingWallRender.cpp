#include "FallingWallRender.h"

using namespace aetherClass;
using namespace std;

void FallingWallRender::Render(ModelBase* model, shared_ptr<ShaderBase> shader)
{
	model->Render(shader.get());
}