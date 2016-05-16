// GlutDemo.cpp : 定义控制台应用程序的入口点。  
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
//圆周率宏  
#define GL_PI 3.14159f
//获取屏幕的宽度  
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//设置程序的窗口大小  
GLint windowWidth = 400;
GLint windowHeight = 300;
//绕x轴旋转角度  
GLfloat xRotAngle = 0.0f;
//绕y轴旋转角度  
GLfloat yRotAngle = 0.0f;
//受支持的点大小范围  
GLfloat sizes[2];
//受支持的点大小增量  
GLfloat step;
//观察点
GLfloat standPoint[] = { 0.0f,0.0f,20.0f };


GLboolean bWire = GL_TRUE;


BigBlock bblock;
//菜单回调函数  
void processMenu(int value) {

	//重新绘制  
	glutPostRedisplay();
}
//显示回调函数  
void renderScreen(void) {
	//将窗口颜色清理为黑色  
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	//将模板缓冲区值全部清理为1  
	glClearStencil(1);
	//使能模板缓冲区  
	glEnable(GL_STENCIL_TEST);
	//把整个窗口清理为当前清理颜色：黑色。清除深度缓冲区、模板缓冲区  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//将当前Matrix状态入栈  
	glPushMatrix();
	

	glEnable(GL_BLEND);     //启用混合状态 
							// 启动混合并设置混合因子
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//进行平滑处理　  
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);


	//全局光照
	{
		GLfloat lmodel_ambient[] = { 0.2f,0.2f,0.2f,1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	}
	
	//光源
	{
		glPushMatrix();
	
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 7.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat spot_direction[] = { 0.0,0.0,-1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //指定第0号光源的位置   
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);//聚光灯方向
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
		glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.0);

		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient); //GL_AMBIENT表示各种光线照射到该材质上，
														 //经过很多次反射后最终遗留在环境中的光线强度（颜色）  
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //漫反射后~~  
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//镜面反射后~~~  

		glEnable(GL_LIGHT0); //使用第0号光照  
		glEnable(GL_LIGHTING); //在后面的渲染中使用光照  
		glEnable(GL_DEPTH_TEST); //这句是启用深度测试，这样，在后面的物体会被挡着，例如房子后面有棵树，如果不启用深度测试，  
							 //你先画了房子再画树，树会覆盖房子的；但启用深度测试后无论你怎么画，树一定在房子后面（被房子挡着）

		glPopMatrix();
	}
	
	
	//坐标系绕x轴旋转xRotAngle  
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	//坐标系绕y轴旋转yRotAngle  
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	//白色绘制坐标系  
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

	//设置绘画颜色为金色  
	glColor3f(0.0f, 1.0f, 0.0f);

	bblock.draw();
	
	//恢复压入栈的Matrix  
	glPopMatrix();
	//交换两个缓冲区的指针  
	glutSwapBuffers();
}
//设置Redering State   
void setupRederingState(void) {
	//设置清理颜色为黑色  
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//设置绘画颜色为绿色  
	glColor3f(1.0f, 1.0f, 0.0f);
	//使能深度测试  
	glEnable(GL_DEPTH_TEST);
	//获取受支持的点大小范围  
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	//获取受支持的点大小增量  
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	printf("point size range:%f-%f\n", sizes[0], sizes[1]);
	printf("point step:%f\n", step);
}
//窗口大小变化回调函数  
void changSize(GLint w, GLint h) {
	//设置坐标系为x(-100.0f,100.0f)、y(-100.0f,100.0f)、z(-100.0f,100.0f)  
	GLfloat coordinatesize = 10.0f;
	//横宽比率  
	GLfloat ratio;
	//窗口宽高为零直接返回  
	if ((w == 0) || (h == 0))
		return;
	//设置视口和窗口大小一致  
	glViewport(0, 0, w, h);
	//对投影矩阵应用随后的矩阵操作  
	glMatrixMode(GL_PROJECTION);
	//重置当前指定的矩阵为单位矩阵　  
	glLoadIdentity();
	ratio = (GLfloat)w / (GLfloat)h;
	////正交投影  
	//if (w<h)
	//	glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
	//else
	//	glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
	gluPerspective(45, ratio , 1.0f, 100.0f);
	gluLookAt(standPoint[0], standPoint[1], standPoint[2], 0.0, 0.0 , 0.0, 0.0f, 1.0f, 0.0f);
	//对模型视图矩阵堆栈应用随后的矩阵操作  
	glMatrixMode(GL_MODELVIEW);
	//重置当前指定的矩阵为单位矩阵　  
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
	//重新绘制  
	glutPostRedisplay();
}
void rotatex(double vec[],double angle)
{
	//x轴旋转
	vec[1] = vec[1] * cos(GL_PI*angle / 180.0) - vec[0] * sin(GL_PI*angle / 180.0);
	vec[2] = vec[1] * sin(GL_PI*angle / 180.0) + vec[2] * cos(GL_PI*angle / 180.0);
}
void rotatey(double vec[],double angle)
{
	//y轴旋转
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
	//重新绘制  
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
				//找出xyz最大的
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
//按键输入处理回调函数  
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
	
	//重新绘制  
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	
	//初始化游戏数据
	bblock.SetSize(4);
	bblock.AddNumber();

	//初始化glut   
	glutInit(&argc, argv);
	//使用双缓冲区、深度缓冲区、模板缓冲区  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//获取系统的宽像素  
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	//获取系统的高像素  
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	//创建窗口，窗口名字为OpenGL Glut Demo  
	glutCreateWindow("2048");
	//设置窗口大小  
	glutReshapeWindow(windowWidth, windowHeight);
	//窗口居中显示  
	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	//窗口大小变化时的处理函数  
	glutReshapeFunc(changSize);
	//设置显示回调函数   
	glutDisplayFunc(renderScreen);
	//设置按键输入处理回调函数  
	glutSpecialFunc(specialKey);
	//键盘输入
	glutKeyboardFunc(keyboard);
	//处理鼠标
	glutMouseFunc(mouse);
	//滑轮
	glutMouseWheelFunc(wheel);
	//设置全局渲染参数  
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
//	// 防止被0所除
//	if (0 == h) 
//	{
//		h = 1;
//	}
//	// 设置视口为窗口的大小
//	glViewport(0, 0, w, h);
//	// 选择投影矩阵，并重置坐标系统
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	// 计算窗口的纵横比（像素比）
//	aspectRatio = (GLfloat)w / (GLfloat)h;
//	// 定义裁剪区域（根据窗口的纵横比，并使用正投影）
//	if (w <= h) 
//	{// 宽 < 高
//		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100 / aspectRatio, 1.0, -1.0);
//	}
//	else
//	{// 宽 > 高
//		glOrtho(-100.0 * aspectRatio, 100.0 *aspectRatio, -100.0, 100.0, 1.0, -1.0);
//	}
//	// 选择模型视图矩阵，并重置坐标系统
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
//	glutCreateWindow("OpenGL程序");
//	init();
//	glutDisplayFunc(&display);
//	glutReshapeFunc(&reshape);
//	glutMouseFunc(&mouse);
//	glutSpecialFunc(&inputKey);
//	glutMainLoop();
//	return 0;
//}