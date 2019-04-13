#include"Header.h"

void Reshape(GLint w, GLint h) {
	width = w;
	height = h;

	if (height == 0)
		height = 1;
	float aspect = (float)(width / height);

	//установить матрицу проекции/определяет объем сцены
	glMatrixMode(GL_PROJECTION);

	//загрузить единичную матрицу
	glLoadIdentity();

	//определить окно просмотра
	glViewport(0, 0, width, height);

	if (perspective) 
		gluPerspective(angle, aspect, 0.1f, 100.0f);
	else
		if (width >= height)
			glOrtho(-mas * aspect, mas* aspect, -mas, mas, -100.0f, 100.0f);
		else
			glOrtho(-mas, mas, -mas / aspect, mas / aspect, -100.0f, 100.0f);

	//возврат к матрице модели
	glMatrixMode(GL_MODELVIEW);
	
}

void Draw3DSGrid()
{
	glColor3ub(0, 255, 0);
	for (float i = -50; i <= 50; i += 1)
	{
		glBegin(GL_LINES);
		// Ось Х
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);

		// Ось Z
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}
}

void Shine_Light()
{
	//GLfloat world_color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat materail_diffuse[4] = { 0.3, 0.3, 0.3, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materail_diffuse);
	glEnable(GL_COLOR_MATERIAL);
	//направленный источник света
	if (type_of_light == 0) {
		GLfloat world_color0[4] = { 0.5f, 0.1f, 0.8f, 1.0f };
		GLfloat color0[4] = { 0.5f, 0.1f, 0.8f, 1.0f };
		GLfloat position[] = {0.0, 1.0, 0.0, 0.0};
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, color0);
		glLightfv(GL_LIGHT0, GL_EMISSION, world_color0);
	}
	//точечный источник света
	if (type_of_light == 1) {
		GLfloat position[] = { 0.0, 1.0, 0.0, 1.0 };
		GLfloat world_color1[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
		GLfloat color1[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat diffuse[] = {0.2f, 0.3f, 0.2f};
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, color1);
		glLightfv(GL_LIGHT0, GL_EMISSION, world_color1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	}
	//прожектор
	if (type_of_light == 2) {
		GLfloat position[] = { 0.0, 1.0, 0.0, 0.0 };
		GLfloat world_color2[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
		GLfloat diffuse[] = { 0.2f, 0.3f, 0.2f };
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, position);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
		glLightfv(GL_LIGHT2, GL_AMBIENT, world_color2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	}
}

void Draw() {
	//рисуем кирпич

	//не каркасный режим
	if (!skeleton) {

		//нормили не сглажены
		if (!smooth_normal) {

			//отрисовка без текстур
			if (!texture) {

				int nN = 0;
				//грань 0123
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glEnd();
				//грань 0154
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glVertex3f(figure[5].x, figure[5].y, figure[5].z);
					glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glEnd();
				//грань 1265
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glVertex3f(figure[6].x, figure[6].y, figure[6].z);
					glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glEnd();
				//грань 2376
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glVertex3f(figure[3].x, figure[3].y, figure[3].z);
					glVertex3f(figure[7].x, figure[7].y, figure[7].z);
					glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glEnd();
				//грань 3047
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glVertex3f(figure[3].x, figure[3].y, figure[3].z);
					glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glVertex3f(figure[4].x, figure[4].y, figure[4].z);
					glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glEnd();
				//грань 4567
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glVertex3f(figure[4].x, figure[4].y, figure[4].z);
					glVertex3f(figure[5].x, figure[5].y, figure[5].z);
					glVertex3f(figure[6].x, figure[6].y, figure[6].z);
					glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glEnd();


				nN = 0;
				//грань 0123
				glBegin(GL_LINE_LOOP);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(227,66,52);
					glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glEnd();
				//грань 0154
				glBegin(GL_LINE_LOOP);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(227,66,52);
					glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glVertex3f(figure[5].x, figure[5].y, figure[5].z);
					glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glEnd();
				//грань 1265
				glBegin(GL_LINE_LOOP);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(227,66,52);
					glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glVertex3f(figure[6].x, figure[6].y, figure[6].z);
					glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glEnd();
				//грань 2376
				glBegin(GL_LINE_LOOP);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(227,66,52);
					glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glVertex3f(figure[3].x, figure[3].y, figure[3].z);
					glVertex3f(figure[7].x, figure[7].y, figure[7].z);
					glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glEnd();
				//грань 3047
				glBegin(GL_LINE_LOOP);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(227,66,52);
					glVertex3f(figure[3].x, figure[3].y, figure[3].z);
					glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glVertex3f(figure[4].x, figure[4].y, figure[4].z);
					glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glEnd();
				//грань 4567
				glBegin(GL_LINE_LOOP);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(227,66,52);
					glVertex3f(figure[4].x, figure[4].y, figure[4].z);
					glVertex3f(figure[5].x, figure[5].y, figure[5].z);
					glVertex3f(figure[6].x, figure[6].y, figure[6].z);
					glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glEnd();
			}

			//отрисовка с текстурами
			else {
				int nN = 0;
				glEnable(GL_TEXTURE_2D);	//разрешить текстурирование
				glBindTexture(GL_TEXTURE_2D, names_tex[0]);	//выбрать текстуру
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//умножение
				//грань 0123
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glTexCoord2f(1, 1); glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glTexCoord2f(1, 0); glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glTexCoord2f(0, 0); glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glEnd();
				//грань 0154
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glTexCoord2f(1, 1); glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glTexCoord2f(1, 0); glVertex3f(figure[5].x, figure[5].y, figure[5].z);
					glTexCoord2f(0, 0); glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glEnd();
				//грань 1265
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure[1].x, figure[1].y, figure[1].z);
					glTexCoord2f(1, 1); glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glTexCoord2f(1, 0); glVertex3f(figure[6].x, figure[6].y, figure[6].z);
					glTexCoord2f(0, 0); glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glEnd();
				//грань 2376
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure[2].x, figure[2].y, figure[2].z);
					glTexCoord2f(1, 1); glVertex3f(figure[3].x, figure[3].y, figure[3].z);
					glTexCoord2f(1, 0); glVertex3f(figure[7].x, figure[7].y, figure[7].z);
					glTexCoord2f(0, 0); glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glEnd();
				//грань 3047
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure[3].x, figure[3].y, figure[3].z);
					glTexCoord2f(1, 1); glVertex3f(figure[0].x, figure[0].y, figure[0].z);
					glTexCoord2f(1, 0); glVertex3f(figure[4].x, figure[4].y, figure[4].z);
					glTexCoord2f(0, 0); glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glEnd();
				//грань 4567
				glBegin(GL_QUADS);
					glNormal3f(normals[nN].x, normals[nN].y, normals[nN].z); nN++;
					glColor3ub(0, 255, 0);
					glTexCoord2f(0, 1); glVertex3f(figure[4].x, figure[4].y, figure[4].z);
					glTexCoord2f(1, 1); glVertex3f(figure[5].x, figure[5].y, figure[5].z);
					glTexCoord2f(1, 0); glVertex3f(figure[6].x, figure[6].y, figure[6].z);
					glTexCoord2f(0, 0); glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glEnd();
			}
			//отключить текстурирование
			glDisable(GL_TEXTURE_2D);
		}

		//нормали сглажены
		else {

		//отрисовка без текстур
		if (!texture) {
			//грань 0123
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glNormal3f(smoothedNormals[3].x, smoothedNormals[3].y, smoothedNormals[3].z);
				glVertex3f(figure[3].x, figure[3].y, figure[3].z);
			glEnd();
			//грань 0156
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glNormal3f(smoothedNormals[5].x, smoothedNormals[5].y, smoothedNormals[5].z);
				glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glVertex3f(figure[6].x, figure[6].y, figure[6].z);
			glEnd();
			//грань 1265
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glNormal3f(smoothedNormals[5].x, smoothedNormals[5].y, smoothedNormals[5].z);
				glVertex3f(figure[5].x, figure[5].y, figure[5].z);
			glEnd();
			//грань 2376
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glNormal3f(smoothedNormals[3].x, smoothedNormals[3].y, smoothedNormals[3].z);
				glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glNormal3f(smoothedNormals[7].x, smoothedNormals[7].y, smoothedNormals[7].z);
				glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glVertex3f(figure[6].x, figure[6].y, figure[6].z);
			glEnd();
			//грань 3047
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[3].x, smoothedNormals[3].y, smoothedNormals[3].z);
				glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glNormal3f(smoothedNormals[4].x, smoothedNormals[4].y, smoothedNormals[4].z);
				glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glNormal3f(smoothedNormals[7].x, smoothedNormals[7].y, smoothedNormals[7].z);
				glVertex3f(figure[7].x, figure[7].y, figure[7].z);
			glEnd();
			//грань 4567
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[4].x, smoothedNormals[4].y, smoothedNormals[4].z);
				glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glNormal3f(smoothedNormals[5].x, smoothedNormals[5].y, smoothedNormals[5].z);
				glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glNormal3f(smoothedNormals[7].x, smoothedNormals[7].y, smoothedNormals[7].z);
				glVertex3f(figure[7].x, figure[7].y, figure[7].z);
			glEnd();
		}

		//отрисовка с текстурами
		else {
			int nN = 0;
			glEnable(GL_TEXTURE_2D);	//разрешить текстурирование
			glBindTexture(GL_TEXTURE_2D, names_tex[0]);	//выбрать текстуру
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//умножение
			//грань 0123
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glTexCoord2f(0, 0); glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glTexCoord2f(0, 1); glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glTexCoord2f(1, 1); glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glNormal3f(smoothedNormals[3].x, smoothedNormals[3].y, smoothedNormals[3].z);
				glTexCoord2f(1, 0); glVertex3f(figure[3].x, figure[3].y, figure[3].z);
			glEnd();
			//грань 0156
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glTexCoord2f(0, 0); glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glTexCoord2f(0, 1); glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glNormal3f(smoothedNormals[5].x, smoothedNormals[5].y, smoothedNormals[5].z);
				glTexCoord2f(1, 1); glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glTexCoord2f(1, 0); glVertex3f(figure[6].x, figure[6].y, figure[6].z);
			glEnd();
			//грань 1265
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[1].x, smoothedNormals[1].y, smoothedNormals[1].z);
				glTexCoord2f(0, 0); glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glTexCoord2f(0, 1); glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glTexCoord2f(1, 1); glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glNormal3f(smoothedNormals[5].x, smoothedNormals[5].y, smoothedNormals[5].z);
				glTexCoord2f(1, 0); glVertex3f(figure[5].x, figure[5].y, figure[5].z);
			glEnd();
			//грань 2376
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[2].x, smoothedNormals[2].y, smoothedNormals[2].z);
				glTexCoord2f(0, 0); glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glNormal3f(smoothedNormals[3].x, smoothedNormals[3].y, smoothedNormals[3].z);
				glTexCoord2f(0, 1); glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glNormal3f(smoothedNormals[7].x, smoothedNormals[7].y, smoothedNormals[7].z);
				glTexCoord2f(1, 1); glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glTexCoord2f(1, 0); glVertex3f(figure[6].x, figure[6].y, figure[6].z);
			glEnd();
			//грань 3047
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[3].x, smoothedNormals[3].y, smoothedNormals[3].z);
				glTexCoord2f(0, 0); glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glNormal3f(smoothedNormals[0].x, smoothedNormals[0].y, smoothedNormals[0].z);
				glTexCoord2f(0, 1); glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glNormal3f(smoothedNormals[4].x, smoothedNormals[4].y, smoothedNormals[4].z);
				glTexCoord2f(1, 1); glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glNormal3f(smoothedNormals[7].x, smoothedNormals[7].y, smoothedNormals[7].z);
				glTexCoord2f(1, 0); glVertex3f(figure[7].x, figure[7].y, figure[7].z);
			glEnd();
			//грань 4567
			glBegin(GL_QUADS);
				glColor3ub(0, 255, 0);
				glNormal3f(smoothedNormals[4].x, smoothedNormals[4].y, smoothedNormals[4].z);
				glTexCoord2f(0, 0); glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glNormal3f(smoothedNormals[5].x, smoothedNormals[5].y, smoothedNormals[5].z);
				glTexCoord2f(0, 1); glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glNormal3f(smoothedNormals[6].x, smoothedNormals[6].y, smoothedNormals[6].z);
				glTexCoord2f(1, 1); glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glNormal3f(smoothedNormals[7].x, smoothedNormals[7].y, smoothedNormals[7].z);
				glTexCoord2f(1, 0); glVertex3f(figure[7].x, figure[7].y, figure[7].z);
			glEnd();
		}
		//отключить текстурирование
		glDisable(GL_TEXTURE_2D);
		}
	}

	//каркасный режим 
	else {

		int nN = 0;
		//грань 0123
		glBegin(GL_LINE_LOOP);
			glColor3ub(255, 0, 0);
			glVertex3f(figure[0].x, figure[0].y, figure[0].z);
			glVertex3f(figure[1].x, figure[1].y, figure[1].z);
			glVertex3f(figure[2].x, figure[2].y, figure[2].z);
			glVertex3f(figure[3].x, figure[3].y, figure[3].z);
		glEnd();
		//грань 0154
		glBegin(GL_LINE_LOOP);
			glColor3ub(255, 0, 0);
			glVertex3f(figure[0].x, figure[0].y, figure[0].z);
			glVertex3f(figure[1].x, figure[1].y, figure[1].z);
			glVertex3f(figure[5].x, figure[5].y, figure[5].z);
			glVertex3f(figure[4].x, figure[4].y, figure[4].z);
		glEnd();
		//грань 1265
		glBegin(GL_LINE_LOOP);
			glColor3ub(255, 0, 0);
			glVertex3f(figure[1].x, figure[1].y, figure[1].z);
			glVertex3f(figure[2].x, figure[2].y, figure[2].z);
			glVertex3f(figure[6].x, figure[6].y, figure[6].z);
			glVertex3f(figure[5].x, figure[5].y, figure[5].z);
		glEnd();
		//грань 2376
		glBegin(GL_LINE_LOOP);
			glColor3ub(255, 0, 0);
			glVertex3f(figure[2].x, figure[2].y, figure[2].z);
			glVertex3f(figure[3].x, figure[3].y, figure[3].z);
			glVertex3f(figure[7].x, figure[7].y, figure[7].z);
			glVertex3f(figure[6].x, figure[6].y, figure[6].z);
		glEnd();
		//грань 3047
		glBegin(GL_LINE_LOOP);
			glColor3ub(255, 0, 0);
			glVertex3f(figure[3].x, figure[3].y, figure[3].z);
			glVertex3f(figure[0].x, figure[0].y, figure[0].z);
			glVertex3f(figure[4].x, figure[4].y, figure[4].z);
			glVertex3f(figure[7].x, figure[7].y, figure[7].z);
		glEnd();
		//грань 4567
		glBegin(GL_LINE_LOOP);
			glColor3ub(255, 0, 0);
			glVertex3f(figure[4].x, figure[4].y, figure[4].z);
			glVertex3f(figure[5].x, figure[5].y, figure[5].z);
			glVertex3f(figure[6].x, figure[6].y, figure[6].z);
			glVertex3f(figure[7].x, figure[7].y, figure[7].z);
		glEnd();
	}

	//отрисовка нормалей
	if (show_normal) {

		//нормали не сглажены
		if (!smooth_normal) {

			//нормали для 0 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glVertex3f(figure[0].x + normals[0].x, figure[0].y + normals[0].y, figure[0].z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glVertex3f(figure[0].x + normals[3].x, figure[0].y + normals[3].y, figure[0].z + normals[3].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[0].x, figure[0].y, figure[0].z);
				glVertex3f(figure[0].x + normals[5].x, figure[0].y + normals[5].y, figure[0].z + normals[5].z);
			glEnd();

			//нормали для 1 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glVertex3f(figure[1].x + normals[0].x, figure[1].y + normals[0].y, figure[1].z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glVertex3f(figure[1].x + normals[1].x, figure[1].y + normals[1].y, figure[1].z + normals[1].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[1].x, figure[1].y, figure[1].z);
				glVertex3f(figure[1].x + normals[5].x, figure[1].y + normals[5].y, figure[1].z + normals[5].z);
			glEnd();

			//нормали для 2 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glVertex3f(figure[2].x + normals[0].x, figure[2].y + normals[0].y, figure[2].z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glVertex3f(figure[2].x + normals[1].x, figure[2].y + normals[1].y, figure[2].z + normals[1].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[2].x, figure[2].y, figure[2].z);
				glVertex3f(figure[2].x + normals[4].x, figure[2].y + normals[4].y, figure[2].z + normals[4].z);
			glEnd();

			//нормали для 3 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glVertex3f(figure[3].x + normals[0].x, figure[3].y + normals[0].y, figure[3].z + normals[0].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glVertex3f(figure[3].x + normals[3].x, figure[3].y + normals[3].y, figure[3].z + normals[3].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[3].x, figure[3].y, figure[3].z);
				glVertex3f(figure[3].x + normals[4].x, figure[3].y + normals[4].y, figure[3].z + normals[4].z);
			glEnd();

			//нормали для 4 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glVertex3f(figure[4].x + normals[2].x, figure[4].y + normals[2].y, figure[4].z + normals[2].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glVertex3f(figure[4].x + normals[3].x, figure[4].y + normals[3].y, figure[4].z + normals[3].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[4].x, figure[4].y, figure[4].z);
				glVertex3f(figure[4].x + normals[5].x, figure[4].y + normals[5].y, figure[4].z + normals[5].z);
			glEnd();

			//нормали для 5 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glVertex3f(figure[5].x + normals[2].x, figure[5].y + normals[2].y, figure[5].z + normals[2].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glVertex3f(figure[5].x + normals[1].x, figure[5].y + normals[1].y, figure[5].z + normals[1].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[5].x, figure[5].y, figure[5].z);
				glVertex3f(figure[5].x + normals[5].x, figure[5].y + normals[5].y, figure[5].z + normals[5].z);
			glEnd();

			//нормали для 6 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glVertex3f(figure[6].x + normals[2].x, figure[6].y + normals[2].y, figure[6].z + normals[2].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glVertex3f(figure[6].x + normals[1].x, figure[6].y + normals[1].y, figure[6].z + normals[1].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[6].x, figure[6].y, figure[6].z);
				glVertex3f(figure[6].x + normals[4].x, figure[6].y + normals[4].y, figure[6].z + normals[4].z);
			glEnd();

			//нормали для 7 вершины 
			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glVertex3f(figure[7].x + normals[2].x, figure[7].y + normals[2].y, figure[7].z + normals[2].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glVertex3f(figure[7].x + normals[3].x, figure[7].y + normals[3].y, figure[7].z + normals[3].z);
			glEnd();

			glBegin(GL_LINE_STRIP);
				glColor3ub(0, 255, 255);
				glVertex3f(figure[7].x, figure[7].y, figure[7].z);
				glVertex3f(figure[7].x + normals[4].x, figure[7].y + normals[4].y, figure[7].z + normals[4].z);
			glEnd();
		}

		//нормали сглажены
		else {

		//нормаль для 0 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[0].x, figure[0].y, figure[0].z);
			glVertex3f(figure[0].x + smoothedNormals[0].x, figure[0].y + smoothedNormals[0].y, figure[0].z + smoothedNormals[0].z);
		glEnd();

		//нормаль для 1 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[1].x, figure[1].y, figure[1].z);
			glVertex3f(figure[1].x + smoothedNormals[1].x, figure[1].y + smoothedNormals[1].y, figure[1].z + smoothedNormals[1].z);
		glEnd();

		//нормаль для 2 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[2].x, figure[2].y, figure[2].z);
			glVertex3f(figure[2].x + smoothedNormals[2].x, figure[2].y + smoothedNormals[2].y, figure[2].z + smoothedNormals[2].z);
		glEnd();

		//нормаль для 3 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[3].x, figure[3].y, figure[3].z);
			glVertex3f(figure[3].x + smoothedNormals[3].x, figure[3].y + smoothedNormals[3].y, figure[3].z + smoothedNormals[3].z);
		glEnd();

		//нормаль для 4 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[4].x, figure[4].y, figure[4].z);
			glVertex3f(figure[4].x + smoothedNormals[4].x, figure[4].y + smoothedNormals[4].y, figure[4].z + smoothedNormals[4].z);
		glEnd();

		//нормаль для 5 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[5].x, figure[5].y, figure[5].z);
			glVertex3f(figure[5].x + smoothedNormals[5].x, figure[5].y + smoothedNormals[5].y, figure[5].z + smoothedNormals[5].z);
		glEnd();

		//нормаль для 6 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[6].x, figure[6].y, figure[6].z);
			glVertex3f(figure[6].x + smoothedNormals[6].x, figure[6].y + smoothedNormals[6].y, figure[6].z + smoothedNormals[6].z);
		glEnd();

		//нормаль для 7 вершины 
		glBegin(GL_LINE_STRIP);
			glColor3ub(0, 255, 255);
			glVertex3f(figure[7].x, figure[7].y, figure[7].z);
			glVertex3f(figure[7].x + smoothedNormals[7].x, figure[7].y + smoothedNormals[7].y, figure[7].z + smoothedNormals[7].z);
		glEnd();
		}
	}

}

void Display(void)
{

	//очистка буфера цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1);

	//включить буфер глубины
	glEnable(GL_DEPTH_TEST);

	if (Light)
		glEnable(GL_LIGHTING);	//включить свет
	else
		glDisable(GL_LIGHTING); //выключить свет	

	 //обнуление трансформации
	glLoadIdentity();

	//установить вид камеры
	gluLookAt(camera1.Position.x, camera1.Position.y, camera1.Position.z,
		camera1.View.x, camera1.View.y, camera1.View.z,
		camera1.UpVector.x, camera1.UpVector.y, camera1.UpVector.z);

	//устаносить освещение
	Shine_Light();

	//нарисовать сетку
	if (show_grid)
		Draw3DSGrid();

	//нарисовать тиражированную фигуру
	Draw();

	//переместиться в точку взгляда
	glTranslatef(camera1.View.x, 0, camera1.View.z);

	//отключить все источники
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);

	//сменить буфер
	glutSwapBuffers();
}

void Move_figure_x(float speed) {
	for (int i = 0; i < figure.size(); i++)
		figure[i].x += speed;
}

void Move_figure_y(float speed) {
	for (int i = 0; i < figure.size(); i++)
		figure[i].y += speed;
}

void Move_figure_z(float speed) {
	for (int i = 0; i < figure.size(); i++)
		figure[i].z += speed;
}

void Scale(float speed) {

}

void Keyboard_Normal(unsigned char key, int x, int y) {

	//приближение и отдаление ортографической проекции
	if (key == '+') {
		if (mas > 0.1 && !perspective) {
			mas -= 0.05;
			Reshape(width, height);
		}
	}

	if (key == '-' && !perspective) {
		if (mas < 10) {
			mas += 0.05;
			Reshape(width, height);
		}
	}

	//включение/ выключение вращения камеры мышью
	if (key == 'o' || key == 'O') {
		rot = !rot;
		ShowCursor(!rot);
	}

	//переключение между режимами перспективной 
	//и ортографической проекции
	if (key == 'p' || key == 'P') {
		perspective = !perspective;
		Reshape(width, height);
	}

	//включение/выключение каркасного режима
	if (key == 'c' || key == 'C') {
		skeleton = !skeleton;
		if (skeleton)
			Light = false;
		else
			Light = true;
	}

	//включение/выключение отображения нормалей
	if (key == 'n' || key == 'N')
		show_normal = !show_normal;

	//включение/выключение отображения сглаживающих нормалей
	if (key == 'm' || key == 'M')
		smooth_normal = !smooth_normal;

	//включение/выключение отображения сетки
	if (key == 'g' || key == 'G')
		show_grid = !show_grid;

	//включение/выключение света
	if (key == 'l' || key == 'L')
		Light = !Light;

	//включение/выключение текстур
	if (key == 't' || key == 'T')
		texture = !texture;

	//движение камеры
	if (key == 'w' || key == 'W')		camera1.Move_Camera_Up_Down(cam_speed);
	if (key == 's' || key == 'S')		camera1.Move_Camera_Up_Down(-cam_speed);
	if (key == 'a' || key == 'A')		camera1.Rotate_Around_Viewer(camera1.View, cam_speed * 2.0f, 0.0f, 1.0f, 0.0f);
	if (key == 'd' || key == 'D')		camera1.Rotate_Around_Viewer(camera1.View, -cam_speed * 2.0f, 0.0f, 1.0f, 0.0f);

	if (key == 'r')						camera1.Rotate_Around_Axis(0.5, 0, 1, 0);

	//настройка источника света
	if (key == '0')						type_of_light = 0;
	if (key == '1')						type_of_light = 1;
	if (key == '2')						type_of_light = 2;

	//перемещение фигуры
	Vector3f l = { 1,0,0 };
	if (key == '3')						{ figure = transform(0, 30, l); Calc_Normals(); }
	l = { 0,1,0 };
	if (key == '4')						{ figure = transform(0, 30, l); Calc_Normals(); }
	l = { 0, 0, 1 };
	if (key == '5')						{ figure = transform(0, 30, l); Calc_Normals(); }
	
}

void Process_Mouse_Move(int x, int y)
{
	if (rot)
		camera1.Set(width, height);
}

void Keyboard_Special(int key, int x, int y) {
	if (key == GLUT_KEY_UP)			camera1.Move_Camera_Up_Down(cam_speed);
	if (key == GLUT_KEY_DOWN)		camera1.Move_Camera_Up_Down(-cam_speed);
	if (key == GLUT_KEY_LEFT)		camera1.Move_Camera_Right_Left(-cam_speed);
	if (key == GLUT_KEY_RIGHT)		camera1.Move_Camera_Right_Left(cam_speed);
	glutPostRedisplay();
}

void Initialization() {
	//установка освещения
	Shine_Light();
	//установка начального полложения каамеры
	camera1.Camera_Position(-18.0f, 0.2f, -3.0f, 
		-12.0f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f);	
	//расчет координат транжирования
	Make_Duplication();
	//расчет нормалей
	Calc_Normals();
	//расчет сглаженных нормалей
	Calc_Smooth_Normals();
	//загрузка текстур
	Load_Texture();
}

int main(int argc, char *argv[])
{
	width = 500;
	height = 500;
	glutInit(&argc, argv);

	//включить буфер глубины/двойную буферизацию
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Computer_grafics_2 ");
	//начальные установки
	Initialization();								

	//обработка клавиш с кодами ascii
	glutKeyboardFunc(Keyboard_Normal);	
	//обработка не-ascii клавиш
	glutSpecialFunc(Keyboard_Special);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutIdleFunc(Display);
	glutPassiveMotionFunc(Process_Mouse_Move);

	glutMainLoop();
}