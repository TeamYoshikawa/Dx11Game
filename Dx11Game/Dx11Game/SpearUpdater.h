#pragma once
#ifndef _SPEARUPDATER_H_
#define _SPEARUPDATER_H_

#include"Spear.h"
#include <memory>
#include <ModelBase.h>
#include <FbxStaticMesh.h>

class SpearUpdater
{
private:
	//���̔�яo��
	void ButtonOn(DxModel::Cube*);
	//���̎��[
	void ButtonOff(DxModel::Cube*);

	void operator =(const SpearUpdater &);

public:
	SpearUpdater();
	~SpearUpdater();

	void Updating(DxModel::Cube*, bool buttonState);


};

#endif