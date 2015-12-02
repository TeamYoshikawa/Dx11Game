#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
#include <memory>
#include <unordered_map>
#include <Direct3DManager.h>
class SceneBase;

class SceneManager
{
	public:
		SceneManager();
		SceneManager(SceneManager&);
		~SceneManager();

		bool Initialize(Dx11::Direct3DManager*,HWND&);
		
		bool SceneUpdatar();
		bool SceneRender();
		void SceneChanger(std::string);
		void SceneShutdown();

		void Shutdown();

	private:
		enum class eGameState{
			eNone,
			eInitialize,
			eUpData,
			eRender,
			eShutdown,
			eChangeScene,
		};
	private:
		void Register(const std::shared_ptr<SceneBase>);
		std::shared_ptr<SceneBase> FindScene(std::string);
		void SceneInitialize();
	private:
		static std::unordered_map<std::string, std::shared_ptr<SceneBase>> m_scenesMap;
		static std::shared_ptr<SceneBase> m_currentScene;
		static eGameState m_gameState;
		HWND* m_hWnd;
		Dx11::Direct3DManager* m_direct3d;
};

#endif