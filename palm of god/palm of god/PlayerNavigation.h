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

		void Initialize(std::shared_ptr<DxCamera::ViewCamera>);

		std::shared_ptr<DxModel::Cube> GetNavigationBox();
		void NextSet();

		void Render(std::shared_ptr<DxShader::ShaderBase>);

		int GetNavigationID()const;
	private:
		static std::shared_ptr<DxModel::Cube> m_navigationBox;
		static DxMath::Vector3 m_navigationBoxPosition[];

		static int m_navigationID;
		int m_navigationArrayElement;
};

#endif
