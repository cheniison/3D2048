#pragma once
#include"Point3F.h"
class Block
{
public:
	Block() = default;
	~Block();
private:
	Point3F location;
	double number;
};

