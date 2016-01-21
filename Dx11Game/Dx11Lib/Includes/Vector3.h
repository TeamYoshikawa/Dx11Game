#ifndef _VECTOR3_H
#define _VECTOR3_H
#include <D3DX10math.h>

namespace DxMath{
	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
	
		Vector3(Vector3&);
		Vector3(const Vector3&);
		~Vector3();

		void Normalize();
		float Dot(Vector3&);
		Vector3 Cross(Vector3&);
		float GetVectorLength();
	public:

		float _x, _y, _z;

	public:
		void operator = (Vector3&);
		void operator =(float&);
		void operator =(float);
		void operator=(const Vector3&);
		void operator = (D3DXVECTOR3& );

		Vector3 operator + (Vector3);
		void operator += (Vector3);
		Vector3 operator + (float);
		void operator += (float);
		
		Vector3 operator - (Vector3);
		void operator -= (Vector3);
		Vector3 operator - (float);
		void operator -= (float);
		
		Vector3 operator * (float );
		Vector3 operator * (D3DXMATRIX );
		void operator *= (float );
		
		Vector3 operator / (float );
		void  operator /= (float );
		
		bool  operator == (Vector3 );
		bool  operator != (Vector3 );
		bool operator < (Vector3 );
		bool operator <= (Vector3 );
		bool operator > (Vector3 );
		bool operator >= (Vector3 );


	};
}
#endif