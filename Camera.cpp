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

	//пересчитаем координаты по каким-то диким формулам
	//новая координата X для вращаемой точки
	new_view.x = (cosA + (1 - cosA)*x*x)	* direction.x;
	new_view.x += ((1 - cosA)*x*y - z * sinA) * direction.y;
	new_view.x += ((1 - cosA)*x*z + y * sinA) * direction.z;

	//новая координата Y для вращаемой точки
	new_view.y = ((1 - cosA)*x*y + z * sinA) * direction.x;
	new_view.y += (cosA + (1 - cosA)*y*y)	* direction.y;
	new_view.y += ((1 - cosA)*y*z - x * sinA) * direction.z;

	//новая координата Z для вращаемой точки
	new_view.z = ((1 - cosA)*x*z - y * sinA) * direction.x;
	new_view.z += ((1 - cosA)*y*z + x * sinA) * direction.y;
	new_view.z += (cosA + (1 - cosA)*z*z)	* direction.z;

	View.x = Position.x + new_view.x;
	View.y = Position.y + new_view.y;
	View.z = Position.z + new_view.z;
}

void Camera::Set(GLint width, GLint height)
{
	POINT mousePos;		//позиция мыши

	//вычислить координаты центра окна
	int middleX = width / 2.0f;
	int middleY = height / 2.0f;

	float angleY = 0.0f;	//Направление взгляда вверх/вниз
	float angleZ = 0.0f;	//Значение, необходимое для вращения влево-вправо (по оси Y)
	static float currentRotX = 0.0f;

	//получить текущие координаты мыши
	GetCursorPos(&mousePos);

	//если положение мыши не изменилось
	//камеру вращать не нужно
	if (mousePos.x == middleX && mousePos.y == middleY) return;

	//вернуть координаты курсора в центр окна
	SetCursorPos(middleX, middleY);

	//определить, куда был сдвинут курсор
	angleY = (float)((middleX - mousePos.x)) / 1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;

	static float lastRotX = 0.0f;
	lastRotX = currentRotX;	//Сохраняем последний угол вращения 
							//и используем заново currentRotX

	//если поворот больше одного градуса, умешьшим его
	//чтобы уменьшить скорость вращения
	if (currentRotX > 1.0f)
	{
		currentRotX = 1.0f;
		if (lastRotX != 1.0f)
		{
			//Чтобы найти ось, вокруг которой нужно совершать вращение вверх и вниз, нужно 
			//найти вектор, перпендикулярный вектору взгляда камеры и 
			//вертикальному вектору
			Vector3f vAxis = Calc_Normal(View - Position, UpVector);

			//нормализуем ось
			vAxis = Normalize(vAxis);

			//вращаем камеру вокруг нашей оси на заданный угол
			Rotate_Around_Axis(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}

	//Если угол меньше -1.0f
	else if (currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
		if (lastRotX != -1.0f)
		{
			//вычисляем ось
			Vector3f vAxis = Calc_Normal(View - Position, UpVector);

			//нормализуем ось
			vAxis = Normalize(vAxis);

			//вращаем
			Rotate_Around_Axis (-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}

	//если в пределах 1.0f -1.0f - просто вращаем
	else
	{
		Vector3f vAxis = Calc_Normal(View - Position, UpVector);
		vAxis = Normalize(vAxis);
		Rotate_Around_Axis(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	//всегда вращаем камеру вокруг Y-оси
	Rotate_Around_Axis(angleY, 0, 1, 0);
}

void Camera::Rotate_Around_Viewer(Vector3f _Center, float angle, float x, float y, float z)
{
	Vector3f _NewPosition;

	//получим центр, вокруг которого нужно вращатся
	Vector3f vPos = Position - _Center;

	//вычислим синус и косинус угла
	float cosA = (float)cos(angle);
	float sinA = (float)sin(angle);

	//Найдем значение X точки вращения
	_NewPosition.x = (cosA + (1 - cosA)*x*x)	* vPos.x;
	_NewPosition.x += ((1 - cosA)*x*y - z * sinA)	* vPos.y;
	_NewPosition.x += ((1 - cosA)*x*z + y * sinA)	* vPos.z;

	//значение Y
	_NewPosition.y = ((1 - cosA)*x*y + z * sinA)	* vPos.x;
	_NewPosition.y += (cosA + (1 - cosA)*y*y)	* vPos.y;
	_NewPosition.y += ((1 - cosA)*y*z - x * sinA)	* vPos.z;

	//значение Z
	_NewPosition.z = ((1 - cosA)*x*z - y * sinA)	* vPos.x;
	_NewPosition.z += ((1 - cosA)*y*z + x * sinA)	* vPos.y;
	_NewPosition.z += (cosA + (1 - cosA)*z*z)	* vPos.z;

	//установить новую позицию камеры
	Position = _Center + _NewPosition;
}
