#pragma once
#include"Point3F.h"

//С����
class Block
{
public:
	Block() = default;
	~Block();
	int number();
	void SetNumber(int n);
private:
	Point3F location;//����λ��
	int num;
};

