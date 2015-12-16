#include "Gamescontroller.h"
#include <iostream>

namespace Gamescontroller{

	Gamescontroller* Gamescontroller::m_controller = nullptr;
	Dx11::Direct3DManager* Gamescontroller::m_direct3d = nullptr;

	Gamescontroller::Gamescontroller()
	{
		m_directInput = 0;
		m_keybord = 0;
		m_mouse = 0;
	}

	Gamescontroller::Gamescontroller(const Gamescontroller& other){}

	Gamescontroller::~Gamescontroller(){}

	bool Gamescontroller::Create(HINSTANCE hInstance, HWND hWnd){
		if (m_controller)
		{
			return true;
		}

		m_controller = new Gamescontroller;
		if (!m_controller)
		{
			return false;
		}
		m_controller->Initialize(hInstance, hWnd);
		return true;
	}

	bool Gamescontroller::Initialize(HINSTANCE& hInstance, HWND& hWnd){

		HRESULT result;

		m_hWnd = hWnd;
		//m_screenWidth = screenWidth;
		//m_screenHeight = screenHeight;

		m_mouseX = 0;
		m_mouseY = 0;
		m_screenWidth = 800;
		m_screenHeight = 600;

		result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
		if (FAILED(result)){ return false; }
		result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keybord, NULL);
		if (FAILED(result)){ return false; }
		result = m_keybord->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result)){ return false; }
		result = m_keybord->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result)){ return false; }
		result = m_keybord->Acquire();
		if (FAILED(result)){ return false; }
		result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		if (FAILED(result)){ return false; }
		result = m_mouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result)){ return false; }
		result = m_mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result)){ return false; }
		result = m_mouse->Acquire();
		if (FAILED(result)){ return false; }
		return true;
	}

	bool Gamescontroller::Frame()
	{
		bool result;

		result = ReadKeybord();
		if (!result)
		{
			return false;
		}

		result = ReadMouse();
		if (!result)
		{
			return false;
		}
		ProcessInput();

		GetCursorPos(&m_MousePos);
		ScreenToClient(m_hWnd, &m_MousePos);

		return true;
	}


	bool Gamescontroller::ReadKeybord()
	{
		HRESULT result;

		result = m_keybord->GetDeviceState(sizeof(m_keybordState), (LPVOID)&m_keybordState);
		if (FAILED(result))
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				m_keybord->Acquire();
			}
			else
			{
				return false;
			}
		}

		return true;
	}


	bool Gamescontroller::ReadMouse()
	{
		HRESULT result;

		result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
		if (FAILED(result))
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				m_mouse->Acquire();
			}
			else
			{
				return false;
			}
		}
		return true;
	}


	void Gamescontroller::ProcessInput()
	{
		m_mouseX += m_mouseState.lX;
		m_mouseY += m_mouseState.lY;

		if (m_mouseX < 0){ m_mouseX = 0; }
		if (m_mouseY < 0){ m_mouseY = 0; }

		if (m_mouseX > m_screenWidth){ m_mouseX = m_screenWidth; }
		if (m_mouseY > m_screenHeight){ m_mouseY = m_screenHeight; }

		return;
	}

	Gamescontroller* Gamescontroller::GetPointer(){
		return m_controller;
	}

	void Gamescontroller::Shutdown(){
		if (!m_controller)
		{
			return;
		}

		if (m_controller->m_mouse)
		{
			m_controller->m_mouse->Unacquire();
			m_controller->m_mouse->Release();
			m_controller->m_mouse = 0;
		}

		if (m_controller->m_keybord)
		{
			m_controller->m_keybord->Unacquire();
			m_controller->m_keybord->Release();
			m_controller->m_keybord = 0;
		}

		if (m_controller->m_directInput)
		{
			m_controller->m_directInput->Release();
			m_controller->m_directInput = 0;
		}

		delete m_controller;
		m_controller = nullptr;

		return;
	}

	bool Gamescontroller::IsLeftButtonDown()
	{
		if (m_mouseState.rgbButtons[0] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool Gamescontroller::IsRightButtonDown()
	{
		if (m_mouseState.rgbButtons[1] & 0x80)
		{
			return true;
		}
		return false;
	}


	bool Gamescontroller::IsWheelDown()
	{
		if (m_mouseState.rgbButtons[2] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool Gamescontroller::IsLeftButtonTrigger()
	{
		static bool prevState[sizeof(m_mouseState.rgbButtons) / sizeof(m_mouseState.rgbButtons[0])];
		bool current = m_mouseState.rgbButtons[0] & 0x80;
		bool ret = current && !prevState[0];
		prevState[0] = current;

		return ret;
	}

	bool Gamescontroller::IsRightButtonTrigger()
	{
		static bool prevState[sizeof(m_mouseState.rgbButtons) / sizeof(m_mouseState.rgbButtons[1])];
		bool current = m_mouseState.rgbButtons[1] & 0x80;
		bool ret = current && !prevState[1];
		prevState[1] = current;

		return ret;
	}

	bool Gamescontroller::IsWheelTrigger()
	{
		static bool prevState[sizeof(m_mouseState.rgbButtons) / sizeof(m_mouseState.rgbButtons[2])];
		bool current = m_mouseState.rgbButtons[2] & 0x80;
		bool ret = current && !prevState[2];
		prevState[2] = current;

		return ret;
	}

	bool Gamescontroller::IsKeyDown(unsigned int buffer)
	{
		if (m_keybordState[buffer] & 0x80)
		{
			return true;
		}
		return false;
	}

	float Gamescontroller::GetMouseX()
	{
		return m_MousePos.x;
	}


	float Gamescontroller::GetMouseY()
	{
		return m_MousePos.y;
	}

	DxMath::Vector3 Gamescontroller::GetMouseDirection()
	{
		return m_mouseDirection;
	}

	HWND Gamescontroller::GetWindowHandle()
	{
		return m_hWnd;
	}

	void Gamescontroller::CopyManagerAddress(Dx11::Direct3DManager* d3d){
		// ƒAƒhƒŒƒX‚Ì‘ã“ü
		m_direct3d = d3d;
		return;
	}

	void Gamescontroller::Intersection(DxMath::Vector3& Rayorigin, DxMath::Vector3& Raydirection)
	{
		float pointX, pointY;
		D3DXMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
		DxMath::Vector3 direction, origin;
		D3DXVECTOR3 rayOrigin, rayDirection;

		pointX = ((2.0f*(float)m_MousePos.x) / (float)m_screenWidth) - 1.0f;
		pointY = (((2.0f*(float)m_MousePos.y) / (float)m_screenHeight) - 1.0f)*-1.0f;



		m_direct3d->GetProjectionMatrix(projectionMatrix);
		pointX = pointX / projectionMatrix._11;
		pointY = pointY / projectionMatrix._22;


		m_camera->GetViewMatrix(viewMatrix);
		D3DXMatrixInverse(&inverseViewMatrix, NULL, &viewMatrix);

		direction._x = (pointX * inverseViewMatrix._11) + (pointY * inverseViewMatrix._21) + inverseViewMatrix._31;
		direction._y = (pointX * inverseViewMatrix._12) + (pointY * inverseViewMatrix._22) + inverseViewMatrix._32;
		direction._z = (pointX * inverseViewMatrix._13) + (pointY * inverseViewMatrix._23) + inverseViewMatrix._33;


		origin = m_camera->Translation();

//		m_direct3d->GetWorldMatrix(worldMatrix);
		D3DXMatrixTranslation(&translateMatrix, origin._x,origin._y,origin._z);
//		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

		D3DXMatrixInverse(&inverseWorldMatrix, NULL, &translateMatrix);
		
		D3DXVECTOR3 d3drayOrigin;
		D3DXVECTOR3 d3dOrigin;
		d3dOrigin.x = origin._x;
		d3dOrigin.y = origin._y;
		d3dOrigin.z = origin._z;

		D3DXVECTOR3 d3dDirection;
		d3dDirection.x = direction._x;
		d3dDirection.y = direction._y;
		d3dDirection.z = direction._z;


//		D3DXVec3TransformCoord(&rayOrigin, &d3dOrigin, &inverseWorldMatrix);
		D3DXVec3TransformNormal(&rayDirection, &d3dDirection, &inverseWorldMatrix);


		D3DXVec3Normalize(&rayDirection, &rayDirection);

		Rayorigin = d3dOrigin;
		Raydirection = rayDirection;

		//std::cout << RaySphereIntersect(rayOrigin, rayDirection, 10.0f) << std::endl;
		//std::cout << rayDirection.x << std::endl;

		//m_mouseDirection = direction;
		//m_mouseDirection._x = rayOrigin.x;
		//m_mouseDirection._y = rayOrigin.y;
		//m_mouseDirection._x = rayOrigin.z;
	}

	void Gamescontroller::SetCamera(DxCamera::ViewCamera* camera)
	{
		m_camera = &(*camera);
	}
}