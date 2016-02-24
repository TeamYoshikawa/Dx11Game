#ifndef _CAMERAMANAGER_H
#define _CAMERAMANAGER_H

#include <ViewCamera.h>
#include <memory>
#include <Vector3.h>
#include <vector>

#include <GameController.h>

class CameraManager
{


	struct CameraPropaty
	{
		aetherClass::Vector3 m_changeCameraTranslationArray;
		aetherClass::Vector3 m_changeCameraRotationArray;

	};

public:

	// ƒJƒƒ‰‚ÌID
	enum CameraID{
		eID1 = 0,
		eID2,
		eID3,
		eID4,
		eID5,
		eID6,
		eID7,
		eID8,
		eID9,
		eID10,
		eID11,
		eID12,
		eID13,
		eID14,
		eID15,
		eNULL
	};

	CameraManager();
	~CameraManager();

	void Initialize();
	void Render();
	std::shared_ptr<aetherClass::ViewCamera>& GetCamera();

	void NextCameraSet();

	// ƒJƒƒ‰IDæ“¾—p
	CameraID GetNowID();
private:
	CameraID m_cameraID;
	std::shared_ptr<aetherClass::ViewCamera> m_camera;
	int m_cameraNumber;
	CameraID GetCameraID(int);
	static CameraPropaty m_propaty[];

};

#endif