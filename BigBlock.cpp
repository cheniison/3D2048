#include "BigBlock.h"
#include<cstdlib>
#include<ctime>



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
	size = s;
	left = s*s*s;
}

bool BigBlock::IsFull()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				if (bigblock[i][j][k].number()==0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool BigBlock::IsEmpty()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				if (bigblock[i][j][k].number() != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool BigBlock::AddNumber()
{
	if (IsFull())
	{
		return false;
	}

	int number = 2;//需添加的数，可拓展为随机数
	srand(time(0));
	int tmp = rand() % left + 1;//随机一个数tmp，找出第tmp个无数字的小方块，将其值设置为number
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				if (bigblock[i][j][k].number() == 0)
				{
					--tmp;//每找到一个无数字的小方块，就减一次tmp
					if (tmp == 0)//当tmp到0时，即取此小方块，设置数字
					{
						bigblock[i][j][k].SetNumber(number);
						--left;//剩余的数量减1
						return true;
					}
				}
			}
		}
	}
	
}

bool BigBlock::move()
{
	std::vector<std::vector<std::vector<Point3F>>> dest;//小方块的终点

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				if (bigblock[i][j][k].number() != 0)
				{
					dest[i][j][k] = cal_dest(bigblock[i][j][k]);//算出每个小正方体的终点
				}
			}
		}
	} 
	int flag;
	int count = 0;
	do
	{
		flag = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				for (int k = 0; k < size; ++k)
				{
					if (bigblock[i][j][k].number() != 0)
					{
						flag += bigblock[i][j][k].move(dest[i][j][k]);//只要有一个小方块变动，则flag！=0
					}
				}
			}
		}
		count++;//计算循环次数
	} while (flag);//直到所有小方块都不动，结束循环

	if (count == 1)
	{
		return false;//没有小方块变动
	}
	else
	{
		update();
		return true;//有小方块变动
	}
}

Point3F BigBlock::cal_dest(const Block &)
{
	return Point3F();
}

void BigBlock::update()
{

}
