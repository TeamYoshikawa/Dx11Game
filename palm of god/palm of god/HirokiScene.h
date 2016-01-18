#pragma once
#include <GameScene.h>
class HirokiScene :
	public aetherClass::GameScene
{
public:
	HirokiScene();
	~HirokiScene();

	/*	必ず継承しなきゃいけないもの	*/
	bool Initialize()override;
	void Render()override;
	bool Updater()override;
	void Finalize()override;

	/*	継承してもしなくてもいいよ*/
	/*bool TransitionIn()override;
	bool TransitionOut()override;*/
public:
	static std::string m_name;
};

