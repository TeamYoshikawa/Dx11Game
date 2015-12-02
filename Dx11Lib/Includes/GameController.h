#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
#include <Windows.h>
#include <memory>
namespace DxController{
	class GameController
	{
	public:

		static bool Create();
		
		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);

		void MouseDown(int& mouseX, int& mouseY);
		void MouseUp(int& mouseX, int& mouseY);

		bool IsMouseDown();
		int GetMousePositionX();
		int GetMousePositionY();

		static GameController* GetPointer();
		static void Shutdown();

	private:
		GameController();
		GameController(const GameController&);
		~GameController();


		void Initialize();

	private:
		bool m_keys[256];

		bool isMouseDown;
		POINT m_MousePosition;

		static GameController* m_controller;
		
	};

}
#endif