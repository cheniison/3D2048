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

bool BigBlock::move()
{
	std::vector<std::vector<std::vector<Point3F>>> dest;//С������յ�

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				if (bigblock[i][j][k].number() != 0)
				{
					dest[i][j][k] = cal_dest(bigblock[i][j][k]);//���ÿ��С��������յ�
				}
			}
		}
	} 
	int flag;
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
						flag += bigblock[i][j][k].move(dest[i][j][k]);//ֻҪ��һ��С����䶯����flag��=0
					}
				}
			}
		}
	} while (flag);//ֱ������С���鶼����������ѭ��
	
}

Point3F BigBlock::cal_dest(const Block &)
{
	return Point3F();
}
