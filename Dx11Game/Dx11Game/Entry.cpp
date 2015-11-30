/*

エントリーポイント
プログラムが始まるとこ

*/

#include "System.h"
#include <iostream>
//	コンソール表示用
#include <io.h>
#include <fcntl.h>
#pragma comment (lib,"Dx11FrameWork.lib")
// コンソール画面ハンドル保存用
int hConsole = 0;

///
// コンソール画面作成用
void CreateConsoleWindow(){

	::AllocConsole();
	hConsole = ::_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	*stdout = *::_fdopen(hConsole, "w");
	setvbuf(stdout, NULL, _IONBF, 0);

}

///
// コンソール画面終了用
void CloseConsoleWindow(){
	::_close(hConsole);
}
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow){

	std::unique_ptr<System> system = nullptr;
	bool result = false;

	system = std::make_unique<System>();
	if (!system)
	{
		std::cout << "Error: Coould not created System object" << std::endl;
		std::cout << "File: Entry.cpp 39 lines" << std::endl;
		return -1;
	}

	CreateConsoleWindow();
	result = system->Initialize();

	if (result)
	{
		std::cout << "Start system run" << std::endl;
		system->Run();
	}

	CloseConsoleWindow();

	system->Shutdown();
	system.release();
	system = nullptr;

	return 0;
}