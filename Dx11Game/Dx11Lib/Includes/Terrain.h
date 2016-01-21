#pragma once
#include "ModelBase.h"
namespace DxModel{
	class Terrain :
		public ModelBase
	{
	private:
		struct HeightMap
		{
			float _x, _y, _z;
		};

	public:
		Terrain();
		Terrain(const Terrain&);
		~Terrain();

		bool InitializeBuffers();
		void ShutdownBuffers();
		void RenderBuffers();

		bool LoadHeightMap(char*);
		void NormalizedHeightMap();
		void ShutdownHeightMap();

	private:
		HeightMap* m_heightMap;
		int m_terrainWidth, m_terrainHeight;

	};
}

