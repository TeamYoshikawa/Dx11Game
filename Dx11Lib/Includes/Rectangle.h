#ifndef _Rectangle_H
#define _Rectangle_H
#pragma once

#include "ModelBase.h"

namespace DxModel{

	class Rectangle :
		public DxModel::ModelBase
	{
	private:
		bool InitializeBuffers() override;
		void ShutdownBuffers() override;
		void RenderBuffers() override;
	protected:
	public:
		Rectangle();
		Rectangle(const Rectangle&);
		~Rectangle();
	};
}
#endif
