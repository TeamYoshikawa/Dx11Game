#ifndef _SCENEGAME_H
#define _SCENEGAME_H
#include "SceneBase.h"

class SceneGame :
	public SceneBase
{
	public:
		SceneGame(SceneManager*);
		~SceneGame();

		void Initialize()override;
		void Updata()override;
		void Render()override;
		void Shutdown()override;

	public:
		static const std::string m_thisName;
};

#endif