#pragma once
#ifndef _SPEARRENDER_H_
#define _SPEARRENDER_H_

#include"Spear.h"
#include <ShaderBase.h>
#include <ModelBase.h>
#include <FbxStaticMesh.h>

/*
     
*/



class SpearRender
{
public:
	SpearRender();
	SpearRender(SpearRender& other);
	~SpearRender();

	
	void Renderring(DxModel::Cube*, std::shared_ptr<DxShader::ShaderBase>, DxModel::eRenderWay);
	void Initialize();

};

#endif