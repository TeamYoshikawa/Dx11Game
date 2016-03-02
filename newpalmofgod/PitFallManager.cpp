#include "PitFallManager.h"
#include "Cube.h"


using namespace aetherClass;
using namespace Pitfall;


bool PitFallManager::Initialize(ViewCamera* camera ,Vector3 origin){

	
	m_pitfalllib[0] = std::make_shared<PitFallLib>();
	if (!m_pitfalllib[0]->Initialize()){
		return false;
	}
	m_pitfalllib[0]->SetCamera(camera);
	m_pitfalllib[0]->property._transform._translation = origin;
	m_pitfalllib[0]->property._transform._translation._x += 1;
	m_pitfalllib[0]->SetCamera(camera);
	m_pitfalllib[0]->property._transform._translation = origin;
	m_pitfalllib[0]->property._transform._scale = 200;
	m_pitfalllib[0]->property._transform._scale._z *= 5.3;
	m_pitfalllib[0]->property._transform._scale._z += 20;
	m_pitfalllib[0]->property._transform._scale._x *= 1.7;

	m_pitfalllib[0]->property._transform._rotation._x = 180;
	m_pitfalllib[0]->property._transform._rotation._y = -90;
	m_pitfalllib[0]->property._transform._translation._z += m_pitfalllib[0]->property._transform._scale._x;



	m_pitfalllib[1] = std::make_shared<PitFallLib>();
	if (!m_pitfalllib[1]->Initialize()){
		return false;
	}
	m_pitfalllib[1]->SetCamera(camera);
	m_pitfalllib[1]->property._transform._translation = origin;
	m_pitfalllib[1]->property._transform._scale = 200;
	m_pitfalllib[1]->property._transform._scale._z *= 5.3;
	m_pitfalllib[1]->property._transform._scale._z += 10;
	m_pitfalllib[1]->property._transform._scale._x *= 1.7;

	m_pitfalllib[1]->property._transform._translation._z -= m_pitfalllib[0]->property._transform._scale._x;
	m_pitfalllib[1]->property._transform._rotation._x = 180;
	m_pitfalllib[1]->property._transform._rotation._y = 90;

	m_pitfall = std::make_shared<PitFall>();
	if (!m_pitfall->Initialize()){
		return false;
	}
	m_pitfall->SetCamera(camera);
	m_pitfall->property._transform._translation = origin;
	m_pitfall->property._transform._scale = 200;
	m_pitfall->property._transform._scale._z *= 5.4;
	m_pitfall->property._transform._scale._z += 10;
	m_pitfall->property._transform._scale._x *= 1.7;

	m_pitfall->property._transform._rotation._x = 180;
	m_pitfall->property._transform._rotation._y = 90;


	m_updater = std::make_shared<PitFallUpdater>();
	m_render = std::make_shared<PitFallRender>();

	Material material;
	material._ambient._color = Color(0.6, 0, 0.6, 1);
	material._diffuse._color = Color(1, 1, 1, 1);
	material._specular._color = Color(1, 0, 0, 1);
	material._specularPower = 0.6;// _color = Color(1, 0, 0, 1);
	
	m_pitfalllib[0]->property._material = material;

	m_pitfalllib[1]->property._material = material;

	m_pitfall->property._material = material;

	m_collideBox = std::make_shared<aetherClass::Cube>();
	m_collideBox->Initialize();
	m_collideBox->SetCamera(camera);
	m_collideBox->property._transform._translation = origin;
	m_collideBox->property._transform._scale = 200;
	return true;
}

void PitFallManager::Shutdown(){
	for (int i = 0; i < 2; i++)
	{
		m_pitfalllib[i]->Finalize();
	}
	m_pitfall->Finalize();
	return;
}

void PitFallManager::Update(){
	static bool button = false;
		button = GameController::GetMouse().IsLeftButtonDown() ? true : false;
		for (int i = 0; i < 2; i++)
		{
			m_updater->Update(m_pitfalllib[i].get(), button);
		}
		return;
}


void PitFallManager::Render(std::shared_ptr<ShaderBase>shader){
	for (int i = 0; i < M_PITLIB; i++)
	{
		m_render->Render(m_pitfalllib[i].get(), shader);
	}
	m_render->Render(m_pitfall.get(), shader);
//	m_collideBox->Render(shader.get());

	return;
}


void PitFallManager::ChangeCamera(ViewCamera *camera){
	for (int i = 0; i < M_PITLIB; i++)
	{
		m_pitfalllib[i]->SetCamera(camera);
	}
	m_pitfall->SetCamera(camera);
	return;
}

std::shared_ptr<aetherClass::ModelBase> PitFallManager::Get()
{
	return 	m_collideBox;
}

int PitFallManager::FlagGet()
{
	return m_updater->FlagGet();
}
