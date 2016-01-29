#ifndef _PLAYERNAVIGATION_H
#define _PLAYERNAVIGATION_H
#include <memory>
#include <Cube.h>
#include <Vector3.h>
#include <ViewCamera.h>
/*
	�v���C���[�����ɒʂ铹���ē����邽�߂̃{�b�N�X��z�u����N���X


*/
class PlayerNavigation
{
	public:
		PlayerNavigation();
		~PlayerNavigation();

		void Initialize(std::shared_ptr<aetherClass::ViewCamera>);

		std::shared_ptr<aetherClass::Cube> GetNavigationBox();
		void NextSet();

		void Render(std::shared_ptr<aetherClass::ShaderBase>);

		int GetNavigationID()const;
	private:
		std::shared_ptr<aetherClass::Cube> m_navigationBox;
		static aetherClass::Vector3 m_navigationBoxPosition[];
		std::shared_ptr<aetherClass::Texture> m_texture;
		int m_navigationID;
		int m_navigationArrayElement;
};

#endif
