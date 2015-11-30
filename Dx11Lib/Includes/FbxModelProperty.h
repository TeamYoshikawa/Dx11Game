
#include "ModelProperty.h"

namespace FbxModelProperty
{
	// Fbxから取り込む用
	struct FbxMeshNode{

		~FbxMeshNode(){
			_uvSetID.clear();
			_index.clear();

		}

		std::string _name; // ノード名
		std::string _parentName; // 親ノード名（いない場合はnullが入る）

		ModelProperty::MeshElements _elements; // メッシュが保持するデータ構造
		std::vector <ModelProperty::Material> _material; // マテリアル

		std::unordered_map<std::string, int> _uvSetID;
		std::vector<unsigned int> _index;			// インデックス配列

		float _matrix4x4[16];
	};
}
