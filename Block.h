#pragma once
#include"Point3F.h"
#include"Vector.h"

//С����
class Block
{
public:
	Block() = default;
	~Block();
	int number();
	void SetNumber(int n);
	bool move(const Point3F &);//�����յ�,�Ѿ����յ��򷵻�false
private:
	Point3F location;//����λ��
	double size;//һ��С������ı߳�
	int num;
};

