#pragma once
#include <GameScene.h>
class GutioScene :
	public aetherClass::GameScene
{
public:
	GutioScene();
	~GutioScene();
	/*	�K���p�����Ȃ��Ⴂ���Ȃ�����	*/
	bool Initialize()override;
	void Render()override;
	bool Updater()override;
	void Finalize()override;

	/*	�p�����Ă����Ȃ��Ă�������*/
	/*bool TransitionIn()override;
	bool TransitionOut()override;*/
public:
	static std::string m_name;
};

