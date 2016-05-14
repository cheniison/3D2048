#include "BigBlock.h"



BigBlock::BigBlock()
{
}


BigBlock::~BigBlock()
{
}

void BigBlock::SetSize(int s)
{
	bigblock.resize(s);
	for (int i = 0; i < s;++i)
	{
		bigblock[i].resize(s);
		for (int j = 0; j < s;++j)
		{
			bigblock[i][j].resize(s);
		}
	}
}
