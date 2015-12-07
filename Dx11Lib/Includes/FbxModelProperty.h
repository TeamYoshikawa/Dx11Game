#ifndef _FBXMODELPROPERTY_H
#define _FBXMODELPROPERTY_H
#include "Texture.h"
#include "ModelProperty.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <fbxsdk.h>
namespace FbxModelProperty
{
	// Fbxから取り込む用
	struct FbxMeshNode{

		~FbxMeshNode(){
			Release();

		}

		void Release()
		{
			_uvSetID.clear();
			_texcoord.clear();
			_material.clear();
			_index.clear();
			_position.clear();
			_normal.clear();
		}

		std::vector<unsigned int>		_index;				// インデックス配列
		std::vector<FbxVector4>			_position;		// ポジション配列
		std::vector<FbxVector4>			_normal;			// 法線配列
		std::vector<FbxVector2>			_texcoord;

		std::string _name; // ノード名
		std::string _parentName; // 親ノード名（いない場合はnullが入る）

		ModelProperty::MeshElements _elements; // メッシュが保持するデータ構造

		std::vector <ModelProperty::Material> _material; // マテリアル

		std::unordered_map<std::string, int> _uvSetID;

		float _matrix4x4[16];
	};

	struct FbxMeshBuffer{
		FbxMeshBuffer(){
			_vertexBuffer = nullptr;
			_indexBuffer = nullptr;
		

		}

		~FbxMeshBuffer(){
			if (_vertexBuffer)
			{
				_vertexBuffer->Release();
				_vertexBuffer = nullptr;
			}

			if (_indexBuffer)
			{
				_indexBuffer->Release();
				_indexBuffer = nullptr;
			}
	
		}
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
	};

}

#endif