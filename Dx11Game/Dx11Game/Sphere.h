#pragma once
#include "ModelBase.h"
namespace DxModel
{
	class Sphere :
		public ModelBase
	{
	private:
		struct Model
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
		};

		Model* m_model;
	public:
		Sphere();
		Sphere(const Sphere&);
		~Sphere();
		bool RayIntersect(DxMath::Vector3 origin, DxMath::Vector3 direction, float scalar);

	private:
		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void RenderBuffers()override;
		bool LoadFile(char*);
	};
}


