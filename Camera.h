//#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"glut.h"
#include"Normal.h"
#include<math.h>
#include<Windows.h>
#include<vector>
using namespace std;

class Camera
{
public:
	//позиция камеры/положение точки наблюдателя/
	Vector3f Position;	
	//направление наблюдения
	Vector3f View;	
	//вектор поворота сцены
	Vector3f UpVector;	

	//конструктор;	
	Camera();
	//установка позиции камеры
	void Camera_Position(float posX, float posY, float posZ,
		float viewX, float viewY, float viewZ,
		float upX, float upY, float upZ);	
	//установка вида с помощью мыши
	void Set(GLint width, GLint height);	
	//передвижение камеры вперед/назад
	void Move_Camera_Up_Down(float speed);	
	//передвижение камеры вправо/влево
	void Move_Camera_Right_Left(float speed);
	//передвижение камеры вверх/вниз
	void Move_Camera(float speed);
	//вращение камеры вокруг заданной оси
	void Rotate_Around_Axis(float angle, float x, float y, float z);	
	//вращение камеры вокруг наблюдателя
	void Rotate_Around_Viewer(Vector3f vCenter, float angle, float x, float y, float z);
};
