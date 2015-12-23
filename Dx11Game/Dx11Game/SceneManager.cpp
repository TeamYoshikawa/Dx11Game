#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGame.h"

std::unordered_map<std::string, std::shared_ptr<SceneBase>> SceneManager::m_scenesMap;
std::shared_ptr<SceneBase> SceneManager::m_currentScene = nullptr;

SceneManager::eGameState SceneManager::m_gameState = SceneManager::eGameState::eNone;

SceneManager::SceneManager(){}
SceneManager::SceneManager(SceneManager& other){}
SceneManager::~SceneManager(){}

bool SceneManager::Initialize(Dx11::Direct3DManager* manager,HWND& hWnd){

	m_direct3d = &(*manager);
	m_hWnd = &hWnd;
	//　シーンが増えてくごとに追加していく
	Register(std::make_shared<SceneTitle>(this));
	Register(std::make_shared<SceneGame>(this));

	m_currentScene = FindScene(SceneGame::m_thisName);
	if (!m_currentScene){

		return false;
	}

	m_gameState = eGameState::eInitialize;
	SceneInitialize();
	return true;
}

void SceneManager::Register(std::shared_ptr<SceneBase> registerScene){
	m_scenesMap.insert(std::make_pair(registerScene->GetName(), registerScene));
}

std::shared_ptr<SceneBase> SceneManager::FindScene(std::string name){
	auto findMap = m_scenesMap.find(name);

	return findMap->second;
}

void SceneManager::SceneInitialize(){
	if (m_gameState != eGameState::eInitialize)
	{
		return;
	}
	m_currentScene->Initialize(m_direct3d,*m_hWnd);

	m_gameState = eGameState::eUpData;
}

bool SceneManager::SceneUpdatar(){
	if (m_gameState != eGameState::eUpData)
	{
		return true;
	}
	m_currentScene->Updata();

	if (m_currentScene->IsChange())
	{
		SceneChanger(m_currentScene->GetChangeAfterSceneName());
	}
	m_gameState = eGameState::eRender;
	return true;
}

bool SceneManager::SceneRender(){
	if (m_gameState != eGameState::eRender)
	{
		return true;
	}

	m_currentScene->Render();
	m_gameState = eGameState::eUpData;
	return true;
}


void SceneManager::SceneShutdown(){
	if (m_gameState != eGameState::eShutdown)
	{
		return;
	}
	m_currentScene->Shutdown();
	return;
}

void SceneManager::Shutdown(){
	m_currentScene.reset();
	m_currentScene = nullptr;

	m_scenesMap.clear();
}


void SceneManager::SceneChanger(std::string nextSceneName){
	std::cout << "Change scene" << std::endl;

	m_gameState = eGameState::eShutdown;
	m_currentScene->Shutdown();

	auto sceneMap = m_scenesMap.find(nextSceneName);
	auto nextScene = sceneMap->second;

	if (!nextScene)
	{
		std::cout << "Not find next scene" << std::endl;
		MessageBox(NULL, L"Not find next scene", L"Error", MB_OK);
		return;
	}

	// TODO: フェードイン・フェードアウト処理 //
	std::cout << "Transition start" << std::endl;

	m_currentScene = nextScene;
	nextScene.reset();
	nextScene = nullptr;

	if (!m_currentScene)
	{
		std::cout << "Not find current scene" << std::endl;
		MessageBox(NULL, L"Not find current scene", L"Error", MB_OK);
		return;
	}

	m_gameState = eGameState::eInitialize;
	SceneInitialize();
	std::cout << "Transition end" << std::endl;


	std::cout << "Changed scene" << std::endl;

	return;
}
