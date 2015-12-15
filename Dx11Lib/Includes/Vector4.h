#ifndef _VECTOR4_H
#define _VECTOR4_H
#include <D3DX10math.h>
#include "Vector3.h"
namespace DxMath{
	class Vector4
	{

		public:
			float _x, _y, _z, _w;
		public:
			Vector4();
			Vector4(float, float, float, float);
			Vector4(Vector3);
			Vector4(Vector4&);
			Vector4(const Vector4&);
			~Vector4();

			void Normalize();
			float Dot(Vector4&);
			Vector4 Cross(Vector4&);

			float GetVectorLength();

		public:
			void operator = (Vector4& );
			void operator = (const Vector4&);
			void operator = (Vector3& );
			void operator = (const Vector3&);
			void operator = (float& );
			void operator = (D3DXVECTOR4& );

			Vector4 operator + (Vector4 );
			void operator += (Vector4 );
			Vector4 operator + (float );
			void operator += (float );

			Vector4 operator - (Vector4 );
			void operator -= (Vector4 );
			Vector4 operator - (float );
			void operator -= (float );

	
			Vector4 operator * (float );
			Vector4 operator * (D3DXMATRIX );
			void operator *= (float );

			Vector4 operator / (float );
			void  operator /= (float );

			bool  operator == (Vector4 );
			bool  operator != (Vector4 );
			bool operator < (Vector4 );
			bool operator <= (Vector4 );
			bool operator > (Vector4 );
			bool operator >= (Vector4 );
	};
}
#endif