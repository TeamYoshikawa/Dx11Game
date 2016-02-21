#include "WallManager.h"
#include <iostream>

using namespace aetherClass;

using namespace n_Wall;


bool WallManager::Initialize(ViewCamera* camera){

	m_WallTexture = std::make_shared<Texture>();
	m_WallTexture->Load("ModelData/textures/seafloor.dds");

	m_HitWallTexture = std::make_shared<Texture>();
	m_HitWallTexture->Load("heart.png");

	m_hplayerTexture = std::make_shared<Texture>();
	m_hplayerTexture->Load("Title.png");


	for (i = 0; i < r_max; i++){
		m_HitWall[i] = std::make_shared<Cube>();
		if (!m_HitWall[i]->Initialize()){
			return false;
		
	}
}



	m_hplayer = std::make_shared<Cube>();
	if (!m_hplayer->Initialize()){
		return false;
	}

	for (i = 0; i < r_max; i++){

		m_HitWall[i]->SetCamera(camera);
		m_HitWall[i]->SetTexture(m_HitWallTexture.get());
	}


	m_hplayer->SetCamera(camera);
	m_hplayer->SetTexture(m_hplayerTexture.get());


	


	/*•Ç*/

	m_HitWall[0]->GetTransform()._translation = Vector3(2000.0f, 100.0f, 310.0f);
	m_HitWall[0]->GetTransform()._scale = Vector3(1000.0f, 300.0f, 10.0f);

	m_HitWall[1]->GetTransform()._translation = Vector3(900.0f, 100.0f, 920.0f);
	m_HitWall[1]->GetTransform()._scale = Vector3(1500.0f, 300.0f, 10.0f);

	m_HitWall[2]->GetTransform()._translation = Vector3(3000.0f, 100.0f, 2525.0f);
	m_HitWall[2]->GetTransform()._scale = Vector3(3000.0f, 300.0f, 10.0f);

	m_HitWall[3]->GetTransform()._translation = Vector3(7150.0f, 100.0f, 920.0f);
	m_HitWall[3]->GetTransform()._scale = Vector3(1250.0f, 300.0f, 10.0f);

	m_HitWall[4]->GetTransform()._translation = Vector3(7150.0f, 100.0f, 300.0f);
	m_HitWall[4]->GetTransform()._scale = Vector3(1950.0f, 300.0f, 10.0f);

	m_HitWall[5]->GetTransform()._translation = Vector3(9500.0f, 100.0f, 1910.0f);
	m_HitWall[5]->GetTransform()._scale = Vector3(500.0f, 300.0f, 10.0f);

	m_HitWall[6]->GetTransform()._translation = Vector3(9000.0f, 100.0f, 2420.0f);
	m_HitWall[6]->GetTransform()._scale = Vector3(1000.0f, 300.0f, 10.0f);
	


	m_HitWall[7]->GetTransform()._translation = Vector3(-188.0f, 100.0f, 0.0f);
	m_HitWall[7]->GetTransform()._scale = Vector3(1500.0f, 300.0f, 10.0f);
	m_HitWall[7]->GetTransform()._rotation._y = 90;

	m_HitWall[8]->GetTransform()._translation = Vector3(3152.0f, 100.0f, 920.0f);
	m_HitWall[8]->GetTransform()._scale = Vector3(980.0f, 300.0f, 10.0f);
	m_HitWall[8]->GetTransform()._rotation._y = 90;

	m_HitWall[9]->GetTransform()._translation = Vector3(2502.0f, 100.0f, 1850.0f);
	m_HitWall[9]->GetTransform()._scale = Vector3(980.0f, 300.0f, 10.0f);
	m_HitWall[9]->GetTransform()._rotation._y = 90;

	m_HitWall[10]->GetTransform()._translation = Vector3(5930.0f, 100.0f, 1900.0f);
	m_HitWall[10]->GetTransform()._scale = Vector3(980.0f, 300.0f, 10.0f);
	m_HitWall[10]->GetTransform()._rotation._y = 90;

	m_HitWall[11]->GetTransform()._translation = Vector3(8402.0f, 100.0f, 1900.0f);
	m_HitWall[11]->GetTransform()._scale = Vector3(980.0f, 300.0f, 10.0f);
	m_HitWall[11]->GetTransform()._rotation._y = 90;

	m_HitWall[12]->GetTransform()._translation = Vector3(9042.0f, 100.0f, 900.0f);
	m_HitWall[12]->GetTransform()._scale = Vector3(980.0f, 300.0f, 10.0f);
	m_HitWall[12]->GetTransform()._rotation._y = 90;

	
	/*‚±‚±‚Ü‚Å*/

	m_updater = std::make_shared<WallUpdater>();
	m_render = std::make_shared<WallRender>();

	m_WallEvent = eEvent::eChecking;
	return true;
}

void WallManager::Update(){

	if (GameController::GetKey().IsKeyDown(DIK_A)){

		m_hplayer->GetTransform()._translation._x -= 1.0f;
	}

	if (GameController::GetKey().IsKeyDown(DIK_D)){

		m_hplayer->GetTransform()._translation._x += 1.0f;
	}

	if (m_WallEvent == eEvent::eChecking)
	{
		
	}
	else
	{
		m_updater->Update(m_Wall[0].get());
	}
}

void WallManager::Render(std::shared_ptr<ShaderBase>shader){

	for (i = 0; i < r_max; i++){
		m_HitWall[i]->Render(shader.get());
	}

	
	m_hplayer->Render(shader.get());
}


std::shared_ptr<aetherClass::ModelBase> WallManager::Get(){

	return m_Wall[0];
}
