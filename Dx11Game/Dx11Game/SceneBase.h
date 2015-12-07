#ifndef _SCENEBASE_H
#define _SCENEBASE_H
#include <string>
#include <iostream>
#include <Windows.h>
#include "SceneManager.h"

#include <FbxStaticMesh.h>
class SceneBase
{
	
	public:
		SceneBase(const std::string &name,SceneManager& manager):
		m_sceneName(name),
		m_manager(manager){
			m_afterSceneName = "null";
			m_isChange = false;
		}

		virtual ~SceneBase() = default;
		
		virtual void Initialize(Dx11::Direct3DManager*, HWND) = 0;
		virtual void Updata() = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;
		
		const std::string GetName(){ return m_sceneName; }
		const std::string GetChangeAfterSceneName(){ return m_afterSceneName; }
		bool IsChange()const{ return m_isChange; }

	protected:
		SceneManager& m_manager;
		void SetChangeScene(const bool flg,std::string afterSceneName){ 
			m_isChange = flg; 
			m_afterSceneName = afterSceneName;
		}
		

	private:
		const std::string m_sceneName;
		std::string m_afterSceneName;
		bool m_isChange;
	
};

#endif