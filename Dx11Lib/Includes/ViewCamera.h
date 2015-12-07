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
		Dx11Math::Vector3& Rotation();
		void Rotation(Dx11Math::Vector3 transform);
		Dx11Math::Vector3& Translation();
		void Translation(Dx11Math::Vector3 transform);
		Dx11Math::Vector3& LookUp();
		void LookUp(Dx11Math::Vector3 transform);
		Dx11Math::Vector3& LookAt();
		void LookAt(Dx11Math::Vector3 transform);


		void Render();
		void GetViewMatrix(D3DXMATRIX&);

	private:
		Dx11Math::Vector3 m_translation;		//Camera's position in world
		Dx11Math::Vector3 m_rotation;		//Camera's rotation in world
		Dx11Math::Vector3 m_lookUp;			//Camera's Upper space on view
		Dx11Math::Vector3 m_lookAt;			//Camera's LookAt position, default z(1.0)

		D3DXMATRIX m_viewMatrix;
	};


}

#endif