//#pragma once
#include"Camera.h"
#include<fstream>
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#define cam_speed 0.03f					//�������� ����������� ������
#define M_PI       3.14159265358979323846
#define _CRT_SECURE_NO_WARNINGS

GLint width, height;
bool perspective = true;				//��� �������������� ������
float angle = 60;						//���� � ������������� ��������
float mas = 10;							//��������� � ��������������� ��������
int type_of_light;						//��� ��������� �����
vector<Vector3f> figure;				//����� ����� ������ ������	
vector<Vector3f> scales;				//��������������� ������� �������
Camera camera1;							//������
vector<Vector3f> normals;				//������ ��������
bool texture = false;					//��� ����������� �������� �� �������
unsigned int names_tex[5];				//������ �������
bool skeleton = false;					//��� ���������� ������
bool smooth_normal = false;				//����������� ��������
vector <Vector3f> smoothedNormals;		//������ ���������� ��������/�������� ������� � ������ �������
bool show_normal = false;				//����������� ��������
bool Light = false;						//���������/���������� �����
bool show_grid = true;					//��������� �����
bool rot = false;

float TMatrix[4][4];					//������� ������
float RMatrix[4][4];					//������� ��������
float SMatrix[4][4];					//������� ���������������

//��������� ���������� �� ��������� �������
Vector3f multCoord(float _matrix[4][4], Vector3f _vec)
{
	float vec[4] = { _vec.x, _vec.y, _vec.z, 1.0f };
	float resVec[4];

	for (int i = 0; i < 4; i++)
	{
		double s = 0;
		for (int j = 0; j < 4; j++)
			s += _matrix[i][j] * vec[j];
		resVec[i] = s;
	}
	return Vector3f::Vector3f(resVec[0], resVec[1], resVec[2]);
}

//���������� ������� ������
void makeTranslateMatrix(float dx, float dy, float dz)
{
	TMatrix[0][0] = 1; TMatrix[0][1] = 0;
	TMatrix[0][2] = 0; TMatrix[0][3] = dx;
	TMatrix[1][0] = 0; TMatrix[1][1] = 1;
	TMatrix[1][2] = 0; TMatrix[1][3] = dy;
	TMatrix[2][0] = 0; TMatrix[2][1] = 0;
	TMatrix[2][2] = 1; TMatrix[2][3] = dz;
	TMatrix[3][0] = 0; TMatrix[3][1] = 0;
	TMatrix[3][2] = 0; TMatrix[3][3] = 1;
}

//���������� ������� ��������/������������ ������������ ���/
void makeRotateMatrix(float angle, Vector3f Axis)
{
	float c = (float)cos(angle* M_PI / 180.0);
	float s = (float)sin(angle* M_PI / 180.0);
	Vector3f Os = Normalize(Axis);

	RMatrix[0][0] = c + (1 - c)*Os.x*Os.x;
	RMatrix[0][1] = (1 - c)*Os.x*Os.y - s * Os.z;
	RMatrix[0][2] = (1 - c)*Os.x*Os.z + s * Os.y;
	RMatrix[0][3] = 0;
	RMatrix[1][0] = (1 - c)*Os.x*Os.y + s * Os.z;
	RMatrix[1][1] = c + (1 - c)*Os.y*Os.y;
	RMatrix[1][2] = (1 - c)*Os.z*Os.y - s * Os.x;
	RMatrix[1][3] = 0;
	RMatrix[2][0] = (1 - c)*Os.x*Os.z - s * Os.y;
	RMatrix[2][1] = (1 - c)*Os.z*Os.y + s * Os.x;
	RMatrix[2][2] = c + (1 - c)*Os.z*Os.z;
	RMatrix[2][3] = 0;
	RMatrix[3][0] = 0;
	RMatrix[3][1] = 0;
	RMatrix[3][2] = 0;
	RMatrix[3][3] = 1;
}

//���������� ������� ��������
void makeScaleMatrix(float sx, float sy, float sz)
{
	SMatrix[0][0] = sx; SMatrix[0][1] = 0;
	SMatrix[0][2] = 0; SMatrix[0][3] = 0;
	SMatrix[1][0] = 0; SMatrix[1][1] = sy;
	SMatrix[1][2] = 0; SMatrix[1][3] = 0;
	SMatrix[2][0] = 0; SMatrix[2][1] = 0;
	SMatrix[2][2] = sz; SMatrix[2][3] = 0;
	SMatrix[3][0] = 0; SMatrix[3][1] = 0;
	SMatrix[3][2] = 0; SMatrix[3][3] = 1;
}

//������������� ������ ����������������
vector<Vector3f> transform(int num, float angle, Vector3f Axis)
{
	vector<Vector3f> _quadr;
	_quadr = figure;

	//���� ���� �� ����� ���� - ��������� �����������
	if (angle != 0)
	{
		makeRotateMatrix(angle, Axis);
		_quadr[0] = multCoord(RMatrix, _quadr[0]);
		_quadr[1] = multCoord(RMatrix, _quadr[1]);
		_quadr[2] = multCoord(RMatrix, _quadr[2]);
		_quadr[3] = multCoord(RMatrix, _quadr[3]);
		_quadr[4] = multCoord(RMatrix, _quadr[4]);
		_quadr[5] = multCoord(RMatrix, _quadr[5]);
		_quadr[6] = multCoord(RMatrix, _quadr[6]);
		_quadr[7] = multCoord(RMatrix, _quadr[7]);
	}

	//������������ �����������
	makeScaleMatrix(scales[num].x, scales[num].y, scales[num].z);
	_quadr[0] = multCoord(SMatrix, _quadr[0]);
	_quadr[1] = multCoord(SMatrix, _quadr[1]);
	_quadr[2] = multCoord(SMatrix, _quadr[2]);
	_quadr[3] = multCoord(SMatrix, _quadr[3]);
	_quadr[4] = multCoord(SMatrix, _quadr[4]);
	_quadr[5] = multCoord(SMatrix, _quadr[5]);
	_quadr[6] = multCoord(SMatrix, _quadr[6]);
	_quadr[7] = multCoord(SMatrix, _quadr[7]);

	return _quadr;
}

//������������ ������
void Make_Duplication() {
	ifstream inp1("quadre.txt");
	Vector3f u;
	for (int i = 0; i < 4; i++)
	{
		inp1 >> u.x >> u.y >> u.z;
		figure.push_back(u);
	}
	float h;
	//���������� ����������
	inp1 >> h;
	//������� ��������� �����
	for (int i = 0, j = 4; i < 4; i++,j++)
	{
		u.x = figure[i].x;
		u.y = figure[i].y;
		u.z = figure[i].z + h;
		figure.push_back(u);
	}
	Vector3f d = { 1.0, 1.0, 1.0 };
	scales.push_back(d);
}

//���������� �������� � ������
void Calc_Normals() {
	Vector3f normal;
	normals.clear();
	float a = -1;
	//1 �����
	normal = Calc_Normal_of_Poligon(figure[2], figure[1], figure[0]);
	normals.push_back(normal);
	//2 �����
	normal =  Calc_Normal_of_Poligon(figure[1], figure[2], figure[6]);
	normals.push_back(normal);
	//3 �����
	normal = Calc_Normal_of_Poligon(figure[5], figure[6], figure[7]);
	normals.push_back(normal);
	//4 �����
	normal = Calc_Normal_of_Poligon(figure[3], figure[0], figure[4]);
	normals.push_back(normal);
	//5 �����
	normal = Calc_Normal_of_Poligon(figure[2], figure[3], figure[7]);
	normals.push_back(normal);
	//6 �����
	normal = Calc_Normal_of_Poligon(figure[0], figure[1], figure[5]);
	normals.push_back(normal);
}

//���������� ���������� ��������
void Calc_Smooth_Normals() {
	Vector3f smooth;

	//1 �������
	smooth = (normals[0] + normals[3] + normals[5]);
	smoothedNormals.push_back(smooth);
	//2 �������
	smooth = (normals[0] + normals[1] + normals[5]);
	smoothedNormals.push_back(smooth);
	//3 �������
	smooth = (normals[0] + normals[1] + normals[4]);
	smoothedNormals.push_back(smooth);
	//4 �������
	smooth = (normals[0] + normals[3] + normals[4]);
	smoothedNormals.push_back(smooth);
	//5 �������
	smooth = (normals[2] + normals[3] + normals[5]);
	smoothedNormals.push_back(smooth);
	//6 ������
	smooth = (normals[2] + normals[1] + normals[5]);
	smoothedNormals.push_back(smooth);
	//7 �������
	smooth = (normals[2] + normals[4] + normals[1]);
	smoothedNormals.push_back(smooth);
	//8 �������
	smooth = (normals[2] + normals[3] + normals[4]);
	smoothedNormals.push_back(smooth);
}

void Load_Texture()//�������� ��������
{
	//��������� ��� ��������
	//unsigned int  sea_tex, sky_tex, space_tex;
	int w1;
	int h1;
	int comp1;
	glGenTextures(10, names_tex);
	unsigned char* image1 = stbi_load("sea.bmp", &w1, &h1, &comp1, STBI_rgb);
	glBindTexture(GL_TEXTURE_2D, names_tex[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w1, h1, GL_RGB, GL_UNSIGNED_BYTE, image1);
}