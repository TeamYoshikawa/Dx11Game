#pragma once
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

		void Render(aetherClass::ModelBase* model, std::shared_ptr<aetherClass::ShaderBase>shader);
	};
}
