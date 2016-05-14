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
