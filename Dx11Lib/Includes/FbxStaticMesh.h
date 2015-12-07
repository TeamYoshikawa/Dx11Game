#pragma once
#include "FbxBase.h"
#include "FbxLoader.h"

namespace DxModel{

	class FbxStaticMesh :
		public DxModel::FbxBase
	{
	public:
		FbxStaticMesh();
		~FbxStaticMesh();

		void LoadFBX(std::string, DxFbx::FbxLoader::eAxisSystem);
		
	private:
		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void NodeRenderBuffers(int id)override;
	
	};

}