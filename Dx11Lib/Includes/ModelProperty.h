#ifndef _MODELPROPERTY_H
#define _MODELPROPERTY_H

#include <D3D11.h>
#include <D3DX10math.h>
#include <string>
#include <list>
#include <memory>
#include <unordered_map>
namespace ModelProperty{

	struct VertexPosition{
		VertexPosition(){
			_x = _y = _z = 0.0f;
		}
		~VertexPosition() = default;

		void operator =(D3DXVECTOR3 vector){
			_x = vector.x;
			_y = vector.y;
			_z = vector.z;
		}
		// 座標の位置
		float _x, _y, _z;
	};

	struct VertexNomal{
		VertexNomal(){

			_x = _y = _z = 0.0f;
		}
		~VertexNomal() = default;
		void operator =(D3DXVECTOR3 vector){
			_x = vector.x;
			_y = vector.y;
			_z = vector.z;
		}
		// 法線の位置
		float _x, _y, _z;
	};

	struct UVPoint{
		UVPoint(){
			_u = _v = 0.0f;
		}
		UVPoint(const float u,const float v){
			_u = u;
			_v = v;
		}
		~UVPoint() = default;
		bool operator==(UVPoint& val)
		{
			if (this->_u == val._u&&this->_v == val._v)
			{
				return true;
			}
			return false;
		}

		void operator =(D3DXVECTOR2 vector){
			_u = vector.x;
			_v = vector.y;
		}

		float _u, _v;
	};

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

	struct Color{
		Color(){
			_red = _blue =
				_green = _alpha = 0.0f;
		}
		~Color() = default;

		void operator =(D3DXVECTOR4 vector){
			_red = vector.x;
			_green = vector.y;
			_blue = vector.z;
			_alpha = vector.w;
		}
		float _red;
		float _green;
		float _blue;
		float _alpha;
	};

	struct VertexType{
		VertexType(){
	
			
			SecureZeroMemory(&_position, sizeof(_position));
			SecureZeroMemory(&_color, sizeof(_color));
			SecureZeroMemory(&_uv, sizeof(_uv));
			_normal = nullptr;
		}
		~VertexType(){
			Deleter();
		}

		void Deleter(){
			SecureZeroMemory(&_position, sizeof(_position));
			SecureZeroMemory(&_color, sizeof(_color));
			SecureZeroMemory(&_uv, sizeof(_uv));
			if (_normal)
			{
				delete _normal;
				_normal = nullptr;
			}

		}

		VertexPosition _position;
		Color _color;
		UVPoint _uv;
		VertexNomal* _normal;
		
		
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
		Color _color;
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
		Color _ambient;
		Color _diffuse;
		Color _specular;
		Color _emmisive;
	};

	struct MaterialData{
		Color _ambient;
		Color _diffuse;
		Color _specular;
		Color _emmisive;
		float _specularPower;
		float _tranceparencyFactory;
		MaterialConstantData _materialConstantData;
	};

	
}

#endif