#include <windows.h>
#pragma comment (lib,"Aether.lib")

#include <GameEntry.h>
#include <GameController.h>
#include <ConsoleWindow.h>
#include <GameSceneManager.h>
#include "SceneTitle.h"
#include "LoadObj.h"


using namespace aetherClass;
// エントリーポイントを作成
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT){

	// コンソールウィンドウが表示される
	//ConsoleWindow::Create();

	// このクラスがメインループを持っているクラス
	GameEntry* entry = new GameEntry();

	// 独自に作成したフレームオブジェクトのオブジェクトを作成
	GameFrame* frame = new GameFrame();

	// 初期化
	entry->Initialize(false, L"Palm of God");
	frame->Initialize(*entry->GetWindowHandle(), POINT{800,600},false,10000000);

	// この関数を呼び出すことによって、画面の背景色の変更ができる
	// デフォルトの設定では黒が設定されている
	frame->BackgroundColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
	
	// エントリークラスにメインループに使うFrameオブジェクトを設定
	entry->SetGameFrame(frame);

	// 最初のシーンのオブジェクトを作成
	GameScene* firstScene = new SceneTitle();


	// 最初のシーンの設定
	GameSceneManager::SetCurrentScene(firstScene);

	// 実行するロードオブジェクトの作成
	LoadScreen *loadobj = new LoadObj;
	GameSceneManager::SetLoadScreen(loadobj);
	// メインループの開始
	// この関数の内部で,GameFrameオブジェクトのFrameRunningが呼ばれる。
	entry->GameRun();

	// フレームオブジェクトの破棄
	delete frame;
	frame = nullptr;

	// エントリーオブジェクトの破棄
	delete entry;
	entry = nullptr;

	// コンソールウィンドウを破棄したいときはこの関数を呼ぶ
	//ConsoleWindow::Close();
	return 0;
}