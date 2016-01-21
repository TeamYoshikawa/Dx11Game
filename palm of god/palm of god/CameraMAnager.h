#ifndef _CAMERAMANAGER_H
#define _CAMERAMANAGER_H
#include <d3d11.h>
#include <D3DX11.h>
#include <D3D10.h>
#include <D3DX10.h>
#include <ViewCamera.h>
#include <memory>
#include <Vector3.h>
#include <vector>

#include <GameController.h>

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

		void NextCameraSet();
		
	private:
	    
		std::shared_ptr<DxCamera::ViewCamera> m_camera;
		int m_cameraID;
		static CameraPropaty m_propaty[];
};

#endif