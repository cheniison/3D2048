#pragma once
#include"Point3F.h"
#include"Block.h"
#include"Vector.h"
#include<vector>

//整个方块
class BigBlock
{
public:
	BigBlock() = default;
	~BigBlock();
	void SetSize(int);
	bool IsFull();//判断整个方块是否已满
	bool IsEmpty();//判断方块是否为空
	bool AddNumber();//随机给方块添加数字,若方块已满，则游戏结束
	bool move();//如果有小方块移动，则返回真
	Point3F cal_dest(const Block &);//计算小方块终点 
	void update();//更新bigblock和left
private:
	Point3F location;//中心位置
	std::vector<std::vector<std::vector<Block>>> bigblock;
	Vector direction;//旋转方向
	int size;//方块的边长
	int left;//剩下空小立方体个数
};

