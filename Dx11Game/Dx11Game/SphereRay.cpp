#include "Sphere.h"

using namespace DxMath;
using namespace DxModel;
bool Sphere::RayIntersect(Vector3 origin, Vector3 direction, float scalar = 1){

	direction *= scalar;

	float xa = origin._x - this->Translation()._x;
	float ya = origin._y - this->Translation()._y;
	float za = origin._z - this->Translation()._z;

	float a = ((direction._x*direction._x) + (direction._y*direction._y) + (direction._z*direction._z));
	float b = 2.0f * ((direction._x * xa) + (direction._y * ya) + (direction._z * za));
	float c = (xa*xa) + (ya*ya) + (za*za) - (this->Scaling()._x * this->Scaling()._x);

	float d = b * b - 4.0f * a * c;
	
	if (d < 0.0f)return false;

	d = sqrtf(d);
	float t0 = (-b + d) / (2.0f * a);
	float t1 = (-b - d) / (2.0f * a);

	float t = 2.0f;
	if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t))t = t0;
	if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t))t = t1;
	if (t > 1.0f)return false;

	return true;
}