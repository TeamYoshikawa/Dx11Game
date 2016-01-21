#include "CameraMAnager.h"

#include <iostream>
CameraManager::CameraPropaty CameraManager::m_propaty[] = {
	{ DxMath::Vector3(575, -442, 447), DxMath::Vector3(-160.0f, 48.0f, 1.0f) },
	{ DxMath::Vector3(-580, -282, 450), DxMath::Vector3(-170.0f, -60.0f, 1.0f) },
	{ DxMath::Vector3(2968, -460, -360), DxMath::Vector3(-160.0f, 115.0f, 1.0f) },
	{ DxMath::Vector3(2176, -212, -426), DxMath::Vector3(-180.0f, 200.0f, 1.0f) }
};

CameraManager::CameraManager()
{
	
}


CameraManager::~CameraManager()
{
}

void CameraManager::Initialize()
{
	m_camera = std::make_shared<DxCamera::ViewCamera>();
	m_camera->Translation(m_propaty[0].m_changeCameraTranslationArray);
	m_camera->Rotation(m_propaty[0].m_changeCameraRotationArray);
	m_cameraID = 0;
}

void CameraManager::Render()
{
	m_camera->Translation(m_propaty[m_cameraID].m_changeCameraTranslationArray);
	m_camera->Rotation(m_propaty[m_cameraID].m_changeCameraRotationArray);
	m_camera->Render();
}

void CameraManager::ChangeCamera(int id)
{
	m_camera->Translation(m_propaty[m_cameraID].m_changeCameraTranslationArray);
	m_camera->Rotation(m_propaty[m_cameraID].m_changeCameraRotationArray);
}

std::shared_ptr<DxCamera::ViewCamera>& CameraManager::GetCamera(){
	return m_camera;

}


void CameraManager::NextCameraSet(){
	m_cameraID += 1;
	if (m_cameraID > 3)
	{
		m_cameraID = 3;
	}
}