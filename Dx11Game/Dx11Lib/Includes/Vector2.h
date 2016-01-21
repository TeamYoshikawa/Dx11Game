#ifndef _VECTOR2_H
#define _VECTOR2_H
/*
	Vextor2ƒNƒ‰ƒX

*/
#include <D3DX10math.h>
namespace DxMath{
	class Vector2
	{
		public:
			float _x, _y;
		public:
			Vector2();
			Vector2(float, float);
			Vector2(Vector2&);
			Vector2(const Vector2&);
			~Vector2();

			void Normalize();
			float Dot(Vector2&);

			float GetVectorLength();

		public:
			void operator = (Vector2& input);
			void operator = (float input);
			void operator = (D3DXVECTOR2 input);
			Vector2 operator + (Vector2 input);
			void operator += (Vector2 input);
			Vector2 operator + (float input);
			void operator += (float input);

			Vector2 operator - (Vector2 input);
			void operator -= (Vector2 input);
			Vector2 operator - (float input);
			void operator -= (float input);


			Vector2 operator * (float input);
			void operator *= (float input);

			Vector2 operator / (float input);
			void  operator /= (float input);

			bool  operator == (Vector2 input);
			bool  operator != (Vector2 input);
			bool operator < (Vector2 input);
			bool operator <= (Vector2 input);
			bool operator > (Vector2 input);
			bool operator >= (Vector2 input);
	};
}
#endif
