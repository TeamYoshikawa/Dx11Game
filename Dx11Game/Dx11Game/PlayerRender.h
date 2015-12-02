/*
	Playerのレンダークラス
	描画処理を担当

*/
#ifndef _PLAYERRENDER_H
#define _PLAYERRENDER_H
#include "PlayerBase.h"
#include <ShaderBase.h>
#include <ModelBase.h>
class PlayerRender :
	private PlayerBase
{
		
	public:
		PlayerRender();
		PlayerRender(PlayerRender&);
		~PlayerRender();

		bool Initialize(const std::shared_ptr<DxCamera::ViewCamera>, std::string fileName = "null");
		void Frame(DxShader::ShaderBase*, DxModel::eRenderWay);

	private:
		std::shared_ptr<DxModel::ModelBase> m_playerObject;
};

#endif