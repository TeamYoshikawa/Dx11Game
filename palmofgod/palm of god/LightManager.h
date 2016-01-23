#ifndef _LIGHTMANAGER_H
#define _LIGHTMANAGER_H

#include <memory>
#include <Light.h>
#include <MaterialShader.h>
#include <ViewCamera.h>
#include <GameController.h>

class LightManager
{
	struct LightPropaty
	{
		aetherClass::Vector3 m_changeLightTranslationArray;
	};

    public:
		LightManager();
		~LightManager();

		void Initialize();
		void Render();
		void ChangeLight(int);
		void Update();
		std::shared_ptr<aetherClass::Light> GetLight();

		void NextLightSet();
		//void SetCamera(std::shared_ptr<aetherClass::ViewCamera>);
    private:

		std::shared_ptr<aetherClass::Light> m_light;
		std::shared_ptr<aetherClass::MaterialShader> m_materialShader;
		std::shared_ptr<aetherClass::ViewCamera> m_camera;
		int m_lightID;
		static LightPropaty m_lightpropaty[];
};

#endif