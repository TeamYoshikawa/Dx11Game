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
#include <Cube.h>
#include<ViewCamera.h>
#include <FbxModel.h>
#include <Texture.h>
#include <memory>
class PlayerManager
{

public:
	PlayerManager();
	~PlayerManager();

	bool Initialize();//const std::shared_ptr<aetherClass::ViewCamera>);

	void Render(const std::shared_ptr<aetherClass::ShaderBase>);
	void Update(const std::shared_ptr<aetherClass::ViewCamera>);
	PlayerBase::PlayerStatus& Status();
	void Status(PlayerBase::PlayerStatus&);

	// �O���I�u�W�F�N�g�Ƃ̓����蔻��p
	bool HitMesh(std::shared_ptr<aetherClass::ModelBase>&);


	std::shared_ptr<aetherClass::ModelBase> Get();

	int LifeGet();

	void SetState(PlayerBase::ePlayerMoveState);

	bool GetIsDamage();

	bool IsDead();

private:
	// ���ɍs�������Z�b�g
	void SetNextPoint(const std::shared_ptr<aetherClass::ModelBase>&);

	// �R���C�h���v���C���[�ɂ��Ă���悤�ɂ���
	void UpdateColliderBox();

private:

	std::unique_ptr<PlayerUpdater> m_updater;		// �v���C���[�̍X�V�I�u�W�F�N�g
	std::unique_ptr<PlayerRender> m_render;	        // �v���C���[�̕`��I�u�W�F���g
	std::shared_ptr<aetherClass::Texture> m_collideTexture;
	std::shared_ptr<aetherClass::FbxModel> m_playerObject; // �v���C���[�̃��f���I�u�W�F�N�g
	std::shared_ptr<aetherClass::ModelBase> m_collideBox;	// ���ۂɓ����蔻����s���I�u�W�F�N�g
	std::shared_ptr<aetherClass::ViewCamera> m_camera;
	std::shared_ptr<aetherClass::ShaderBase> m_collideBoxShader;
	bool m_isCahngeCamera;		// �J������؂�ւ���t���O
};

#endif