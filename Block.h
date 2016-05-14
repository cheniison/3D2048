#pragma once
#include"Point3F.h"

//小方块
class Block
{
public:
	Block() = default;
	~Block();
	int number();
	void SetNumber(int n);
private:
	Point3F location;//中心位置
	int num;
};

