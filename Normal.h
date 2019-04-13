#include<math.h>

//ВЫЧИСЛЕНИЕ НОРМАЛИ/ОТРИСОВКА ПОЛИГОНОВ/ ПРОТИВ/!!!!/ ЧАСОВОЙ СТРЕЛКИ

class Vector3f
{
public:
	float x, y, z;
	//конструктор по умолчанию
	Vector3f() {};	

	//конструктор
	Vector3f(float _x, float _y, float _z)	
	{
		x = _x;
		y = _y;
		z = _z;
	}

	//Переопределение оператора +
	Vector3f operator + (Vector3f _Vector)
	{
		return Vector3f(_Vector.x + x, _Vector.y + y, _Vector.z + z);
	}

	//Переопределение оператора -
	Vector3f operator - (Vector3f _Vector)
	{
		return Vector3f(x - _Vector.x, y - _Vector.y, z - _Vector.z);
	}

	//Переопределение оператора *
	Vector3f operator * (float num)
	{
		return Vector3f(x * num, y * num, z * num);
	}

	//Переопределение оператора /
	Vector3f operator / (float num)
	{
		return Vector3f(x / num, y / num, z / num);
	}
};

//вычисление нормали для двух векторов
Vector3f Calc_Normal(Vector3f a, Vector3f b);

//вычисление нормы вектора
float Calc_Norm(Vector3f a);

//нормализация вектора
Vector3f Normalize(Vector3f a);

//скалярное произведдение вух векторов
float Calc_Scal(Vector3f a, Vector3f b);

//нахождение вектора межжду двумя точками
Vector3f Find_Vector(Vector3f point_a, Vector3f point_b);

//вычисление нормали полигона
Vector3f Calc_Normal_of_Poligon(Vector3f point_1, Vector3f point_2, Vector3f point_3);