#pragma once
#include "ModelBase.h"


//origin is x(1.0), Base lib type is Right side.
//
namespace Pitfall{
	class PitFallLib :
		public DxModel::ModelBase
	{
	public:
		PitFallLib() = default;
		PitFallLib(const PitFallLib&) = default;
		~PitFallLib() = default;

		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void RenderBuffers()override;


	};

}
