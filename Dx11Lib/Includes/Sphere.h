#pragma once
#include "ModelBase.h"
namespace DxModel
{
	class Sphere :
		public ModelBase
	{
	public:
		Sphere();
		Sphere(const Sphere&);
		~Sphere();

	private:
		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void RenderBuffers()override;
	};
}


