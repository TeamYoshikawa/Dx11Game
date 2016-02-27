#pragma once
#include"ShaderBase.h"
#include"ModelBase.h"
#include<memory>

class NavigationRender
{
private:
	NavigationRender(const NavigationRender&) = default;
	void operator =(const NavigationRender&){};

public:
	NavigationRender() = default;
	~NavigationRender() = default;

	void Render(aetherClass::ModelBase* model, std::shared_ptr<aetherClass::ShaderBase>shader);
};

