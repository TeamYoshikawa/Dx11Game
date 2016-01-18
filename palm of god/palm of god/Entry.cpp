#include <windows.h>
#pragma comment (lib,"Aether.lib")

#include <GameEntry.h>
#include <GameController.h>
#include <ConsoleWindow.h>
#include <GameSceneManager.h>

#include "HirokiScene.h"

using namespace aetherClass;
// エントリーポイントを作成
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT){

	// コンソールウィンドウが表示される
	ConsoleWindow::Create();

	// このクラスがメインループを持っているクラス
	GameEntry* entry = new GameEntry();

	// 独自に作成したフレームオブジェクトのオブジェクトを作成
	GameFrame* frame = new GameFrame();
	// 初期化
	entry->Initialize(false, L"Sample");
	frame->Initialize(*entry->GetWindowHandle());

	// この関数を呼び出すことによって、画面の背景色の変更ができる
	// デフォルトの設定では黒が設定されている
	frame->BackgroundColor(Color(0.3f, 0.4f, 0.2f, 1.0f));
	
	// エントリークラスにメインループに使うFrameオブジェクトを設定
	entry->SetGameFrame(frame);

	// 最初のシーンのオブジェクトを作成
	GameScene* firstScene = new HirokiScene();

	// 最初のシーンの設定
	GameSceneManager::SetCurrentScene(firstScene);

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
	ConsoleWindow::Close();
	return 0;
}