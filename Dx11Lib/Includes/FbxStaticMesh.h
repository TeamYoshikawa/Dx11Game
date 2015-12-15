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

		
		
	private:
		bool InitializeBuffers()override;
		void ShutdownBuffers()override;
		void NodeRenderBuffers(int id)override;
	
	};

}