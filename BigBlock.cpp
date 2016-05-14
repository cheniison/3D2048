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

	int number = 2;//����ӵ���������չΪ�����
	srand(time(0));
	int tmp = rand() % left + 1;//���һ����tmp���ҳ���tmp�������ֵ�С���飬����ֵ����Ϊnumber
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				if (bigblock[i][j][k].number() == 0)
				{
					--tmp;//ÿ�ҵ�һ�������ֵ�С���飬�ͼ�һ��tmp
					if (tmp == 0)//��tmp��0ʱ����ȡ��С���飬��������
					{
						bigblock[i][j][k].SetNumber(number);
						--left;//ʣ���������1
						return true;
					}
				}
			}
		}
	}
	
}
