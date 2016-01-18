#pragma once
#include <GameScene.h>
class HirokiScene :
	public aetherClass::GameScene
{
public:
	HirokiScene();
	~HirokiScene();

	/*	•K‚¸Œp³‚µ‚È‚«‚á‚¢‚¯‚È‚¢‚à‚Ì	*/
	bool Initialize()override;
	void Render()override;
	bool Updater()override;
	void Finalize()override;

	/*	Œp³‚µ‚Ä‚à‚µ‚È‚­‚Ä‚à‚¢‚¢‚æ*/
	/*bool TransitionIn()override;
	bool TransitionOut()override;*/
public:
	static std::string m_name;
};

