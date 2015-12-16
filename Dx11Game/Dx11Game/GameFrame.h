#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H
#pragma comment (lib,"Dx11FrameWork.lib")
#include <Direct3DManager.h>
#include <ViewCamera.h>
#include <memory>
#include "SceneManager.h"

// constants
namespace{
	const bool kFullScreen = false;
	const bool kVsyncEnabled = true;
	const float kScreenDepth = 1000000.0f;
	const float kScreenNear = 0.1f;
}


class GameFrame
{

private:
	std::shared_ptr <Dx11::Direct3DManager> m_d3d11Manager;
	std::unique_ptr <SceneManager> m_sceneManager;

public:
	GameFrame();
	GameFrame(GameFrame&);
	~GameFrame();

	bool Initialize(POINT, HWND);

	bool Updatar();

	void Shutdown();

};

#endif