#pragma once
#include "ModelBase.h"
namespace DxModel{
	class TerrainClass :
		public ModelBase
	{
	private:
		struct HeightMap
		{
			float _x, _y, _z;
		};

	public:
		TerrainClass();
		TerrainClass(const TerrainClass&);
		~TerrainClass();

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

