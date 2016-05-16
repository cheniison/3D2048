#include "Block.h"

Block::Block():size(1.0f),num(0){}


Block::~Block()
{
}

int & Block::number()
{
	return num;
}

void Block::SetNumber(int n)
{
	num = n;
}

void Block::SetLocation(double x, double y, double z)
{
	location.SetPoint(x,y,z);
}

bool Block::move(const Point3F &dest)
{
	Vector u_vector = Vector(dest - location).cal_unit_vector();

	const double v=1.0;//�ٶ�
	if (location != dest)//���޸�==���غ���
	{
		location += v * u_vector;
		return true;
	}
	return false;
}

void Block::draw()
{
	glPushMatrix();
	//glColor3f(0.0, 1.0, 0.0);
	glTranslatef(location.x, location.y, location.z);
	GLfloat earth_mat_ambient[] = { 1, 1 , 1 , 1.0f };
	GLfloat earth_mat_diffuse[] = { 1 ,1 , 1 , 1.0f };
	GLfloat earth_mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat earth_mat_shininess = 50.0f;
	//͸��
	if (num == 0)
	{
		//����Ȼ�������Ϊֻ��
		glDepthMask(GL_FALSE);
		earth_mat_ambient[3] = earth_mat_diffuse[3] = 0.1f;
	}
	switch (num)
	{
	case 2:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 255/255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 0 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 0 / 255.0f;
		break;
	case 4:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 255 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 102 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 0 / 255.0f;
		break;
	case 8:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 255 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 255 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 0 / 255.0f;
		break;
	case 16:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 51 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 255 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 0 / 255.0f;
		break;
	case 32:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 102 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 255 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 51 / 255.0f;
		break;
	case 64:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 153 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 255 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 255 / 255.0f;
		break;
	case 128:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 0 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 102 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 153 / 255.0f;
		break;
	case 256:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 0 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 0 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 255 / 255.0f;
		break;
	case 512:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 102 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 0 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 51 / 255.0f;
		break;
	case 1024:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 51 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 0 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 51 / 255.0f;
		break;
	case 2048:
		earth_mat_ambient[0] = earth_mat_diffuse[0] = 0 / 255.0f;
		earth_mat_ambient[1] = earth_mat_diffuse[1] = 0 / 255.0f;
		earth_mat_ambient[2] = earth_mat_diffuse[2] = 0 / 255.0f;
		break;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
	//glColor3f((i+3)/6.0, (j+ 3) / 6.0, (j + 3) / 6.0);
	if (num==0)
	{
		glutWireCube(size);
	}
	else
	{
		glutSolidCube(size);
	}
	
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
	// ��ɰ�͸������Ļ��ƣ�����Ȼ������ָ�Ϊ�ɶ���д����ʽ
	glDepthMask(GL_TRUE);
	glPopMatrix();
}
