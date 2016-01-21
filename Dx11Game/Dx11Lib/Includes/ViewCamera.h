#ifndef _CAMERA_H
#define _CAMERA_H

#include <D3DX10math.h>
#include"Vector3.h"
namespace DxCamera{
	class ViewCamera
	{
	public:
		ViewCamera();
		ViewCamera(const ViewCamera&);
		~ViewCamera() = default;
		

		//Accessor Methods
		DxMath::Vector3& Rotation();
		void Rotation(DxMath::Vector3 transform);
		DxMath::Vector3& Translation();
		void Translation(DxMath::Vector3 transform);
		DxMath::Vector3& LookUp();
		void LookUp(DxMath::Vector3 transform);
		DxMath::Vector3& LookAt();
		void LookAt(DxMath::Vector3 transform);


		void Render();
		void GetViewMatrix(D3DXMATRIX&);

	private:
		DxMath::Vector3 m_translation;		//Camera's position in world
		DxMath::Vector3 m_rotation;		//Camera's rotation in world
		DxMath::Vector3 m_lookUp;			//Camera's Upper space on view
		DxMath::Vector3 m_lookAt;			//Camera's LookAt position, default z(1.0)

		D3DXMATRIX m_viewMatrix;
	};


}

#endif