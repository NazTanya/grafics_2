#include "Camera.h"

Camera::Camera(){
}

void Camera::Camera_Position(float posX, float posY, float posZ,
	float viewX, float viewY, float viewZ,
	float upX, float upY, float upZ) {

	Vector3f pos = Vector3f(posX, posY, posZ);
	Vector3f view = Vector3f(viewX, viewY, viewZ);
	Vector3f up = Vector3f(upX, upY, upZ);
	
	Position = pos;
	View = view;
	UpVector = up;
}

void Camera::Move_Camera_Up_Down(float speed) {
	Vector3f direction = View - Position;

	Position.x += direction.x * speed;

	View.x += direction.x * speed;
}

void Camera::Move_Camera_Right_Left(float speed) {
	Vector3f direction = View - Position;

	Position.z += direction.z * speed;

	View.z += direction.z * speed;
}

void Camera::Move_Camera(float speed) {
	Vector3f direction = View - Position;

	Position.y += direction.y * speed;

	View.y += direction.y * speed;
}

void Camera:: Rotate_Around_Axis(float angle, float x, float y, float z) {
	float cosA = cos(angle);
	float sinA = sin(angle);
	Vector3f direction = View - Position;
	Vector3f new_view;

	//����������� ���������� �� �����-�� ����� ��������
	//����� ���������� X ��� ��������� �����
	new_view.x = (cosA + (1 - cosA)*x*x)	* direction.x;
	new_view.x += ((1 - cosA)*x*y - z * sinA) * direction.y;
	new_view.x += ((1 - cosA)*x*z + y * sinA) * direction.z;

	//����� ���������� Y ��� ��������� �����
	new_view.y = ((1 - cosA)*x*y + z * sinA) * direction.x;
	new_view.y += (cosA + (1 - cosA)*y*y)	* direction.y;
	new_view.y += ((1 - cosA)*y*z - x * sinA) * direction.z;

	//����� ���������� Z ��� ��������� �����
	new_view.z = ((1 - cosA)*x*z - y * sinA) * direction.x;
	new_view.z += ((1 - cosA)*y*z + x * sinA) * direction.y;
	new_view.z += (cosA + (1 - cosA)*z*z)	* direction.z;

	View.x = Position.x + new_view.x;
	View.y = Position.y + new_view.y;
	View.z = Position.z + new_view.z;
}

void Camera::Set(GLint width, GLint height)
{
	POINT mousePos;		//������� ����

	//��������� ���������� ������ ����
	int middleX = width / 2.0f;
	int middleY = height / 2.0f;

	float angleY = 0.0f;	//����������� ������� �����/����
	float angleZ = 0.0f;	//��������, ����������� ��� �������� �����-������ (�� ��� Y)
	static float currentRotX = 0.0f;

	//�������� ������� ���������� ����
	GetCursorPos(&mousePos);

	//���� ��������� ���� �� ����������
	//������ ������� �� �����
	if (mousePos.x == middleX && mousePos.y == middleY) return;

	//������� ���������� ������� � ����� ����
	SetCursorPos(middleX, middleY);

	//����������, ���� ��� ������� ������
	angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

	static float lastRotX = 0.0f;
	lastRotX = currentRotX;	//��������� ��������� ���� �������� 
							//� ���������� ������ currentRotX

	//���� ������� ������ ������ �������, �������� ���
	//����� ��������� �������� ��������
	if (currentRotX > 1.0f)
	{
		currentRotX = 1.0f;
		if (lastRotX != 1.0f)
		{
			//����� ����� ���, ������ ������� ����� ��������� �������� ����� � ����, ����� 
			//����� ������, ���������������� ������� ������� ������ � 
			//������������� �������
			Vector3f vAxis = Calc_Normal(View - Position, UpVector);

			//����������� ���
			vAxis = Normalize(vAxis);

			//������� ������ ������ ����� ��� �� �������� ����
			Rotate_Around_Axis(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}

	//���� ���� ������ -1.0f
	else if (currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
		if (lastRotX != -1.0f)
		{
			//��������� ���
			Vector3f vAxis = Calc_Normal(View - Position, UpVector);

			//����������� ���
			vAxis = Normalize(vAxis);

			//�������
			Rotate_Around_Axis (-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}

	//���� � �������� 1.0f -1.0f - ������ �������
	else
	{
		Vector3f vAxis = Calc_Normal(View - Position, UpVector);
		vAxis = Normalize(vAxis);
		Rotate_Around_Axis(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	//������ ������� ������ ������ Y-���
	Rotate_Around_Axis(angleY, 0, 1, 0);
}

void Camera::Rotate_Around_Viewer(Vector3f _Center, float angle, float x, float y, float z)
{
	Vector3f _NewPosition;

	//������� �����, ������ �������� ����� ��������
	Vector3f vPos = Position - _Center;

	//�������� ����� � ������� ����
	float cosA = (float)cos(angle);
	float sinA = (float)sin(angle);

	//������ �������� X ����� ��������
	_NewPosition.x = (cosA + (1 - cosA)*x*x)	* vPos.x;
	_NewPosition.x += ((1 - cosA)*x*y - z * sinA)	* vPos.y;
	_NewPosition.x += ((1 - cosA)*x*z + y * sinA)	* vPos.z;

	//�������� Y
	_NewPosition.y = ((1 - cosA)*x*y + z * sinA)	* vPos.x;
	_NewPosition.y += (cosA + (1 - cosA)*y*y)	* vPos.y;
	_NewPosition.y += ((1 - cosA)*y*z - x * sinA)	* vPos.z;

	//�������� Z
	_NewPosition.z = ((1 - cosA)*x*z - y * sinA)	* vPos.x;
	_NewPosition.z += ((1 - cosA)*y*z + x * sinA)	* vPos.y;
	_NewPosition.z += (cosA + (1 - cosA)*z*z)	* vPos.z;

	//���������� ����� ������� ������
	Position = _Center + _NewPosition;
}
