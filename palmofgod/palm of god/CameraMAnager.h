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
		CameraManager();
		~CameraManager();

		void Initialize();
		void Render();
		void ChangeCamera(int);
		std::shared_ptr<aetherClass::ViewCamera>& GetCamera();

		void NextCameraSet();
		
	private:
	    
		std::shared_ptr<aetherClass::ViewCamera> m_camera;
		int m_cameraID;
		static CameraPropaty m_propaty[];
};

#endif