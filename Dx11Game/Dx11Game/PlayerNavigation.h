#ifndef _PLAYERNAVIGATION_H
#define _PLAYERNAVIGATION_H
#include <memory>
#include <Cube.h>
#include <Vector3.h>
class PlayerNavigation
{
	public:
		PlayerNavigation();
		~PlayerNavigation();

		void Initialize();


	private:
		static std::shared_ptr<DxModel::Cube> m_navigationBox;
		static DxMath::Vector3 m_vavigationBoxPoisition[];
};

#endif
