#pragma once
#include"Rock.h"
#include"ShaderBase.h"
#include<memory>
#include"Sphere.h"

namespace n_Rock{
	class RockRender
	{
	private:
		RockRender(const RockRender&) = default;
		void operator =(const RockRender&){};


	public:
		RockRender() = default;
		~RockRender() = default;

		void Render(DxModel::Sphere* model, std::shared_ptr<DxShader::ShaderBase>shader, DxModel::eRenderWay eRen);
	};
}
