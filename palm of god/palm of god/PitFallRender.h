#pragma once
#include"PitFall.h"
#include"ShaderBase.h"
#include<memory>

namespace Pitfall{
	class PitFallRender
	{
	private:
		PitFallRender(const PitFallRender&) = default;
		void operator =(const PitFallRender&){};



	public:
		PitFallRender() = default;
		~PitFallRender() = default;

		void Render(aetherClass::ModelBase*, std::shared_ptr<aetherClass::ShaderBase>);

	};

}