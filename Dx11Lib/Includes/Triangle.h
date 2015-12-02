#pragma once
#include "ModelBase.h"

namespace DxModel{
	class Triangle :
		public ModelBase
	{
		public:
			Triangle();
			Triangle(Triangle&);
			~Triangle();

		private:
			bool InitializeBuffers()override;
			void ShutdownBuffers()override;
			void RenderBuffers()override;
	};
}
