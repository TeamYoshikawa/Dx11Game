#ifndef _FBXLOADER_H
#define _FBXLOADER_H
#pragma comment (lib,"libfbxsdk-md.lib")
#include <fbxsdk.h>
#include "FbxModelProperty.h"
#include "ModelProperty.h"
namespace DxFbx{
	class FbxLoader
	{

	public:

		enum class eAxisSystem{
			eAxisDirectX = 0,
			eAxisOpenGL
		};


	public:
		FbxLoader();
		~FbxLoader();

		bool FileOpen(std::string, eAxisSystem);

		std::vector<FbxModelProperty::FbxMeshNode> GetMeshNode();

		void Release();


		ModelProperty::VertexType* GetVertex(int id);
		unsigned long* GetIndex(int id);
		void GetMeshElements(ModelProperty::MeshElements&,int id);

		unsigned int GetMeshNodeCount();

	private:
		void TriangulatedPolygons(FbxScene*, FbxNode*);
		void GetMesh(FbxNode* node);

		void GetVertexPosition(FbxMesh* mesh);

		void GetVertexNomal(FbxMesh* mesh);

		void GetVertexUV(FbxMesh* mesh);

		void GetVertexColor(FbxMesh* mesh);

		void GetMaterial(FbxMesh*);
		void CopyMaterialData(FbxSurfaceMaterial*, ModelProperty::Material*);

		void SetFbxColor(ModelProperty::MaterialElement&, FbxDouble3);

		FbxDouble3 FbxLoader::GetMaterialPropertey(
			const FbxSurfaceMaterial* material,
			std::string propertyName,
			std::string factorPropertyName,
			ModelProperty::MaterialElement* element);

		void ComputeNodeMatrix(FbxNode*, FbxModelProperty::FbxMeshNode*, FbxScene*);

		static void FbxMatrixToFloat16(FbxMatrix*, float matrix[16]);

	private:

		unsigned int m_meshNodeCounter;

		ModelProperty::VertexType* m_vertexBuffer;
		unsigned long* m_indexBuffer;
		ModelProperty::MeshElements m_meshElements;

		std::vector<FbxModelProperty::FbxMeshNode> m_meshNode;
		std::vector<unsigned long*> m_polygonSizeArray;

		std::vector<ModelProperty::VertexType*> m_vertexBufferArray;
		std::vector<unsigned long*> m_indexBufferArray;
		std::vector<ModelProperty::MeshElements> m_meshElementsArray;

	};
}

#endif