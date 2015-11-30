#include "GameFrame.h"
#include "SceneGame.h"
#include <iostream>

GameFrame::GameFrame()
{
	m_d3d11Manager = nullptr;
	m_sceneManager = nullptr;
}

GameFrame::GameFrame(GameFrame& other){

}

GameFrame::~GameFrame()
{
	m_d3d11Manager = nullptr;
	m_sceneManager = nullptr;
}

bool GameFrame::Initialize(POINT screen, HWND hWnd){
	bool result;

	m_d3d11Manager = std::make_shared<Dx11::Direct3DManager>();
	if (!m_d3d11Manager)
	{
		return false;
	}

	result = m_d3d11Manager->Initialize(screen, kVsyncEnabled, hWnd, kFullScreen, kScreenDepth, kScreenNear);
	if (!result)
	{
		return false;
	}

	m_sceneManager = std::make_unique<SceneManager>();
	if (!m_sceneManager)
	{
		return false;
	}

	result = m_sceneManager->Initialize();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GameFrame::Updatar(){
	bool result;

	result = m_sceneManager->SceneRender();
	if (!result)
	{
		MessageBox(NULL, L"Do not Render", L"Error", MB_OK);
	}

	result = m_sceneManager->SceneUpdatar();
	if (!result)
	{
		MessageBox(NULL, L"Do not Updater", L"Error", MB_OK);
	}

	return true;
}

void GameFrame::Shutdown(){
	if (m_d3d11Manager)
	{
		m_d3d11Manager->Shutdown();
		m_d3d11Manager.reset();
		m_d3d11Manager = nullptr;
	}

	if (m_sceneManager)
	{
		m_sceneManager->Shutdown();
		m_sceneManager.release();
		m_sceneManager = nullptr;
	}
	return;
}