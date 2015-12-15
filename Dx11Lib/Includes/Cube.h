#ifndef _CUBE_H
#define _CUBE_H
#include "ModelBase.h"
namespace DxModel{
	class Cube :
		public ModelBase
	{
		public:
			Cube();
			Cube(const Cube&);
			~Cube();

		private:
			bool InitializeBuffers()override;
			void ShutdownBuffers()override;
			void RenderBuffers()override;
	};
}

#endif