#ifndef _FBXLOADER_H
#define _FBXLOADER_H
#pragma comment (lib,"libfbxsdk-md.lib")
#include <fbxsdk.h>
#include "FbxModelProperty.h"

namespace MyFbx{
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

		void GetInfo();

		void Release();


		ModelProperty::VertexType* GetVertex();
		unsigned long* GetIndex();
		void GetMeshElements(ModelProperty::MeshElements&);
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
	public:

		std::vector<FbxModelProperty::FbxMeshNode> m_meshNode;

		unsigned long m_polygonCount;
		unsigned long* m_polygonSize;


		ModelProperty::VertexType* m_vertexBuffer;
		unsigned long* m_indexBuffer;
		ModelProperty::MeshElements m_meshElements;

		
		



	};
}
#endif