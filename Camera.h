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
	//������� ������/��������� ����� �����������/
	Vector3f Position;	
	//����������� ����������
	Vector3f View;	
	//������ �������� �����
	Vector3f UpVector;	

	//�����������;	
	Camera();
	//��������� ������� ������
	void Camera_Position(float posX, float posY, float posZ,
		float viewX, float viewY, float viewZ,
		float upX, float upY, float upZ);	
	//��������� ���� � ������� ����
	void Set(GLint width, GLint height);	
	//������������ ������ ������/�����
	void Move_Camera_Up_Down(float speed);	
	//������������ ������ ������/�����
	void Move_Camera_Right_Left(float speed);
	//������������ ������ �����/����
	void Move_Camera(float speed);
	//�������� ������ ������ �������� ���
	void Rotate_Around_Axis(float angle, float x, float y, float z);	
	//�������� ������ ������ �����������
	void Rotate_Around_Viewer(Vector3f vCenter, float angle, float x, float y, float z);
};
