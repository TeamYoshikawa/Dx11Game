#pragma once
#include <ModelBase.h>


//origin is x(1.0), Base lib type is Right side.
//
namespace Pitfall{
	class PitFallLib :
		public aetherClass::ModelBase
	{
	public:
		PitFallLib() = default;
		PitFallLib(const PitFallLib&) = default;
		~PitFallLib() = default;

		bool InitializeBuffers()override;
		void FinalizeBuffers()override;
		void RenderBuffers()override;


	};

}
