#pragma once
#include "ModelBase.h"
#include "FbxLoader.h"

namespace DxModel{

	class FbxStaticMesh :
		public DxModel::ModelBase
	{
	public:
		FbxStaticMesh();
		~FbxStaticMesh();

		void LoadFBX(std::string, MyFbx::FbxLoader::eAxisSystem);
	private:
		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void RenderBuffers()override;

	private:
		std::unique_ptr<MyFbx::FbxLoader> m_fbxLoader;
	};

}