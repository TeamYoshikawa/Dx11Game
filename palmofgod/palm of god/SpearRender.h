#pragma once
#ifndef _SPEARRENDER_H_
#define _SPEARRENDER_H_

//#include "Spear.h"
#include <ShaderBase.h>
#include <ModelBase.h>
//#include <Cube.h>

/*
     
*/
namespace n_Spear{

	class SpearRender
	{
	public:
		SpearRender();
		SpearRender(SpearRender& other);
		~SpearRender();

		void Renderring(aetherClass::ModelBase*, std::shared_ptr<aetherClass::ShaderBase>);
	};

}

#endif