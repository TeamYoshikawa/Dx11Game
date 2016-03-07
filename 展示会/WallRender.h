#pragma once
#include"ShaderBase.h"
#include<memory>
#include"Sphere.h"
namespace n_Wall{
	class WallRender
	{
	private:
		WallRender(const WallRender&) = default;
		void operator =(const WallRender&){};


	public:
		WallRender() = default;
		~WallRender() = default;

		void Render(aetherClass::ModelBase* model, std::shared_ptr<aetherClass::ShaderBase>shader);
	};
}
