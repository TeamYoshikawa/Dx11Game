#include <windows.h>
#pragma comment (lib,"Aether.lib")

#include <GameEntry.h>
#include <GameController.h>
#include <ConsoleWindow.h>
#include <GameSceneManager.h>
#include "SceneTitle.h"
#include "LoadObj.h"


using namespace aetherClass;
// �G���g���[�|�C���g���쐬
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT){

	// �R���\�[���E�B���h�E���\�������
	//ConsoleWindow::Create();

	// ���̃N���X�����C�����[�v�������Ă���N���X
	GameEntry* entry = new GameEntry();

	// �Ǝ��ɍ쐬�����t���[���I�u�W�F�N�g�̃I�u�W�F�N�g���쐬
	GameFrame* frame = new GameFrame();

	// ������
	entry->Initialize(false, L"Palm of God");
	frame->Initialize(*entry->GetWindowHandle(), POINT{800,600},false,10000000);

	// ���̊֐����Ăяo�����Ƃɂ���āA��ʂ̔w�i�F�̕ύX���ł���
	// �f�t�H���g�̐ݒ�ł͍����ݒ肳��Ă���
	frame->BackgroundColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
	
	// �G���g���[�N���X�Ƀ��C�����[�v�Ɏg��Frame�I�u�W�F�N�g��ݒ�
	entry->SetGameFrame(frame);

	// �ŏ��̃V�[���̃I�u�W�F�N�g���쐬
	GameScene* firstScene = new SceneTitle();


	// �ŏ��̃V�[���̐ݒ�
	GameSceneManager::SetCurrentScene(firstScene);

	// ���s���郍�[�h�I�u�W�F�N�g�̍쐬
	LoadScreen *loadobj = new LoadObj;
	GameSceneManager::SetLoadScreen(loadobj);
	// ���C�����[�v�̊J�n
	// ���̊֐��̓�����,GameFrame�I�u�W�F�N�g��FrameRunning���Ă΂��B
	entry->GameRun();

	// �t���[���I�u�W�F�N�g�̔j��
	delete frame;
	frame = nullptr;

	// �G���g���[�I�u�W�F�N�g�̔j��
	delete entry;
	entry = nullptr;

	// �R���\�[���E�B���h�E��j���������Ƃ��͂��̊֐����Ă�
	//ConsoleWindow::Close();
	return 0;
}