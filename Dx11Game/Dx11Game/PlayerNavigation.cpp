#include "PlayerNavigation.h"

using namespace DxModel;
using namespace DxMath;
std::shared_ptr<Cube> PlayerNavigation::m_navigationBox = nullptr;
Vector3 PlayerNavigation::m_vavigationBoxPoisition[] = {
	{Vector3(0.f,0.f,0.f)}
};

PlayerNavigation::PlayerNavigation()
{
}


PlayerNavigation::~PlayerNavigation()
{
}
