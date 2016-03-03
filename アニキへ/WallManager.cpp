#include "WallManager.h"
#include <iostream>

using namespace aetherClass;

using namespace n_Wall;


bool WallManager::Initialize(ViewCamera* camera){

	m_WallTexture = std::make_shared<Texture>();
	m_WallTexture->Load("ModelData/textures/seafloor.dds");

	m_HitWallTexture = std::make_shared<Texture>();
	m_HitWallTexture->Load("image/kabe2.png");

	m_hplayerTexture = std::make_shared<Texture>();
	m_hplayerTexture->Load("Title.png");


	for (i = 0; i < r_max; i++){
		m_HitWall[i] = std::make_shared<Cube>();
		if (!m_HitWall[i]->Initialize()){
			return false;

		}
	}

	for (i = 0; i < r_max; i++){

		m_HitWall[i]->SetCamera(camera);
		m_HitWall[i]->SetTexture(m_HitWallTexture.get());
	}	


	/*壁*/

	//スタートすぐ右の壁
	m_HitWall[0]->property._transform._translation = Vector3(-178.0f, 100.0f, 0.0f);
	m_HitWall[0]->property._transform._scale = Vector3(1500.0f, 300.0f, 10.0f);
	m_HitWall[0]->property._transform._rotation._y = 90;

	//スタートすぐ目の前
	m_HitWall[1]->property._transform._translation = Vector3(880.0f, 100.0f, 900.0f);
	m_HitWall[1]->property._transform._scale = Vector3(1610.0f, 300.0f, 10.0f);

	//スタートすぐ後ろ
	m_HitWall[14]->property._transform._translation = Vector3(14.0f, 100.0f, 10.0f);
	m_HitWall[14]->property._transform._scale = Vector3(180.0f, 300.0f, 10.0f);

	m_HitWall[18]->property._transform._translation = Vector3(800.0f, 100.0f, 10.0f);
	m_HitWall[18]->property._transform._scale = Vector3(300.0f, 300.0f, 10.0f);

	m_HitWall[19]->property._transform._translation = Vector3(400.0f, 275.0f, 10.0f);
	m_HitWall[19]->property._transform._scale = Vector3(600.0f, 300.0f, 10.0f);


	m_HitWall[20]->property._transform._translation = Vector3(400.0f, -200.0f, 10.0f);
	m_HitWall[20]->property._transform._scale = Vector3(600.0f, 40.0f, 10.0f);

	//スタート左の壁
	m_HitWall[15]->property._transform._translation = Vector3(1000.0f, 100.0f, 70.0f);
	m_HitWall[15]->property._transform._scale = Vector3(520.0f, 300.0f, 30.0f);
	m_HitWall[15]->property._transform._rotation._y = 90;

	//↑の壁の対局位置にいる壁
	m_HitWall[17]->property._transform._translation = Vector3(1000.0f, 100.0f, 870.0f);
	m_HitWall[17]->property._transform._scale = Vector3(80.0f, 300.0f, 30.0f);
	m_HitWall[17]->property._transform._rotation._y = 90;

	//次の部屋後ろ
	m_HitWall[2]->property._transform._translation = Vector3(2200.0f, 100.0f, 310.0f);
	m_HitWall[2]->property._transform._scale = Vector3(1200.0f, 300.0f, 10.0f);

	//岩の先の通路の壁
	m_HitWall[3]->property._transform._translation = Vector3(3000.0f, 100.0f, 2515.0f);
	m_HitWall[3]->property._transform._scale = Vector3(3000.0f, 300.0f, 10.0f);

	//岩の先の通路の壁
	m_HitWall[16]->property._transform._translation = Vector3(4200.0f, 100.0f, 1910.0f);
	m_HitWall[16]->property._transform._scale = Vector3(1100.0f, 300.0f, 10.0f);

	//岩左壁
	m_HitWall[4]->property._transform._translation = Vector3(3145.0f, 100.0f, 910.0f);
	m_HitWall[4]->property._transform._scale = Vector3(980.0f, 300.0f, 50.0f);
	m_HitWall[4]->property._transform._rotation._y = 90;

	//岩右壁
	m_HitWall[5]->property._transform._translation = Vector3(2500.0f, 100.0f, 1850.0f);
	m_HitWall[5]->property._transform._scale = Vector3(970.0f, 300.0f, 10.0f);
	m_HitWall[5]->property._transform._rotation._y = 90;

	//落とし穴の前の右壁
	m_HitWall[6]->property._transform._translation = Vector3(5900.0f, 100.0f, 1890.0f);
	m_HitWall[6]->property._transform._scale = Vector3(980.0f, 300.0f, 10.0f);
	m_HitWall[6]->property._transform._rotation._y = 90;

	//落とし穴の前の左壁
	m_HitWall[13]->property._transform._translation = Vector3(5300.0f, 100.0f, 910.0f);
	m_HitWall[13]->property._transform._scale = Vector3(980.0f, 300.0f, 10.0f);
	m_HitWall[13]->property._transform._rotation._y = 90;

	//落とし穴の場所の壁
	m_HitWall[7]->property._transform._translation = Vector3(9540.0f, 100.0f, 1920.0f);
	m_HitWall[7]->property._transform._scale = Vector3(500.0f, 300.0f, 10.0f);

	//落とし穴の場所の壁
	m_HitWall[8]->property._transform._translation = Vector3(7150.0f, 100.0f, 340.0f);
	m_HitWall[8]->property._transform._scale = Vector3(1950.0f, 300.0f, 10.0f);

	//槍の場所の右の壁
	m_HitWall[9]->property._transform._translation = Vector3(8402.0f, 100.0f, 1920.0f);
	m_HitWall[9]->property._transform._scale = Vector3(980.0f, 300.0f, 50.0f);
	m_HitWall[9]->property._transform._rotation._y = 90;

	//槍の場所の左の壁
	m_HitWall[10]->property._transform._translation = Vector3(9042.0f, 100.0f, 950.0f);
	m_HitWall[10]->property._transform._scale = Vector3(980.0f, 300.0f, 50.0f);
	m_HitWall[10]->property._transform._rotation._y = 90;

	//槍の奥の壁
	m_HitWall[11]->property._transform._translation = Vector3(9000.0f, 100.0f, 2400.0f);
	m_HitWall[11]->property._transform._scale = Vector3(1000.0f, 300.0f, 10.0f);

	//ゴールの壁
	m_HitWall[12]->property._transform._translation = Vector3(7150.0f, 100.0f, 910.0f);
	m_HitWall[12]->property._transform._scale = Vector3(1250.0f, 300.0f, 10.0f);

	
	/*ここまで*/

	m_updater = std::make_shared<WallUpdater>();
	m_render = std::make_shared<WallRender>();

	m_WallEvent = eEvent::eChecking;
	return true;
}

void WallManager::Update(){

}

bool WallManager::HitMesh(std::shared_ptr<aetherClass::ModelBase>& player , std::shared_ptr<aetherClass::ViewCamera> camera){
	
	for (i = 0; i < r_max; i++){
		if (m_updater->HitProcessor(m_HitWall[i], player)){
			std::cout << "壁に当たったよ" << std::endl;
			return true;
		}
	}
	return false;
}

void WallManager::Render(std::shared_ptr<ShaderBase>shader){

	for (i = 0; i < r_max; i++){
		m_HitWall[i]->Render(shader.get());
	}

	
	//m_hplayer->Render(shader.get());
}


std::shared_ptr<aetherClass::ModelBase> WallManager::Get(int i){	
	return m_HitWall[i];
}

int WallManager::WallCnt()
{
	return r_max;
}
