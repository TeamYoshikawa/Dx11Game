#pragma once
#include "ModelBase.h"
namespace DxModel{
	class Circle :
		public ModelBase
	{
	private:
		float m_slice;	//Vertex slice set;
	public:
		Circle();
		Circle(const Circle&);
		Circle(float);
		~Circle() = default;

		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void RenderBuffers()override;


	};
}
