#include "CameraMAnager.h"

#include <iostream>
using namespace aetherClass;



CameraManager::CameraPropaty CameraManager::m_propaty[] = {
	{ Vector3(902, -208, 900), Vector3(-160.0f, 48.0f, 1.0f) },
	{ Vector3(-170, -138, 890), Vector3(-170.0f, -60.0f, 1.0f) },
	{ Vector3(3096, -188, 328), Vector3(-160.0f, 115.0f, 1.0f) },
	{ Vector3(2374, 100, 316), Vector3(-180.0f, 200.0f, 1.0f) },
	{ Vector3(2558, -180, 2494), Vector3(-166.0f, -16.0f, 1.0f) },
	{ Vector3(2558, -12, 2206), Vector3(-172.0f, 271.0f, 1.0f) },
	{ Vector3(4394, 184, 2218), Vector3(-172.0f, 92.0f, 1.0f) },
	{ Vector3(5294, -106, 1938), Vector3(-180.0f, 107.0f, 1.0f) },
	{ Vector3(5300, -136, 314), Vector3(-182.0f, 206.0f, 1.0f) },
	{ Vector3(9006, -142, 866), Vector3(-170.0f, 70.0f, 1.0f) },
	{ Vector3(9004, -142, 328), Vector3(-170.0f, 117.0f, 1.0f) },
	{ Vector3(8728, -192, 314), Vector3(-174.0f, 180.0f, 1.0f) },
	{ Vector3(8484, -12, 2130), Vector3(-174.0f, -88.0f, 1.0f) }
};

CameraManager::CameraManager()
{
	
}


CameraManager::~CameraManager()
{
}

void CameraManager::Initialize()
{
	m_cameraNumber = NULL;
	m_camera = std::make_shared<ViewCamera>();
	m_cameraID = GetCameraID(m_cameraNumber);
	m_camera->Translation() = m_propaty[m_cameraID].m_changeCameraTranslationArray;
	m_camera->Rotation() = m_propaty[m_cameraID].m_changeCameraRotationArray;
}

void CameraManager::Render()
{
	m_camera->Translation() = m_propaty[m_cameraID].m_changeCameraTranslationArray;
	m_camera->Rotation() = m_propaty[m_cameraID].m_changeCameraRotationArray;
	m_camera->Render();
}

std::shared_ptr<ViewCamera>& CameraManager::GetCamera(){
	return m_camera;

}


void CameraManager::NextCameraSet(){
	m_cameraNumber += 1;
	
	int changeMax = sizeof(m_propaty) / sizeof(m_propaty[0]); // Ø‚è‘Ö‚¦‚é—v‘f”‚Ìæ“¾
	
	// ƒJƒƒ‰‚ÌØ‚è‘Ö‚¦‚ÌŒÀŠE‚ğ’´‚¦‚½‚çƒJƒƒ‰‚ÌŒÀŠE’l‚Å~‚ß‚é
	if (m_cameraNumber > changeMax-1)
	{
		m_cameraNumber = changeMax-1;
	}		

	// ƒJƒƒ‰‚ÌØ‚è‘Ö‚¦‚ÌŒÀŠE‚ª‚«‚Ä‚È‚¯‚ê‚ÎØ‚è‘Ö‚¦‚Ä‚¢‚­B
	m_cameraID = GetCameraID(m_cameraNumber);
	
}

CameraManager::CameraID CameraManager::GetCameraID(int number)
{
	switch (number)
	{
	case 0:
		return CameraID::eID1;
	case 1:
		return CameraID::eID2;
	case 2:
		return CameraID::eID3;
	case 3:
		return CameraID::eID4;
	case 4:
		return CameraID::eID5;
	case 5:
		return CameraID::eID6;
	case 6:
		return CameraID::eID7;
	case 7:
		return CameraID::eID8;
	case 8:
		return CameraID::eID9;
	case 9:
		return CameraID::eID10;
	case 10:
		return CameraID::eID11;
	case 11:
		return CameraID::eID12;
	case 12:
		return CameraID::eID13;
	case 13:
		return CameraID::eID14;
	case 15:
		return CameraID::eID15;
	default:
		return CameraID::eNULL;
	}
}