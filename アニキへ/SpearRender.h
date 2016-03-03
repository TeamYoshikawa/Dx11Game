#pragma once
#ifndef _SPEARRENDER_H_
#define _SPEARRENDER_H_

//#include "Spear.h"
#include <ShaderBase.h>
#include <ModelBase.h>
#include <Cube.h>
#include <FbxModel.h>

/*
     
*/
namespace n_Spear{

	class SpearRender
	{
	public:
		SpearRender();
		SpearRender(SpearRender& other);
		~SpearRender();

		void Renderring(std::shared_ptr<aetherClass::FbxModel>&, std::shared_ptr<aetherClass::ShaderBase>);
	};

}

#endif