#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
/*
	Player�Ǘ��N���X
	updater��render�̃I�u�W�F�N�g��ێ����A
	player�̏�Ԃ̊Ǘ��Ȃǂ𐿂������Ƃ��H

*/
#include "PlayerBase.h"
#include "PlayerUpdater.h"
#include "PlayerRender.h"
#include "PlayerNavigation.h"
#include <memory>
#include <CollideBoxOBB.h>
class PlayerManager
{

	public:
		PlayerManager();
		~PlayerManager();

		bool Initialize(const std::shared_ptr<DxCamera::ViewCamera>);
		
		void Render(const std::shared_ptr<DxShader::ShaderBase>);
		void Update(float);
		PlayerBase::PlayerStatus& Status();
		void Status(PlayerBase::PlayerStatus&);

		// �O���I�u�W�F�N�g�Ƃ̓����蔻��p
		bool HitMesh(const std::shared_ptr<DxModel::ModelBase>&);
		bool HitMesh(const std::shared_ptr<DxModel::FbxStaticMesh>&);

		void NextSerch();

		bool IsChangeCamera();	// �J������؂�ւ��邩�̔��ʗp
		std::unique_ptr<PlayerNavigation> m_navigation; // �v���C���[�̃��[�g�p�I�u�W�F�N�g
	private:
		// ���ɍs�������Z�b�g
		void SetNextPoint(const std::shared_ptr<DxModel::ModelBase>&);

	private:
		std::unique_ptr<PlayerUpdater> m_updater;		// �v���C���[�̍X�V�I�u�W�F�N�g
		std::unique_ptr<PlayerRender> m_render;	        // �v���C���[�̕`��I�u�W�F���g
		

		std::shared_ptr<DxModel::FbxStaticMesh> m_playerObject; // �v���C���[�̃��f���I�u�W�F�N�g
		std::shared_ptr<DxModel::ModelBase> m_collideBox;	// ���ۂɓ����蔻����s���I�u�W�F�N�g

		CollideBoxOBB m_collider;	// �����蔻����s���֐�
		bool m_isCahngeCamera;		// �J������؂�ւ���t���O
		
};

#endif