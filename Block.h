#pragma once
#include"Point3F.h"
#include"Vector.h"

//小方块
class Block
{
public:
	Block() = default;
	~Block();
	int number();
	void SetNumber(int n);
	bool move(const Point3F &);//移向终点,已经到终点则返回false
private:
	Point3F location;//中心位置
	double size;//一个小正方块的边长
	int num;
};

