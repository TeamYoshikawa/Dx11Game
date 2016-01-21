#ifndef _Rock_H
#define _Rock_H

#include "Cube.h"

namespace n_Rock{
	class Rock :
		public aetherClass::Cube
	{
	public:
		Rock() = default;
		Rock(const Rock&) = default;
		~Rock() = default;

		/*
	private:
		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void RenderBuffers()override;
		*/
	};
}
#endif