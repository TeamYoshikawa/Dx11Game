#ifndef _MODELPROPERTY_H
#define _MODELPROPERTY_H

#include <D3D11.h>
#include <D3DX10math.h>
#include <string>
#include <list>
#include <memory>
#include <unordered_map>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
namespace ModelProperty{

	struct UVSet{
		UVSet(){
			_uvSetName = "Null";
			_texture.clear();
		}
		~UVSet(){
			_texture.clear();
		}
		std::string _uvSetName;
		std::list<std::string> _texture;
	};

	struct VertexType{
		VertexType(){
	
			
			SecureZeroMemory(&_position, sizeof(_position));
			SecureZeroMemory(&_color, sizeof(_color));
			SecureZeroMemory(&_uv, sizeof(_uv));
			SecureZeroMemory(&_normal, sizeof(_normal));
		}
		~VertexType(){
			Deleter();
		}

		void Deleter(){
			SecureZeroMemory(&_position, sizeof(_position));
			SecureZeroMemory(&_color, sizeof(_color));
			SecureZeroMemory(&_uv, sizeof(_uv));
			SecureZeroMemory(&_normal, sizeof(_normal));

		}

		DxMath::Vector3 _position;
		DxMath::Vector4 _color;
		DxMath::Vector2 _uv;
		DxMath::Vector3 _normal;
		
		
		UVSet _uvSet;
	};

	struct MeshElements{
		MeshElements(){
			_vertexCount = 0;
			_indexCount = 0;
			_uvCount = 0;
			_normalCount = 0;
			_materialCount = 0;

		}

		~MeshElements(){
			_vertexCount = 0;
			_uvCount = 0;
			_normalCount = 0;
			_materialCount = 0;
		}
		unsigned long _polygonCount;
		unsigned long _vertexCount;
		unsigned long _indexCount;
		unsigned long _uvCount;
		unsigned int _uvSetCount;
		unsigned long _normalCount;
		unsigned int _materialCount;


	};


	struct MaterialElement{
		enum class eMaterialElementType{
			eElementNone = 0,
			eElementColor,
			eElementTexture,
			eElementBoth,
			eElementMax
		};

		// UVセット名,テクスチャパス名(1つのUVSetに複数のテクスチャがある場合がある)
		std::unordered_map<std::string, std::vector<std::string>> _texture;
		eMaterialElementType _type;
		DxMath::Vector4 _color;
	};

	struct Material{

		// FBXのマテリアルは二種類しかない
		enum class eMaterialType{
			eMaterialLambert = 0,
			eMaterialPhong
		};

		eMaterialType _type;
		MaterialElement _ambient;
		MaterialElement _diffuse;
		MaterialElement _emmisive;
		MaterialElement _specular;

		float _shininess; // 光
		float _transparencyFactor;	// 透過度
	};

	struct MaterialConstantData{
		DxMath::Vector4 _ambient;
		DxMath::Vector4 _diffuse;
		DxMath::Vector4 _specular;
		DxMath::Vector4 _emmisive;
	};

	struct MaterialData{
		DxMath::Vector4 _ambient;
		DxMath::Vector4 _diffuse;
		DxMath::Vector4 _specular;
		DxMath::Vector4 _emmisive;
		float _specularPower;
		float _tranceparencyFactory;
		MaterialConstantData _materialConstantData;
	};

	
}

#endif