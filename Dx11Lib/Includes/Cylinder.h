#pragma once
#include "ModelBase.h"

namespace DxModel{
	class Cylinder :
		public ModelBase
	{
		float m_slice;
	public:
		Cylinder();
		Cylinder(float);
		Cylinder(const Cylinder&);
		~Cylinder() = default;

		bool InitializeBuffers() override;
		void ShutdownBuffers() override;
		void RenderBuffers() override;


	};

}