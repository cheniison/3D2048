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
	//设置位置
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				bigblock[i][j][k].SetLocation((i-1.5)*2,(j-1.5)*2,(k-1.5)*2);
			}
		}
	}
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
	
	return true;
}

bool BigBlock::move(const std::vector<int> &direct)
{
	std::vector<std::vector<std::vector<Point3F>>> dest;//小方块的终点

	//for (int i = 0; i < size; ++i)
	//{
	//	for (int j = 0; j < size; ++j)
	//	{
	//		for (int k = 0; k < size; ++k)
	//		{
	//			if (bigblock[i][j][k].number() != 0)
	//			{
	//				dest[i][j][k] = cal_dest(bigblock[i][j][k],i,j,k,direct);//算出每个小正方体的终点
	//			}
	//		}
	//	}
	//} 
	if (direct[0]!=0)
	{
		if (direct[0]>0)
		{
			
			//面遍历
			for (int j = 0; j < size;++j)
			{
				for (int k = 0; k < size;++k)
				{
					//柱状投影
					int flag = 1;
					int temp;
					int p = size - 1;
					for (int i = size - 1; i >= 0; --i)
					{
						if (bigblock[i][j][k].number()!=0)
						{
							//合并
							if ((p != size-1)&&(bigblock[i][j][k].number()==bigblock[p+1][j][k].number())&&(flag==1))
							{
								bigblock[p + 1][j][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=i)
							{
								//交换
								bigblock[p][j][k].number() = bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
							}
							--p;
						}
					}//i
				}//k
			}//j
		}
		else
		{
			//面遍历
			for (int j = 0; j < size; ++j)
			{
				for (int k = 0; k < size; ++k)
				{
					//柱状投影
					int flag = 1;
					int temp;
					int p = 0;
					for (int i = 0; i <size; ++i)
					{
						
						if (bigblock[i][j][k].number() != 0 )
						{
							//合并
							if (p != 0 && bigblock[i][j][k].number() == bigblock[p - 1][j][k].number()&& flag == 1)
							{
								bigblock[p - 1][j][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=i)
							{
								//交换
								bigblock[p][j][k].number() = bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
							}
							++p;
						}
					}//i
				}//k
			}//j}
		}
	}
	else if (direct[1]!=0)
	{
		if (direct[1]>0)
		{
			//面遍历
			for (int i = 0; i < size; ++i)
			{
				for (int k = 0; k < size; ++k)
				{
					//柱状投影
					int flag = 1;
					int temp;
					int p = size - 1;
					for (int j = size - 1; j >= 0; --j)
					{
						
						if (bigblock[i][j][k].number() != 0)
						{
							//合并
							if (p != size-1 && bigblock[i][j][k].number() == bigblock[i][p+1][k].number()&& flag == 1)
							{
								bigblock[i][p + 1][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								
								flag = 0;
							}
							else if(p!=j)
							{
								//交换
								bigblock[i][p][k].number() = bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
							}
							--p;
						}
					}//i
				}//k
			}//j
		}
		else
		{
			//面遍历
			for (int i = 0; i < size; ++i)
			{
				for (int k = 0; k < size; ++k)
				{
					//柱状投影
					int flag = 1;
					int temp;
					int p = 0;
					for (int j = 0; j <size; ++j)
					{
						
						if (bigblock[i][j][k].number() != 0)
						{
							//合并
							if (p != 0 && bigblock[i][j][k].number() == bigblock[i][p - 1][k].number()&&flag == 1)
							{
								bigblock[i][p - 1][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=j)
							{
								//交换
								bigblock[i][p][k].number() = bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
							}
							++p;
						}
					}//i
				}//k
			}//j}

		}
	}
	else if (direct[2]!=0)
	{
		if (direct[2]>0)
		{
			//面遍历
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					//柱状投影
					int flag = 1;
					int temp;
					int p = size - 1;
					for (int k = size - 1; k >= 0; --k)
					{
						
						if (bigblock[i][j][k].number() != 0 )
						{
							//合并
							if (p != size-1 && bigblock[i][j][k].number() == bigblock[i][j][p + 1].number()&& flag == 1)
							{
								bigblock[i][j][p + 1].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if (p != k)
							{
								//交换
								bigblock[i][j][p].number() = bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;;
							}
							--p;
						}
					}//i
				}//k
			}//j
		}
		else
		{
			//面遍历
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					//柱状投影
					int flag = 1;
					int temp;
					int p = 0;
					for (int k = 0; k <size; ++k)
					{
						
						if (bigblock[i][j][k].number() != 0 )
						{
							//合并
							if (p != 0 && bigblock[i][j][k].number() == bigblock[i][j][p - 1].number()&& flag == 1)
							{
								bigblock[i][j][p - 1].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=k)
							{
								//交换
								/*temp = bigblock[i][j][k].number();
								bigblock[i][j][k].number() = bigblock[p][j][k].number();
								bigblock[p][j][k].number() = temp;*/
								bigblock[i][j][p].number() = bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
							}
							++p;
						}
					}//i
				}//k
			}//j}
		}
	}

	int flag;
	int count = 0;
	/*
	
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
	*/
	

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

Point3F BigBlock::cal_dest(const Block &sblock,int i,int j,int k,const std::vector<int> &direct)
{
	
	return Point3F();
}

void BigBlock::update()
{

}

void BigBlock::draw()
{
	for (int i = 0; i < size;++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				bigblock[i][j][k].draw();
			}
		}
	}
}
