#include<math.h>

//���������� �������/��������� ���������/ ������/!!!!/ ������� �������

class Vector3f
{
public:
	float x, y, z;
	//����������� �� ���������
	Vector3f() {};	

	//�����������
	Vector3f(float _x, float _y, float _z)	
	{
		x = _x;
		y = _y;
		z = _z;
	}

	//��������������� ��������� +
	Vector3f operator + (Vector3f _Vector)
	{
		return Vector3f(_Vector.x + x, _Vector.y + y, _Vector.z + z);
	}

	//��������������� ��������� -
	Vector3f operator - (Vector3f _Vector)
	{
		return Vector3f(x - _Vector.x, y - _Vector.y, z - _Vector.z);
	}

	//��������������� ��������� *
	Vector3f operator * (float num)
	{
		return Vector3f(x * num, y * num, z * num);
	}

	//��������������� ��������� /
	Vector3f operator / (float num)
	{
		return Vector3f(x / num, y / num, z / num);
	}
};

//���������� ������� ��� ���� ��������
Vector3f Calc_Normal(Vector3f a, Vector3f b);

//���������� ����� �������
float Calc_Norm(Vector3f a);

//������������ �������
Vector3f Normalize(Vector3f a);

//��������� ������������� ��� ��������
float Calc_Scal(Vector3f a, Vector3f b);

//���������� ������� ������ ����� �������
Vector3f Find_Vector(Vector3f point_a, Vector3f point_b);

//���������� ������� ��������
Vector3f Calc_Normal_of_Poligon(Vector3f point_1, Vector3f point_2, Vector3f point_3);