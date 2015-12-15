#ifndef _CAMERAMANAGER_H
#define _CAMERAMANAGER_H
#include <ViewCamera.h>
#include <memory>
#include <Vector3.h>
#include <vector>
	

class CameraManager
{
	

	struct CameraPropaty
	{
	     DxMath::Vector3 m_changeCameraTranslationArray;
		 DxMath::Vector3 m_changeCameraRotationArray;

	};

	public:
		CameraManager();
		~CameraManager();

		void Initialize();
		void Render();
		void ChangeCamera(int);
		std::shared_ptr<DxCamera::ViewCamera>& GetCamera();
		
	private:
	    
		std::shared_ptr<DxCamera::ViewCamera> m_camera;
		
		static CameraPropaty m_propaty[];
};

#endif