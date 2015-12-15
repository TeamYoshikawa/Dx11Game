#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
#define DIRECTINPUT_VERSION 0x0800
/*
入力制御クラス

制作者　湯川　計。
*/
#include <Windows.h>
#include <memory>
#include<dinput.h>
#include "Direct3DManager.h"
#include "ViewCamera.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

namespace DxController{
	class GameController
	{
	private:
		struct DXMOUSE3D
		{
			int _x;
			int _y;
			int _z;
		};

	public:
		static bool Create(HINSTANCE, HWND);

		static GameController* GetPointer();
		static void Shutdown();

		bool Frame();

		bool IsLeftButtonDown();
		bool IsRightButtonDown();
		bool IsWheelDown();

		bool IsLeftButtonTrigger();
		bool IsRightButtonTrigger();
		bool IsWheelTrigger();

		bool IsKeyDown(unsigned int);

		float GetMouseX();
		float GetMouseY();
		DxMath::Vector3 GetMouseDirection();

		HWND GetWindowHandle();
		static void CopyManagerAddress(Dx11::Direct3DManager*);

		void Intersection(int, int);
		void SetCamera(DxCamera::ViewCamera*);
	private:
		GameController();
		GameController(const GameController&);
		~GameController();

		bool Initialize(HINSTANCE&, HWND&);
		bool ReadKeybord();
		bool ReadMouse();
		void ProcessInput();

	private:
		HWND m_hWnd;
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_keybord;
		IDirectInputDevice8* m_mouse;

		DIMOUSESTATE m_mouseState;
		int m_mouseX, m_mouseY;
		POINT m_MousePos;
		DxMath::Vector3 m_mouseDirection;


		int m_screenWidth, m_screenHeight;

		unsigned char m_keybordState[256];

		static GameController* m_controller;
		static Dx11::Direct3DManager* m_direct3d;

		DxCamera::ViewCamera* m_camera;
	};

}
#endif