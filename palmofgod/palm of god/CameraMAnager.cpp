#include "CameraMAnager.h"

#include <iostream>
using namespace aetherClass;
CameraManager::CameraPropaty CameraManager::m_propaty[] = {
	{ Vector3(575, -442, 447), Vector3(-160.0f, 48.0f, 1.0f) },
	{ Vector3(-580, -282, 450), Vector3(-170.0f, -60.0f, 1.0f) },
	{ Vector3(2968, -460, -360), Vector3(-160.0f, 115.0f, 1.0f) },
	{ Vector3(2176, -212, -426), Vector3(-180.0f, 200.0f, 1.0f) },
	{ Vector3(2480, -416, 2030), Vector3(-166.0f, -16.0f, 1.0f) },
	{ Vector3(2106, -66, 1786), Vector3(-172.0f, 271.0f, 1.0f) },
	{ Vector3(4178, -80, 1786), Vector3(-172.0f, 92.0f, 1.0f) },
	{ Vector3(5362, -232, 1540), Vector3(-180.0f, 107.0f, 1.0f) },
	{ Vector3(5246, -232, 774), Vector3(-160.0f, 206.0f, 1.0f) },
	{ Vector3(8092, -396, 138), Vector3(-170.0f, -284.0f, 1.0f) },
	{ Vector3(8338, -350, 138), Vector3(-170.0f, 70.0f, 1.0f) },
	{ Vector3(8620, -200, -258), Vector3(-174.0f, 117.0f, 1.0f) },
	{ Vector3(8436, -314, -252), Vector3(-174.0f, 180.0f, 1.0f) },
	{ Vector3(8136, -284, 1766), Vector3(-174.0f, -88.0f, 1.0f) }
};

CameraManager::CameraManager()
{
	
}


CameraManager::~CameraManager()
{
}

void CameraManager::Initialize()
{
	m_camera = std::make_shared<ViewCamera>();
	m_camera->Translation() = m_propaty[0].m_changeCameraTranslationArray;
	m_camera->Rotation() = m_propaty[0].m_changeCameraRotationArray;
	m_cameraID = 0;
}

void CameraManager::Render()
{
	m_camera->Translation() = m_propaty[m_cameraID].m_changeCameraTranslationArray;
	m_camera->Rotation() = m_propaty[m_cameraID].m_changeCameraRotationArray;
	m_camera->Render();
}

void CameraManager::ChangeCamera(int id)
{
	m_camera->Translation() = m_propaty[m_cameraID].m_changeCameraTranslationArray;
	m_camera->Rotation() = m_propaty[m_cameraID].m_changeCameraRotationArray;
}

std::shared_ptr<ViewCamera>& CameraManager::GetCamera(){
	return m_camera;

}


void CameraManager::NextCameraSet(){
	m_cameraID += 1;
	int changeMax = sizeof(m_propaty) / sizeof(m_propaty[0]); // Ø‚è‘Ö‚¦‚é—v‘f”‚ÌŽæ“¾
	if (m_cameraID > changeMax)
	{
		m_cameraID = changeMax;
	}
}