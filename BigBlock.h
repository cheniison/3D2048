#pragma once
#include"Point3F.h"
#include"Block.h"
#include<vector>

class BigBlock
{
public:
	BigBlock() = default;
	~BigBlock();
	void SetSize(int);
private:
	Point3F location;
	std::vector<std::vector<std::vector<Block>>> bigblock;

};

