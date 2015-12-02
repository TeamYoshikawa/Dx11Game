#ifndef _CAMERA_H
#define _CAMERA_H

#include <D3DX10math.h>

namespace DxCamera{
	class ViewCamera
	{
	public:
		ViewCamera();
		ViewCamera(const ViewCamera&);
		~ViewCamera();

		void Translation(D3DXVECTOR3);
		void Rotation(D3DXVECTOR3);
		void LookUp(D3DXVECTOR3);



		D3DXVECTOR3 GetPosition();
		D3DXVECTOR3 GetRotation();

		void Render();
		void GetViewMatrix(D3DXMATRIX&);

		void SetPosition(float x, float y, float z);
	private:
		D3DXVECTOR3 m_position;		//Camera's position in world
		D3DXVECTOR3 m_rotation;		//Camera's rotation in world
		D3DXVECTOR3 m_lookup;		//Camera's Up in view

		D3DXMATRIX m_viewMatrix;
	};


}

#endif