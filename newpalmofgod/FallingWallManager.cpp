#include "FallingWallManager.h"

using namespace std;
using namespace aetherClass;

FallingWallManager::FallingWallManager()
{
	m_size = 250;
}


FallingWallManager::~FallingWallManager()
{
}

bool FallingWallManager::Initialize(ViewCamera* camera)
{
	m_updater = make_shared<FallingWallUpdater>();
	m_render = make_shared<FallingWallRender>();

	m_texture = make_shared<Texture>();
	m_texture->Load("ModelData/textures/cocoa.jpg");

	m_fallingWall = make_shared<Cube>();
	if (!m_fallingWall->Initialize()){ return false; }

	m_fallingWall->SetCamera(camera);
	m_fallingWall->SetTexture(m_texture.get());

	m_fallingWall->GetTransform()._scale = Vector3(m_size,m_size,m_size);
	m_fallingWall->GetTransform()._translation = Vector3(8700,-8,1200);


	m_collider = make_shared<Cube>();
	if (!m_collider->Initialize()){ return false; }

	m_collider->SetCamera(camera);
	m_collider->SetTexture(m_texture.get());
	m_collider->GetTransform()._scale = Vector3(m_size-10, 1, m_size-10);
	m_collider->GetTransform()._translation = m_fallingWall->GetTransform()._translation;

}

void FallingWallManager::Update()
{
	m_updater->Update(m_fallingWall.get());
	float x = m_fallingWall->GetTransform()._translation._x;
	float z = m_fallingWall->GetTransform()._translation._z;
	float y = m_fallingWall->GetTransform()._translation._y + (m_fallingWall->GetTransform()._scale._y);

	m_collider->GetTransform()._translation = Vector3(x, y, z);
}

void FallingWallManager::Render(shared_ptr<ShaderBase> shader)
{
	m_render->Render(m_fallingWall.get(), shader);
	m_collider->Render(shader.get());
}

bool FallingWallManager::HitMesh(shared_ptr<ModelBase>& player, shared_ptr<ModelBase>& other)
{
	if (!m_updater->HittingProcessor(player, other))
	{
		return false;
	}

	return true;
}

shared_ptr<ModelBase> FallingWallManager::GetFallingWall()
{
	return m_collider;
}