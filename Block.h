#pragma once
#include"Point3F.h"
#include"Vector.h"
#include<GL\freeglut.h>
//С����
class Block
{
public:
	Block();
	~Block();
	int & number();
	void SetNumber(int n);
	void SetLocation(double x,double y,double z);
	bool move(const Point3F &);//�����յ�,�Ѿ����յ��򷵻�false
	void draw();
	int GetNum() { return num; }
private:
	Point3F location;//����λ��
	double size;//һ��С������ı߳�
	int num;
};

