#pragma once
#include "ModelBase.h"
namespace DxModel{
	class Line :
		public ModelBase
	{
	public:
		Line() = default;
		~Line() = default;
		Line(const Line&);

	private:
		bool InitializeBuffers() override;
		void ShutdownBuffers() override;
		void RenderBuffers() override;


	};

}