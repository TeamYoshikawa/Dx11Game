#ifndef _VECTOR3_H
#define _VECTOR3_H
#include <D3DX10math.h>

namespace Dx11Math{
	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(Vector3&);
		~Vector3();

		void Normalize();


	public:

		float _x, _y, _z;

	public:
		void operator = (Vector3 input){
			_x = input._x;
			_y = input._y;
			_z = input._z;
			return;
		};

		void operator = (D3DXVECTOR3 input){
			_x = input.x;
			_y = input.y;
			_z = input.z;
			return;
		};

		Vector3 operator + (Vector3 input){
			Vector3 output;
			output._x = _x + input._x;
			output._y = _y + input._y;
			output._z = _z + input._z;

			return output;
		};

		void operator += (Vector3 input){

			_x += input._x;
			_y += input._y;
			_z += input._z;
			return;
		};

		Vector3 operator + (float input){
			Vector3 output;
			output._x = _x + input;
			output._y = _y + input;
			output._z = _z + input;

			return output;
		};

		void operator += (float input){

			_x += input;
			_y += input;
			_z += input;
			return;
		};

		Vector3 operator - (Vector3 input){
			Vector3 output;
			output._x = _x - input._x;
			output._y = _y - input._y;
			output._z = _z - input._z;

			return output;
		};

		void operator -= (Vector3 input){

			_x -= input._x;
			_y -= input._y;
			_z -= input._z;
			return;
		};

		Vector3 operator - (float input){
			Vector3 output;
			output._x = _x - input;
			output._y = _y - input;
			output._z = _z - input;

			return output;
		};

		void operator -= (float input){

			_x -= input;
			_y -= input;
			_z -= input;
			return;
		};

		Vector3 operator * (Vector3 input){
			Vector3 output;
			output._x = _x * input._x;
			output._y = _y * input._y;
			output._z = _z * input._z;

			return output;
		};

		Vector3  operator *= (Vector3 input){
			Vector3 output;
			_x *= input._x;
			_y *= input._y;
			_z *= input._z;

			return output;
		};


		Vector3 operator * (float input){
			Vector3 output;
			output._x = _x * input;
			output._y = _y * input;
			output._z = _z * input;

			return output;
		};

		void operator *= (float input){

			_x *= input;
			_y *= input;
			_z *= input;
			return;
		};

		Vector3 operator / (float input){
			Vector3 output;
			output._x = _x / input;
			output._y = _y / input;
			output._z = _z / input;

			return output;
		};

		void  operator /= (float input){
		
			_x /= input;
			_y /= input;
			_z /= input;
			return;
		};

		bool  operator == (Vector3 input){
			if (_x != input._x ||
				_y != input._y ||
				_z != input._z)
			{
				return false;
			}
			return true;
		};

		bool  operator != (Vector3 input){
			if (_x == input._x ||
				_y == input._y ||
				_z == input._z)
			{
				return false;
			}
			return true;
		};

		bool operator < (Vector3 input){

			if (_x < input._x ||
				_y < input._y ||
				_z < input._z)
			{
				return false;
			}
			return true;
		};

		bool operator <= (Vector3 input){

			if (_x <= input._x ||
				_y <= input._y ||
				_z <= input._z)
			{
				return false;
			}
			return true;
		};

		bool operator > (Vector3 input){

			if (_x > input._x ||
				_y > input._y ||
				_z > input._z)
			{
				return false;
			}
			return true;
		};

		bool operator >= (Vector3 input){

			if (_x >= input._x ||
				_y >= input._y ||
				_z >= input._z)
			{
				return false;
			}
			return true;
		};


	};
}
#endif