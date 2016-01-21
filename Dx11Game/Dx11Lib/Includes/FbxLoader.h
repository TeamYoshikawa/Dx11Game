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


		ModelProperty::VertexType* GetMeshNodeVertexBuffer(int id);
		unsigned long* GetMeshNodeIndexBuffer(int id);
		void GetMeshElements(ModelProperty::MeshElements&, int id);

		unsigned int GetMeshNodeCount();

	private:
		void TriangulatedPolygons(FbxScene*, FbxNode*);

		void GetMesh(FbxNode*, FbxScene*);

		void GetMeshProperty(FbxMesh*, FbxScene*);

		void GetTransform(FbxMesh*);

		void GetVertexPosition(FbxMesh*);

		void GetVertexNomal(FbxMesh*);

		void GetVertexUV(FbxMesh*);

		void GetMaterial(FbxMesh*);

		void GetSkin(FbxMesh*, FbxScene*);
		void CopyMaterialData(FbxSurfaceMaterial*, ModelProperty::Material*);

		void SetFbxColor(ModelProperty::MaterialElement&, FbxDouble3);

		FbxDouble3 FbxLoader::GetMaterialPropertey(
			const FbxSurfaceMaterial* material,
			std::string propertyName,
			std::string factorPropertyName,
			ModelProperty::MaterialElement* element);

		void ComputeNodeMatrix(FbxNode*, FbxModelProperty::FbxMeshNode*, FbxScene*);

		void FbxDoubleToVector3(DxMath::Vector3&,FbxDouble3*);

		static void FbxMatrixToFloat16(float*, FbxMatrix*);
		std::string StringSplite(const std::string&,char);
	private:

		unsigned int m_meshNodeCounter;

		ModelProperty::VertexType* m_vertexBuffer;
		unsigned long* m_indexBuffer;
		FbxModelProperty::FbxMeshNode m_meshNode;
		ModelProperty::MeshElements m_meshElements;

		std::vector<FbxModelProperty::FbxMeshNode> m_meshNodeArray;
		std::vector<unsigned long*> m_polygonSizeArray;

		std::vector<ModelProperty::VertexType*> m_vertexBufferArray;
		std::vector<unsigned long*> m_indexBufferArray;
		std::vector<ModelProperty::MeshElements> m_meshElementsArray;

	};
}

#endif