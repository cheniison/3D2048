#include "Block.h"




Block::~Block()
{
}

int Block::number()
{
	return num;
}

void Block::SetNumber(int n)
{
	num = n;
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
