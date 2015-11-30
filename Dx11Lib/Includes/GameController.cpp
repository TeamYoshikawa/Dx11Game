#include "GameController.h"


namespace DxController{

	GameController* GameController::m_controller = nullptr;

	GameController::GameController(){}

	GameController::GameController(const GameController& other){}

	GameController::~GameController(){}

	bool GameController::Create(){
		if (m_controller) 
		{
			return true;
		}

		m_controller = new GameController;
		if (!m_controller)
		{
			return false;
		}
		m_controller->Initialize();
		return true;
	}

	void GameController::Initialize(){

		// Initialize all the keys to
		for (int i = 0; i < 256; i++)
		{
			m_keys[i] = false;
		}

		SecureZeroMemory(&m_MousePosition, sizeof(POINT));
		return;
	}


	void GameController::KeyDown(unsigned int input){
		// If a key is pressed then save that state in the key array
		m_keys[input] = true;

		return;
	}

	void GameController::KeyUp(unsigned int input){
		// If a key is released then save that state in the key array
		m_keys[input] = false;
		return;
	}

	bool GameController::IsKeyDown(unsigned int key){
		// Return what state the key is in (pressed/not pressed)
		return m_keys[key];
	}

	void GameController::MouseDown(int& mouseX, int& mouseY)
	{
		isMouseDown = true;
		m_MousePosition = { mouseX, mouseY };
	}

	void GameController::MouseUp(int& mouseX, int& mouseY)
	{
		isMouseDown = false;
	}

	bool GameController::IsMouseDown()
	{
		return isMouseDown;
	}

	int GameController::GetMousePositionX()
	{
		return static_cast<int>(m_MousePosition.x);
	}

	int GameController::GetMousePositionY()
	{
		return static_cast<int>(m_MousePosition.y);
	}

	GameController* GameController::GetPointer(){
		return m_controller;
	}

	void GameController::Shutdown(){
		if (!m_controller)
		{
			return;
		}
		m_controller->Initialize();
		delete m_controller;
		m_controller = nullptr;
		return;
	}
}