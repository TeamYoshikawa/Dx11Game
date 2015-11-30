#include "FbxLoader.h"

#include <iostream>

namespace MyFbx{
	FbxLoader::FbxLoader(){

		m_polygonCount = 0;
		m_polygonSize = nullptr;
		m_vertexBuffer = nullptr;
		m_indexBuffer = nullptr;
	}


	FbxLoader::~FbxLoader()
	{

	}

	void FbxLoader::Release(){
		// Release Buffer
		if (m_vertexBuffer)
		{
			delete[] m_vertexBuffer;
			m_vertexBuffer = nullptr;
		}
		
		if (m_indexBuffer)
		{
			delete[] m_indexBuffer;
			m_indexBuffer = nullptr;
		}

		
		if (m_polygonSize)
		{
			delete[] m_polygonSize;
			m_polygonSize = nullptr;
		}
		
	}

	void FbxLoader::FbxMatrixToFloat16(FbxMatrix* src, float dest[16])
	{
		unsigned int nn = 0;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				dest[nn] = static_cast<float>(src->Get(i, j));
				nn++;
			}
		}
	}

	bool FbxLoader::FileOpen(std::string filePath, eAxisSystem axis){
		bool result;

		// Fbx sdk Manager class
		FbxManager* manager = FbxManager::Create();

		FbxIOSettings* iossetings = FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(iossetings);

		FbxString lPath = FbxGetApplicationDirectory();
		manager->LoadPluginsDirectory(lPath.Buffer());

		// vertex information accese
		FbxScene* scene = FbxScene::Create(manager, "");

		// this class is fbx file open 
		FbxImporter* importer = FbxImporter::Create(manager, "");

		// Open the fbx file
		result = importer->Initialize(filePath.c_str());
		if (!result)
		{
			return false;
		}

		// Read in fbx infomation
		importer->Import(scene);

		// インポーターはファイル開いてsceneに橋渡しするだけ
		// 以降、使わないから破棄
		importer->Destroy();
		importer = nullptr;

		// 軸の設定
		FbxAxisSystem ourAxisSystem = FbxAxisSystem::DirectX;

		// OpenGL系の軸
		if (axis == eAxisSystem::eAxisOpenGL)
		{
			ourAxisSystem = FbxAxisSystem::OpenGL;
		}

		// DirectX系
		FbxAxisSystem sceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
		if (sceneAxisSystem != ourAxisSystem)
		{
			FbxAxisSystem::DirectX.ConvertScene(scene);
		}

		// 単位系の統一
		FbxSystemUnit sceneSystemUnit = scene->GetGlobalSettings().GetSystemUnit();
		if (sceneSystemUnit.GetScaleFactor() != 1.0)
		{
			// センチメーター単位にコンバートする
			FbxSystemUnit::cm.ConvertScene(scene);
		}


		//	Get the root node
		FbxNode* rootNode = scene->GetRootNode();

		if (!rootNode)
		{
			return false;
		}

		// 全てのポリゴンを三角形化
		TriangulatedPolygons(scene, rootNode);

		// Get the root node child
		const unsigned int childCount = rootNode->GetChildCount();

		for (unsigned int i = 0; i < childCount; i++)
		{
			GetMesh(rootNode->GetChild(i));
		}

		manager->Destroy();
		manager = nullptr;
		return true;
	}

	void FbxLoader::TriangulatedPolygons(FbxScene* scene, FbxNode* node){
		FbxNodeAttribute* lNodeAttribute = node->GetNodeAttribute();

		if (lNodeAttribute)
		{
			switch (lNodeAttribute->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh:
			case FbxNodeAttribute::eNurbs:
			case FbxNodeAttribute::eNurbsSurface:
			case FbxNodeAttribute::ePatch:
			{
				FbxGeometryConverter converter(node->GetFbxManager());

				// どんな形状も三角形化
				converter.Triangulate(scene, true);
			}
			default:
				break;
			}
		}


		const int childCount = node->GetChildCount();

		for (int index = 0; index < childCount; ++index)
		{
			// 子ノードを探索
			TriangulatedPolygons(scene, node->GetChild(index));
		}
	}

	void FbxLoader::GetMesh(FbxNode* node){

		// Get node attribute 
		FbxNodeAttribute* attribute = node->GetNodeAttribute();

		switch (attribute->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh:
			// find Mesh!!!
		{
			FbxMesh* mesh = node->GetMesh();
			GetVertexPosition(mesh);
			GetVertexNomal(mesh);
			GetVertexUV(mesh);
			GetVertexColor(mesh);
			GetMaterial(mesh);
		}
		break;

		default:
			break;
		}

		// child node Recursive exploration
		const unsigned int childCount = node->GetChildCount();
		for (unsigned int i = 0; i < childCount; ++i)
		{
			GetMesh(node->GetChild(i));
		}
		return;
	}

	// 座標位置などの取得
	void FbxLoader::GetVertexPosition(FbxMesh* mesh){
		// Get the number of polygons
		m_polygonCount = mesh->GetPolygonCount();

		m_polygonSize = new unsigned long[m_polygonCount];
		for (int i = 0; i < m_polygonCount; i++)
		{
			m_polygonSize[i] = mesh->GetPolygonSize(i);

		}

		// Get the all number of vertex
		m_meshElements._vertexCount = mesh->GetControlPointsCount();

		// Get the number of index
		m_meshElements._indexCount = mesh->GetPolygonVertexCount();

		// Get the vertex buffer
		FbxVector4* vertex = mesh->GetControlPoints();

		m_vertexBuffer = new ModelProperty::VertexType[m_meshElements._vertexCount];

		for (int i = 0; i < m_meshElements._vertexCount; i++)
		{
			// X座標取得（英語でかくのムズイ）
			m_vertexBuffer[i]._position._x = static_cast<float>(vertex[i][0]);
			m_vertexBuffer[i]._position._y = static_cast<float>(vertex[i][1]);
			m_vertexBuffer[i]._position._z = static_cast<float>(vertex[i][2]);
		}


		// Get the index buffer
		int* index = mesh->GetPolygonVertices();
		m_indexBuffer = new unsigned long[m_meshElements._indexCount];

		for (int i = 0; i < m_meshElements._indexCount; i++)
		{
			m_indexBuffer[i] = index[i];
		}
		return;
	}

	void FbxLoader::GetVertexColor(FbxMesh* mesh){
		// 頂点カラーセット数を取得
		unsigned int vertexColorLayerCount = mesh->GetElementVertexColorCount();

		for (unsigned int i = 0; i < vertexColorLayerCount; i++)
		{
			// 法線セットを取得
			FbxGeometryElementVertexColor* color = mesh->GetElementVertexColor(i);


			FbxGeometryElement::EMappingMode mapping = color->GetMappingMode();
			FbxGeometryElement::EReferenceMode reference = color->GetReferenceMode();

			// 判別
			switch (mapping)
			{
			case FbxGeometryElement::eByControlPoint:
				break;

			case FbxGeometryElement::eByPolygon:
				break;

			case FbxGeometryElement::eByPolygonVertex:
				if (reference == FbxGeometryElement::eIndexToDirect)
				{
					FbxLayerElementArrayTemplate<int>* index = &color->GetIndexArray();

					int indexCount = index->GetCount();

					m_vertexBuffer->_color = new ModelProperty::VertexColor[indexCount];

					// Get vertex color
					for (unsigned int j = 0; j < indexCount; j++)
					{
						m_vertexBuffer->_color[j]._red = static_cast<float>(color->GetDirectArray().GetAt(index->GetAt(j))[0]);
						m_vertexBuffer->_color[j]._green = static_cast<float>(color->GetDirectArray().GetAt(index->GetAt(j))[1]);
						m_vertexBuffer->_color[j]._blue = static_cast<float>(color->GetDirectArray().GetAt(index->GetAt(j))[2]);
						m_vertexBuffer->_color[j]._alpha = static_cast<float>(color->GetDirectArray().GetAt(index->GetAt(j))[3]);
					}
				}
				else
					if (reference == FbxGeometryElement::eDirect)
					{

					}
				break;
			}

		}
	}

	// 法線取得
	void FbxLoader::GetVertexNomal(FbxMesh* mesh){
		// 法線セット数を取得
		unsigned int nomalLayerCount = mesh->GetElementNormalCount();

		// レイヤー数分回す
		for (int i = 0; i < nomalLayerCount; i++)
		{
			// 法線セットを取得
			FbxGeometryElementNormal* normal = mesh->GetElementNormal(i);

			// マッピングモードの取得
			FbxGeometryElement::EMappingMode mapping = normal->GetMappingMode();
			// リファレンスモードの取得
			FbxGeometryElement::EReferenceMode reference = normal->GetReferenceMode();

			// 法線数を取得
			m_meshElements._normalCount = normal->GetDirectArray().GetCount();
			m_vertexBuffer->_normal = new ModelProperty::VertexNomal[m_meshElements._normalCount];

			// マッピングモードの判別
			switch (mapping)
			{
			case FbxGeometryElement::eByControlPoint:
				// リファレンスモードの判別

				if (reference == FbxGeometryElement::eDirect)
				{

					// eDirectの場合データは順番に格納されているのでそのまま保持
					for (int j = 0; j < m_meshElements._normalCount; j++)
					{
						m_vertexBuffer->_normal[j]._x = static_cast<float>(normal->GetDirectArray().GetAt(j)[0]);
						m_vertexBuffer->_normal[j]._y = static_cast<float>(normal->GetDirectArray().GetAt(j)[1]);
						m_vertexBuffer->_normal[j]._z = static_cast<float>(normal->GetDirectArray().GetAt(j)[2]);
					}
				}
				else
					if (reference == FbxGeometryElement::eIndexToDirect)
					{

					}
				break;
			case FbxGeometryElement::eByPolygonVertex:
				if (reference == FbxGeometryElement::eDirect)
				{
					for (int j = 0; j < m_meshElements._normalCount; j++)
					{
						m_vertexBuffer->_normal[j]._x = static_cast<float>(normal->GetDirectArray().GetAt(j)[0]);
						m_vertexBuffer->_normal[j]._y = static_cast<float>(normal->GetDirectArray().GetAt(j)[1]);
						m_vertexBuffer->_normal[j]._z = static_cast<float>(normal->GetDirectArray().GetAt(j)[2]);
					}
				}
				else
					if (reference == FbxGeometryElement::eIndexToDirect)
					{

					}
				break;
			default:
				break;
			}
		}
		return;
	}

	// UV取得関数
	void FbxLoader::GetVertexUV(FbxMesh* mesh){
		// UVセット数を取得
		unsigned int uvLayerCount = mesh->GetElementUVCount();

		for (int i = 0; i < uvLayerCount; i++)
		{
			// UVバッファの取得
			FbxGeometryElementUV* UV = mesh->GetElementUV(i);

			// Get now mapping mode
			FbxGeometryElement::EMappingMode mapping = UV->GetMappingMode();

			// Get now reference mode
			FbxGeometryElement::EReferenceMode reference = UV->GetReferenceMode();

			m_meshElements._uvCount = UV->GetDirectArray().GetCount();

			switch (mapping)
			{
			case FbxGeometryElement::eByControlPoint:
				break;

			case FbxGeometryElement::eByPolygonVertex:

				if (reference == FbxGeometryElement::eDirect)
				{

				}
				else
					if (reference == FbxGeometryElement::eIndexToDirect)
					{
						FbxLayerElementArrayTemplate<int>* uvIndex = &UV->GetIndexArray();
						int uvIndexCount = uvIndex->GetCount();

						// Save UV
						ModelProperty::UVPoint sample;
						for (int i = 0; i < uvIndexCount; i++)
						{
							sample._u = static_cast<float>(UV->GetDirectArray().GetAt(uvIndex->GetAt(i))[0]);
							sample._v = 1.0f - static_cast<float>(UV->GetDirectArray().GetAt(uvIndex->GetAt(i))[1]);
							m_vertexBuffer->_uv._buffer = sample;
						}

						// Get uvSet name
						m_vertexBuffer->_uv._uvSetName = UV->GetName();
					}
				break;

			case FbxGeometryElement::eByEdge:
				break;

			case FbxGeometryElement::eByPolygon:
				break;
			default:
				break;
			}

		}
		return;
	}

	void FbxLoader::GetMaterial(FbxMesh* mesh){
		FbxNode* node = mesh->GetNode();
		FbxModelProperty::FbxMeshNode meshNode;
		m_meshElements._materialCount = node->GetMaterialCount();

		for (int materialID = 0; materialID < m_meshElements._materialCount; ++materialID)
		{
			FbxSurfaceMaterial* material = node->GetMaterial(materialID);

			if (!material)
			{

				continue;
			}
			ModelProperty::Material destMaterial;
			CopyMaterialData(material, &destMaterial);
			meshNode._material.push_back(destMaterial);
		}
		ComputeNodeMatrix(node, &meshNode, node->GetScene());
		m_meshNode.push_back(meshNode);
	}

	void FbxLoader::CopyMaterialData(FbxSurfaceMaterial* material, ModelProperty::Material* destMaterial){

		if (!material)
		{

			return;
		}
		if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
		{
			destMaterial->_type = ModelProperty::Material::eMaterialType::eMaterialLambert;
		}
		else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
		{
			destMaterial->_type = ModelProperty::Material::eMaterialType::eMaterialPhong;
		}

		const FbxDouble3 emmisive = GetMaterialPropertey(material,
			FbxSurfaceMaterial::sEmissive, FbxSurfaceMaterial::sEmissiveFactor, &destMaterial->_emmisive);
		SetFbxColor(destMaterial->_emmisive, emmisive);

		const FbxDouble3 ambient = GetMaterialPropertey(material,
			FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor, &destMaterial->_ambient);
		SetFbxColor(destMaterial->_ambient, ambient);

		const FbxDouble3 diffuse = GetMaterialPropertey(material,
			FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor, &destMaterial->_diffuse);
		SetFbxColor(destMaterial->_diffuse, diffuse);

		const FbxDouble3 specular = GetMaterialPropertey(material,
			FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor, &destMaterial->_specular);
		SetFbxColor(destMaterial->_specular, specular);


		FbxProperty tranceparencyFaxtoryProperty = material->FindProperty(FbxSurfaceMaterial::sTransparencyFactor);
		if (tranceparencyFaxtoryProperty.IsValid())
		{
			double tranceparencyFactory = tranceparencyFaxtoryProperty.Get<FbxDouble>();
			destMaterial->_transparencyFactor = static_cast<float>(tranceparencyFactory);
		}

		// Specular Power
		FbxProperty shininessProperty = material->FindProperty(FbxSurfaceMaterial::sShininess);
		if (shininessProperty.IsValid())
		{
			double shininess = shininessProperty.Get<FbxDouble>();
			destMaterial->_shininess = static_cast<float>(shininess);
		}
	}

	void FbxLoader::ComputeNodeMatrix(FbxNode* node, FbxModelProperty::FbxMeshNode* meshNode, FbxScene* scene){

		if (!node || !meshNode)
		{

			return;
		}

		FbxAnimEvaluator* evaluator = scene->GetAnimationEvaluator();
		FbxMatrix global;
		global.SetIdentity();

		if (node != scene->GetRootNode())
		{
			global = evaluator->GetNodeGlobalTransform(node);

			FbxMatrixToFloat16(&global, meshNode->_matrix4x4);

		}
		else
		{
			FbxMatrixToFloat16(&global, meshNode->_matrix4x4);
		}
	}

	void FbxLoader::SetFbxColor(ModelProperty::MaterialElement& destColor, FbxDouble3 srcColor){
		destColor._color._red = static_cast<float>(srcColor[0]);
		destColor._color._green = static_cast<float>(srcColor[1]);
		destColor._color._blue = static_cast<float>(srcColor[2]);
		destColor._color._alpha = 1.0f;

	}

	FbxDouble3 FbxLoader::GetMaterialPropertey(
		const FbxSurfaceMaterial* material,
		std::string propertyName,
		std::string factorPropertyName,
		ModelProperty::MaterialElement* element){

		element->_type = ModelProperty::MaterialElement::eMaterialElementType::eElementNone;

		FbxDouble3 result(0, 0, 0);
		const FbxProperty property = material->FindProperty(propertyName.c_str());
		const FbxProperty factorProperty = material->FindProperty(factorPropertyName.c_str());

		if (property.IsValid() && factorProperty.IsValid())
		{
			result = property.Get<FbxDouble3>();
			double factor = factorProperty.Get<FbxDouble>();

			if (factor != 1)
			{
				result[0] *= factor;
				result[1] *= factor;
				result[2] *= factor;
			}

			element->_type = ModelProperty::MaterialElement::eMaterialElementType::eElementColor;
		}

		if (property.IsValid())
		{
			int existTextureCount = 0;
			const int textureCount = property.GetSrcObjectCount<FbxFileTexture>();

			for (int i = 0; i < textureCount; ++i)
			{
				FbxFileTexture* fileTexture = property.GetSrcObject<FbxFileTexture>(i);
				if (!fileTexture)
				{
					continue;
				}

				FbxString uvsetName = fileTexture->UVSet.Get();
				std::string uvSetString = uvsetName.Buffer();
				std::string filePath = fileTexture->GetFileName();
				std::cout << uvSetString << std::endl;
				element->_texture[uvSetString].push_back(filePath);

				++existTextureCount;
			}

			const int layerdTextureCount = property.GetDstObjectCount<FbxLayeredTexture>();

			for (int j = 0; j < layerdTextureCount; ++j)
			{
				FbxLayeredTexture* layeredTexture = property.GetSrcObject<FbxLayeredTexture>(j);

				const int textureFileCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

				for (int k = 0; k < textureFileCount; ++k)
				{
					FbxFileTexture* fileTexture = layeredTexture->GetSrcObject<FbxFileTexture>(k);

					if (!fileTexture)
					{
						continue;
					}

					FbxString uvsetName = fileTexture->UVSet.Get();
					std::string uvsetString = uvsetName.Buffer();
					std::string filePath = fileTexture->GetFileName();

					element->_texture[uvsetString].push_back(filePath);

					++existTextureCount;
				}
			}

			if (existTextureCount > 0)
			{
				if (element->_type == ModelProperty::MaterialElement::eMaterialElementType::eElementColor)
				{
					element->_type = ModelProperty::MaterialElement::eMaterialElementType::eElementBoth;
				}
				else
				{
					element->_type = ModelProperty::MaterialElement::eMaterialElementType::eElementTexture;
				}
			}
		}
		return result;
	}

	void FbxLoader::GetInfo(){
		std::cout << "The number of polygons\t:" << m_polygonCount << std::endl;
		std::cout << "The number of vertexes\t:" << m_meshElements._vertexCount << std::endl;
		std::cout << "The number of index\t:" << m_meshElements._indexCount << std::endl;
		std::cout << "The number of normal\t:" << m_meshElements._normalCount << std::endl;
		std::cout << "The number of UV\t:" << m_meshElements._uvCount << std::endl;
		std::cout << "The number of Material\t:" << m_meshElements._materialCount << std::endl;

	}

	void FbxLoader::GetMeshElements(ModelProperty::MeshElements& elements){
		elements = m_meshElements;
		return;

	}

	ModelProperty::VertexType* FbxLoader::GetVertex(){
		return m_vertexBuffer;
	}
	unsigned long* FbxLoader::GetIndex(){
		return m_indexBuffer;
	}
}