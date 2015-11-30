#include "ViewCamera.h"

namespace DxCamera{
	ViewCamera::ViewCamera(){
		ZeroMemory(&m_position, sizeof(m_position));
		ZeroMemory(&m_rotation, sizeof(m_rotation));
		ZeroMemory(&m_lookup, sizeof(m_lookup));
		m_lookup.y = 1.0f;
	}
	ViewCamera::ViewCamera(const ViewCamera&){}
	ViewCamera::~ViewCamera(){}

	void ViewCamera::Translation(D3DXVECTOR3 pos){
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_position.z = pos.z;
	}

	void ViewCamera::Rotation(D3DXVECTOR3 rote){
		m_rotation.x = rote.x;
		m_rotation.y = rote.y;
		m_rotation.z = rote.z;
	}
	void ViewCamera::LookUp(D3DXVECTOR3 lookup){
		m_lookup.x = lookup.x;
		m_lookup.y = lookup.y;
		m_lookup.z = lookup.z;
	}

	D3DXVECTOR3 ViewCamera::GetPosition(){
		return m_position;
	}


	D3DXVECTOR3 ViewCamera::GetRotation(){
		return m_rotation;
	}

	void ViewCamera::SetPosition(float x, float y, float z){
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	void ViewCamera::Render(){
		D3DXVECTOR3 up, position, lookAt;
		float yaw, pitch, roll;
		D3DXMATRIX rotationMatrix;

		// Setup the vector that points upwards
		up.x = m_lookup.x;
		up.y = m_lookup.y;
		up.z = m_lookup.z;

		// Setup the vector that points of the camera in the world
		position.x = m_position.x;
		position.y = m_position.y;
		position.z = m_position.z;

		// Setup where the camera is looking by default
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;

		// Set the yaw(Y axis),pitch(X axis),and roll(Z axis)rotation in randians
		pitch = m_rotation.x*0.0174532925f;
		yaw = m_rotation.y*0.0174532925f;
		roll = m_rotation.z* 0.0174532925f;

		// Create the rotation matrix from the yaw,pitch,and roll values
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

		// Transform the lookAt and up vector by the rotation matrix so the view is correctty rotated at the origin
		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
		D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

		// Translate the rotated camera position to the location of the viewer
		lookAt = position + lookAt;

		// Finally create the view matrix from the three updata vectors
		D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

		return;
	}

	void ViewCamera::GetViewMatrix(D3DXMATRIX& viewMatrix){
		viewMatrix = m_viewMatrix;
		return;
	}


}