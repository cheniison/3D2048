// GlutDemo.cpp : �������̨Ӧ�ó������ڵ㡣  
//  


#include<stdio.h>
#include <GL/freeglut.h>
#include <math.h> 
#include"BigBlock.h"
#include"Block.h"
#include"Point3F.h"
#include"Vector.h"
#include<vector>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
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
//�۲��
GLfloat standPoint[] = { 0.0f,0.0f,20.0f };


GLboolean bWire = GL_TRUE;


BigBlock bblock;
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
	

	glEnable(GL_BLEND);     //���û��״̬ 
							// ������ϲ����û������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//����ƽ������  
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);


	//ȫ�ֹ���
	{
		GLfloat lmodel_ambient[] = { 0.2f,0.2f,0.2f,1.0f };
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

	bblock.draw();
	
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
	//��������ϵΪx(-100.0f,100.0f)��y(-100.0f,100.0f)��z(-100.0f,100.0f)  
	GLfloat coordinatesize = 10.0f;
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
	////����ͶӰ  
	//if (w<h)
	//	glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
	//else
	//	glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
	gluPerspective(45, ratio , 1.0f, 100.0f);
	gluLookAt(standPoint[0], standPoint[1], standPoint[2], 0.0, 0.0 , 0.0, 0.0f, 1.0f, 0.0f);
	//��ģ����ͼ�����ջӦ�����ľ������  
	glMatrixMode(GL_MODELVIEW);
	//���õ�ǰָ���ľ���Ϊ��λ����  
	glLoadIdentity();
}
void wheel(int button, int dir, int x, int y)
{
	if (dir<=0)
	{
		if (standPoint[2] >= 6 && standPoint[2] <30)
		{
			++standPoint[2];
		}
		
	}
	if (dir>0)
	{
		if (standPoint[2] > 6 && standPoint[2] <= 30)
		{
			--standPoint[2];
		}
		
	}
	changSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//���»���  
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
	std::vector<int> temp;
	switch (key)
	{
	case 'w':
		temp.clear();
		temp.push_back(0);
		temp.push_back(0);
		temp.push_back(0);
		temp[0] = 1;
		bblock.move(temp);
		bblock.AddNumber();
		break;
	case 's':
		temp.clear();
		temp.push_back(0);
		temp.push_back(0);
		temp.push_back(0);
		temp[0] = -1;
		bblock.move(temp);
		bblock.AddNumber();
		break;
	case 'a':
		temp.clear();
		temp.push_back(0);
		temp.push_back(0);
		temp.push_back(0);
		temp[1] = 1;
		bblock.move(temp);
		bblock.AddNumber();
		break;
	case 'd':
		temp.clear();
		temp.push_back(0);
		temp.push_back(0);
		temp.push_back(0);
		temp[1] = -1;
		bblock.move(temp);
		bblock.AddNumber();
		break;
	case 'q':
		temp.clear();
		temp.push_back(0);
		temp.push_back(0);
		temp.push_back(0);
		temp[2] = 1;
		bblock.move(temp);
		bblock.AddNumber();
		break;
	case 'e':
		temp.clear();
		temp.push_back(0);
		temp.push_back(0);
		temp.push_back(0);
		temp[2] = -1;
		bblock.move(temp);
		bblock.AddNumber();
		break;
	}
	//���»���  
	glutPostRedisplay();
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
	
	//��ʼ����Ϸ����
	bblock.SetSize(4);
	bblock.AddNumber();

	//��ʼ��glut   
	glutInit(&argc, argv);
	//ʹ��˫����������Ȼ�������ģ�建����  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//��ȡϵͳ�Ŀ�����  
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	//��ȡϵͳ�ĸ�����  
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	//�������ڣ���������ΪOpenGL Glut Demo  
	glutCreateWindow("2048");
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