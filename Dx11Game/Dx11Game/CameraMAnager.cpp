#include "CameraMAnager.h"

#include <iostream>
CameraManager::CameraPropaty CameraManager::m_propaty[] = {
	{ DxMath::Vector3(575, -442, 447), DxMath::Vector3(-160.0f, 48.0f, 1.0f) },
	{ DxMath::Vector3(-580, -282, 450), DxMath::Vector3(-170.0f, -60.0f, 1.0f) },
	{ DxMath::Vector3(2986, -460, -360), DxMath::Vector3(-160.0f, 115.0f, 1.0f) },
	{ DxMath::Vector3(-500, -446, 446), DxMath::Vector3(160.0f, 70.0f, 1.0f) }
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
	
}

void CameraManager::Render()
{
	m_camera->Render();
}

void CameraManager::ChangeCamera(int id)
{
	m_camera->Translation(m_propaty[id].m_changeCameraTranslationArray);
	m_camera->Rotation(m_propaty[id].m_changeCameraRotationArray);
}

std::shared_ptr<DxCamera::ViewCamera>& CameraManager::GetCamera(){
	return m_camera;

}