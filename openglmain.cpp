// GlutDemo.cpp : �������̨Ӧ�ó������ڵ㡣  
//  


#include<stdio.h>
#include <GL/freeglut.h>
#include <math.h> 
#include"BigBlock.h"
#include"Block.h"
#include"Point3F.h"
#include"Vector.h"
//Բ���ʺ�  
#define GL_PI 3.14159f
//��ȡ��Ļ�Ŀ��  
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//���ó���Ĵ��ڴ�С  
GLint windowWidth = 400;
GLint windowHeight = 300;
//��x����ת�Ƕ�  
GLfloat xRotAngle = 0.0f;
//��y����ת�Ƕ�  
GLfloat yRotAngle = 0.0f;
//��֧�ֵĵ��С��Χ  
GLfloat sizes[2];
//��֧�ֵĵ��С����  
GLfloat step;
//��������ϵΪx(-100.0f,100.0f)��y(-100.0f,100.0f)��z(-100.0f,100.0f)  
GLfloat coordinatesize = 10.0f;


GLboolean bWire = GL_TRUE;
//�˵��ص�����  
void processMenu(int value) {

	//���»���  
	glutPostRedisplay();
}
//��ʾ�ص�����  
void renderScreen(void) {
	//��������ɫ����Ϊ��ɫ  
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	//��ģ�建����ֵȫ������Ϊ1  
	glClearStencil(1);
	//ʹ��ģ�建����  
	glEnable(GL_STENCIL_TEST);
	//��������������Ϊ��ǰ������ɫ����ɫ�������Ȼ�������ģ�建����  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//����ǰMatrix״̬��ջ  
	glPushMatrix();
	
	//����ƽ������  
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);


	//ȫ�ֹ���
	{
		GLfloat lmodel_ambient[] = { 0.2,0.2,0.2,1.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	}
	
	//��Դ
	{
		glPushMatrix();
	
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 7.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat spot_direction[] = { 0.0,0.0,-1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //ָ����0�Ź�Դ��λ��   
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);//�۹�Ʒ���
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
		glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient); //GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ�
														 //�����ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��  
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //�������~~  
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//���淴���~~~  

		glEnable(GL_LIGHT0); //ʹ�õ�0�Ź���  
		glEnable(GL_LIGHTING); //�ں������Ⱦ��ʹ�ù���  
		glEnable(GL_DEPTH_TEST); //�����������Ȳ��ԣ��������ں��������ᱻ���ţ����緿�Ӻ����п����������������Ȳ��ԣ�  
							 //���Ȼ��˷����ٻ��������Ḳ�Ƿ��ӵģ���������Ȳ��Ժ���������ô������һ���ڷ��Ӻ��棨�����ӵ��ţ�

		glPopMatrix();
	}
	
	
	//����ϵ��x����תxRotAngle  
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	//����ϵ��y����תyRotAngle  
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	//��ɫ��������ϵ  
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(-9.0f, 0.0f, 0.0f);
	glVertex3f(9.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -9.0f, 0.0f);
	glVertex3f(0.0f, 9.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -9.0f);
	glVertex3f(0.0f, 0.0f, 9.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(9.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 9.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();

	//���û滭��ɫΪ��ɫ  
	glColor3f(0.0f, 1.0f, 0.0f);

	for (int i = -3; i <= 3;i+=2)
	{
		for (int j = -3; j <= 3; j+=2)
		{
			for (int k = -3; k <= 3; k+=2)
			{
				glPushMatrix();
				//glColor3f(0.0, 1.0, 0.0);
				glTranslatef(i, j, k);
				GLfloat earth_mat_ambient[] = { (i + 3) / 6.0, (j + 3) / 6.0, (k + 3) / 6.0, 1.0f };
				GLfloat earth_mat_diffuse[] = { (i + 3) / 6.0, (j + 3) / 6.0, (k + 3) / 6.0, 1.0f };
				GLfloat earth_mat_specular[] = { 0.4f, 0.4f, 0.4f, 1.0f };
				GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				GLfloat earth_mat_shininess = 10.0f;

				glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
				glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
				glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
				//glColor3f((i+3)/6.0, (j+ 3) / 6.0, (j + 3) / 6.0);
				glutSolidCube(1.0f);
				
				//glColor3f(0.0, 0.0, 0.0);
				////Ҫ��ʾ���ַ�  
				//char str[10];
				//sprintf_s(str, "%d", i + j + k);
				//int n = strlen(str);
				////����Ҫ����Ļ����ʾ�ַ�����ʼλ��  
				//glRasterPos3f(0.0, 0.0, 0.0);
				////�����ʾ�ַ����е�ÿ���ַ�

				//for (int i = 0; i < n; i++)
				//	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *(str + i));

				glPopMatrix();
			}
		}

	}
	
	//�ָ�ѹ��ջ��Matrix  
	glPopMatrix();
	//����������������ָ��  
	glutSwapBuffers();
}
//����Redering State   
void setupRederingState(void) {
	//����������ɫΪ��ɫ  
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//���û滭��ɫΪ��ɫ  
	glColor3f(1.0f, 1.0f, 0.0f);
	//ʹ����Ȳ���  
	glEnable(GL_DEPTH_TEST);
	//��ȡ��֧�ֵĵ��С��Χ  
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	//��ȡ��֧�ֵĵ��С����  
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	printf("point size range:%f-%f\n", sizes[0], sizes[1]);
	printf("point step:%f\n", step);
}
//���ڴ�С�仯�ص�����  
void changSize(GLint w, GLint h) {
	//������  
	GLfloat ratio;
	//���ڿ��Ϊ��ֱ�ӷ���  
	if ((w == 0) || (h == 0))
		return;
	//�����ӿںʹ��ڴ�Сһ��  
	glViewport(0, 0, w, h);
	//��ͶӰ����Ӧ�����ľ������  
	glMatrixMode(GL_PROJECTION);
	//���õ�ǰָ���ľ���Ϊ��λ����  
	glLoadIdentity();
	ratio = (GLfloat)w / (GLfloat)h;
	//����ͶӰ  
	if (w<h)
		glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
	else
		glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
	//��ģ����ͼ�����ջӦ�����ľ������  
	glMatrixMode(GL_MODELVIEW);
	//���õ�ǰָ���ľ���Ϊ��λ����  
	glLoadIdentity();
}
void wheel(int button, int dir, int x, int y)
{
	if (dir<=0)
	{
		if (coordinatesize >= 6 && coordinatesize <30)
		{
			++coordinatesize;
		}
		
	}
	if (dir>0)
	{
		if (coordinatesize > 6 && coordinatesize <= 30)
		{
			--coordinatesize;
		}
		
	}
	changSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutPostRedisplay();
}
void rotatex(double vec[],double angle)
{
	//x����ת
	vec[1] = vec[1] * cos(GL_PI*angle / 180.0) - vec[0] * sin(GL_PI*angle / 180.0);
	vec[2] = vec[1] * sin(GL_PI*angle / 180.0) + vec[2] * cos(GL_PI*angle / 180.0);
}
void rotatey(double vec[],double angle)
{
	//y����ת
	vec[0] = vec[0] * cos(GL_PI*angle / 180.0) + vec[1] * sin(GL_PI*angle / 180.0);
	vec[2] = -vec[0] * sin(GL_PI*angle / 180.0) + vec[2] * cos(GL_PI*angle / 180.0);
}
void keyboard(unsigned char key, int x, int y)
{
	
}

void mouse(int button, int state, int x, int y)
{
	static int ox=0, oy=0;
	static int flag = 0;
	double vec[3];
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			if (flag==1)
			{
				ox = x;
				oy = y;
			}
			flag = 0;
			//glutIdleFunc();
		}
		if (state==GLUT_UP)
		{
			if (flag == 0)
			{
				vec[0] = x -ox;
				vec[1] = oy - y;
				vec[2] = 10;
				rotatex(vec,-xRotAngle);
				rotatey(vec,-yRotAngle);
				//�ҳ�xyz����
				if (fabs(vec[0]) >= fabs(vec[1]) && fabs(vec[0]) >= fabs(vec[2]))
				{
					printf("x:%lf\n", vec[0]);
				}
				else if (fabs(vec[1]) >= fabs(vec[0]) && fabs(vec[1]) >= fabs(vec[2]))
				{
					printf("y:%lf\n", vec[1]);
				}
				else
				{
					printf("z:%lf\n", vec[2]);
				}
			}
			flag = 1;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}
//�������봦��ص�����  
void specialKey(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		xRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_DOWN) {
		xRotAngle += 5.0f;
	}
	else if (key == GLUT_KEY_LEFT) {
		yRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_RIGHT) {
		yRotAngle += 5.0f;
	}
	//���»���  
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	int nModelMenu;
	int nWireMenu;
	int nMainMenu;
	//��ʼ��glut   
	glutInit(&argc, argv);
	//ʹ��˫����������Ȼ�������ģ�建����  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//��ȡϵͳ�Ŀ�����  
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	//��ȡϵͳ�ĸ�����  
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	//�������ڣ���������ΪOpenGL Glut Demo  
	glutCreateWindow("OpenGL Glut Demo");
	//���ô��ڴ�С  
	glutReshapeWindow(windowWidth, windowHeight);
	//���ھ�����ʾ  
	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	//���ڴ�С�仯ʱ�Ĵ�����  
	glutReshapeFunc(changSize);
	//������ʾ�ص�����   
	glutDisplayFunc(renderScreen);
	//���ð������봦��ص�����  
	glutSpecialFunc(specialKey);
	//��������
	glutKeyboardFunc(keyboard);
	//�������
	glutMouseFunc(mouse);
	//����
	glutMouseWheelFunc(wheel);
	//����ȫ����Ⱦ����  
	setupRederingState();
	glutMainLoop();
	return 0;
}



//#include <GL\freeglut.h>
//#include<cmath>
//
//
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//
//static GLfloat spin = 0.0;
//static GLfloat col = 0.0;
//
//static float angle = 0.0, ratio;
//static float x = 0.0f, y = 1.75f, z = 5.0f;
//static float lx = 0.0f, ly = 0.0f, lz = -1.0f;
//
//void init()
//{
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glShadeModel(GL_SMOOTH);
//}
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glColor3f(0.5f, 0.25f, 0.0f);
//	
//
//	glPushMatrix();
//
//	//glRotated(angle, 0.0f, 0.0f, 1.0f);
//	glTranslatef(0.0f, 0.0f, 1.0f);
//	glutWireTeapot(8.0f);
//	
//	glPopMatrix();
//	//glutSwapBuffers();
//	glFlush();
//}
//
//
//
//void reshape(GLsizei w, GLsizei h)
//{
//	GLfloat aspectRatio;
//	// ��ֹ��0����
//	if (0 == h) 
//	{
//		h = 1;
//	}
//	// �����ӿ�Ϊ���ڵĴ�С
//	glViewport(0, 0, w, h);
//	// ѡ��ͶӰ���󣬲���������ϵͳ
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	// ���㴰�ڵ��ݺ�ȣ����رȣ�
//	aspectRatio = (GLfloat)w / (GLfloat)h;
//	// ����ü����򣨸��ݴ��ڵ��ݺ�ȣ���ʹ����ͶӰ��
//	if (w <= h) 
//	{// �� < ��
//		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100 / aspectRatio, 1.0, -1.0);
//	}
//	else
//	{// �� > ��
//		glOrtho(-100.0 * aspectRatio, 100.0 *aspectRatio, -100.0, 100.0, 1.0, -1.0);
//	}
//	// ѡ��ģ����ͼ���󣬲���������ϵͳ
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslatef(0.0f, 0.0f, 3.0f);
//}
//
//void mouse(int button, int state, int x, int y)
//{
//	switch (button)
//	{
//	case GLUT_LEFT_BUTTON:
//		if (state == GLUT_DOWN)
//		{
//			//glutIdleFunc();
//		}
//		break;
//	case GLUT_RIGHT_BUTTON:
//		break;
//	case GLUT_MIDDLE_BUTTON:
//		if (state == GLUT_DOWN)
//			glutIdleFunc(NULL);
//		break;
//	default:
//		break;
//	}
//}
//void orientMe(float ang) 
//{
//	lx = sin(ang);
//	lz = -cos(ang);
//	glLoadIdentity();
//	gluLookAt(x, y, z,x + lx, y + ly, z + lz,0.0f, 1.0f, 0.0f);
//}
//void moveMeFlat(int direction) 
//{
//	x = x + direction*(lx)*0.1;
//	z = z + direction*(lz)*0.1;
//	glLoadIdentity();
//	gluLookAt(x, y, z,x + lx, y + ly, z + lz,0.0f, 1.0f, 0.0f);
//}
//void inputKey(int key, int x, int y) 
//{
//	switch (key)
//	{
//	case GLUT_KEY_LEFT:
//		angle -= 0.1f;
//		orientMe(angle); break;
//	case GLUT_KEY_RIGHT:
//		angle += 0.1f;
//		orientMe(angle); break;
//	case GLUT_KEY_UP:
//		moveMeFlat(1); break;
//	case GLUT_KEY_DOWN:
//		moveMeFlat(-1); break;
//	}
//	glutPostRedisplay();
//}
//
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
//	glutInitWindowPosition(500, 250);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("OpenGL����");
//	init();
//	glutDisplayFunc(&display);
//	glutReshapeFunc(&reshape);
//	glutMouseFunc(&mouse);
//	glutSpecialFunc(&inputKey);
//	glutMainLoop();
//	return 0;
//}