#pragma once
#include "Cube.h"
#include "FbxBase.h"
#include "ModelBase.h"
#include <memory>

class CollideBoxOBB
{
public:
	CollideBoxOBB();
	CollideBoxOBB(const CollideBoxOBB&);
	~CollideBoxOBB();

	bool IsCollideBoxOBB(std::shared_ptr<DxModel::Cube>&, std::shared_ptr<DxModel::Cube>&);
	//bool IsCompareLengthOBB(std::shared_ptr<DxModel::Cube>&, std::shared_ptr<DxModel::Cube>&, Dx11Math::Vector3&, Dx11Math::Vector3&);

	bool IsCollideOBB(const std::shared_ptr<DxModel::ModelBase>&, const std::shared_ptr<DxModel::ModelBase>&);
	bool IsCompareLengthOBB(const std::shared_ptr<DxModel::ModelBase>&, const std::shared_ptr<DxModel::ModelBase>&, DxMath::Vector3&, DxMath::Vector3&);
};