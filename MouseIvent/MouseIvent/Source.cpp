// ************************************
// マウスのイベント処理
// ************************************
#define STRICT

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// シンボル定義及びマクロ
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

//文字列描画用配列
TCHAR   szstr[256] = _T("ボタンを押していません");

//ポイント構造体
POINT  pt = { 5, 5 };

//  インスタンス（グローバル変数）
HINSTANCE hInst;

//  ウィンドウプロシージャのコールバック関数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	static TCHAR szWindowClass[] = _T("Sample");
	static TCHAR szTitle[] = _T("マウスイベント処理");

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("RegisterClassExの処理に失敗"),
			_T("Sample"),
			NULL);

		return 1;
	}

	hInst = hInstance; // グローバル変数に値を入れる

	// The parameters to CreateWindow explained:
	// szWindowClass                : アプリケーションの名前
	// szTitle                      : タイトルバーに現れる文字列
	// WS_OVERLAPPEDWINDOW          : 生成するウィンドウのタイプ
	// CW_USEDEFAULT, CW_USEDEFAULT : 最初に置くポジション (x, y)
	// WINDOW_WIDTH, WINDOW_HEIGHT  : 最初のサイズ (幅, 高さ)
	// NULL                         : このウィンドウの親ウィンドウのハンドル
	// NULL                         : メニューバー（このサンプルでは使用せず）
	// hInstance                    : WinMain関数の最初のパラメータ
	// NULL                         : WM_CREATE情報（このアプリケーションでは使用せず）
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	//  ウィンドウが生成できなかった場合
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("ウィンドウ生成に失敗"),
			_T("Sample05"),
			NULL);
		return 1;
	}

	// ウィンドウの表示に必要なパラメータ:
	// hWnd     : CreateWindowの戻り値
	// nCmdShow : WinMainの引数の4番目
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// メインのメッセージループ:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

//  ウィンドウプロシージャ（メッセージに対するコールバック関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_PAINT:
		//  描画処理の開始
		hdc = BeginPaint(hWnd, &ps);
		// 文字列の出力。
		TextOut(hdc,
			pt.x, pt.y,
			szstr, _tcslen(szstr));
		//  ペイント処理の終了
		EndPaint(hWnd, &ps);
		break;
		//キーを押した
		return 0;
		//左クリック
	case WM_LBUTTONDOWN:
		//処理
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		InvalidateRect(hWnd, NULL, TRUE); //座標をとる
		break;
	case WM_LBUTTONUP:
		break;
	case WM_LBUTTONDBLCLK:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_RBUTTONDBLCLK:
		break;
	case WM_MBUTTONDOWN:
		break;
	case WM_MBUTTONUP:
		break;
	case WM_MBUTTONDBLCLK:
		break;
	case WM_MOUSEMOVE:
		_stprintf_s(szstr, _T("座標（%d,%d)"), LOWORD(lParam), HIWORD(lParam));
		//再描画メッセージを発生させる
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
		break;
		//キーを押した
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//終了メッセージを発生させる
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}