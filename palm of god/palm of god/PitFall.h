#ifndef _PITFALL_H
#define _PITFALL_H

#include "ModelBase.h"


/*///////////////////
*	class: PitFall extends ModelBase's and PitFallBased
*	
*////////////////////

namespace Pitfall{
	class PitFall :
		public DxModel::ModelBase
	{
	public:
		PitFall() = default;
		PitFall(const PitFall&) = default;
		~PitFall() = default;

		bool GroundDecision(ModelBase &other);

	private:
		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void RenderBuffers()override;

	};
}

#endif