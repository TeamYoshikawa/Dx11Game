#pragma once
#include <GameScene.h>
class GutioScene :
	public aetherClass::GameScene
{
public:
	GutioScene();
	~GutioScene();
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

