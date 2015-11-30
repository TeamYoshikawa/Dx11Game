#ifndef _SCENETITLE_H
#define _SCENETITLE_H
#include "SceneBase.h"
class SceneTitle :
	public SceneBase
{
	public:
		SceneTitle(SceneManager* manager);
		~SceneTitle();

		void Initialize()override;
		void Updata()override;
		void Render()override;
		void Shutdown()override;

	public:
		static const std::string m_thisName;
};

#endif