#include"Normal.h"

Vector3f Calc_Normal(Vector3f a, Vector3f b)
 {

	Vector3f n;

	n.x = ((a.y * b.z) - (a.z * b.y));
	n.y = ((a.z * b.x) - (a.x * b.z));
	n.z = ((a.x * b.y) - (a.y * b.x));

	return n;
}

float Calc_Norm(Vector3f a) {
	return (float)sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

Vector3f Normalize(Vector3f a) {
	float norm = Calc_Norm(a);
	a = a / norm;
	return a;
}

float Calc_Scal(Vector3f a, Vector3f b){
	return ((a.x * b.x) + (a.y * b.y) + (a.z + b.z));

}

Vector3f Find_Vector(Vector3f point_a, Vector3f point_b) {
	Vector3f vector;

	vector.x = point_a.x - point_b.x;
	vector.y = point_a.y - point_b.y;
	vector.z = point_a.z - point_b.z;

	return vector;
}

Vector3f Calc_Normal_of_Poligon(Vector3f point_1, Vector3f point_2, Vector3f point_3) {
	Vector3f ba = Find_Vector(point_3, point_2);
	Vector3f ca = Find_Vector(point_1, point_2);
	Vector3f norm_ = Calc_Normal(ba, ca);
	norm_ = Normalize(norm_);
	return norm_;
}