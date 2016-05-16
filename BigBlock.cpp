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
	//����λ��
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
	
	return true;
}

bool BigBlock::move(const std::vector<int> &direct)
{
	std::vector<std::vector<std::vector<Point3F>>> dest;//С������յ�

	//for (int i = 0; i < size; ++i)
	//{
	//	for (int j = 0; j < size; ++j)
	//	{
	//		for (int k = 0; k < size; ++k)
	//		{
	//			if (bigblock[i][j][k].number() != 0)
	//			{
	//				dest[i][j][k] = cal_dest(bigblock[i][j][k],i,j,k,direct);//���ÿ��С��������յ�
	//			}
	//		}
	//	}
	//} 
	if (direct[0]!=0)
	{
		if (direct[0]>0)
		{
			
			//�����
			for (int j = 0; j < size;++j)
			{
				for (int k = 0; k < size;++k)
				{
					//��״ͶӰ
					int flag = 1;
					int temp;
					int p = size - 1;
					for (int i = size - 1; i >= 0; --i)
					{
						if (bigblock[i][j][k].number()!=0)
						{
							//�ϲ�
							if ((p != size-1)&&(bigblock[i][j][k].number()==bigblock[p+1][j][k].number())&&(flag==1))
							{
								bigblock[p + 1][j][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=i)
							{
								//����
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
			//�����
			for (int j = 0; j < size; ++j)
			{
				for (int k = 0; k < size; ++k)
				{
					//��״ͶӰ
					int flag = 1;
					int temp;
					int p = 0;
					for (int i = 0; i <size; ++i)
					{
						
						if (bigblock[i][j][k].number() != 0 )
						{
							//�ϲ�
							if (p != 0 && bigblock[i][j][k].number() == bigblock[p - 1][j][k].number()&& flag == 1)
							{
								bigblock[p - 1][j][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=i)
							{
								//����
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
			//�����
			for (int i = 0; i < size; ++i)
			{
				for (int k = 0; k < size; ++k)
				{
					//��״ͶӰ
					int flag = 1;
					int temp;
					int p = size - 1;
					for (int j = size - 1; j >= 0; --j)
					{
						
						if (bigblock[i][j][k].number() != 0)
						{
							//�ϲ�
							if (p != size-1 && bigblock[i][j][k].number() == bigblock[i][p+1][k].number()&& flag == 1)
							{
								bigblock[i][p + 1][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								
								flag = 0;
							}
							else if(p!=j)
							{
								//����
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
			//�����
			for (int i = 0; i < size; ++i)
			{
				for (int k = 0; k < size; ++k)
				{
					//��״ͶӰ
					int flag = 1;
					int temp;
					int p = 0;
					for (int j = 0; j <size; ++j)
					{
						
						if (bigblock[i][j][k].number() != 0)
						{
							//�ϲ�
							if (p != 0 && bigblock[i][j][k].number() == bigblock[i][p - 1][k].number()&&flag == 1)
							{
								bigblock[i][p - 1][k].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=j)
							{
								//����
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
			//�����
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					//��״ͶӰ
					int flag = 1;
					int temp;
					int p = size - 1;
					for (int k = size - 1; k >= 0; --k)
					{
						
						if (bigblock[i][j][k].number() != 0 )
						{
							//�ϲ�
							if (p != size-1 && bigblock[i][j][k].number() == bigblock[i][j][p + 1].number()&& flag == 1)
							{
								bigblock[i][j][p + 1].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if (p != k)
							{
								//����
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
			//�����
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					//��״ͶӰ
					int flag = 1;
					int temp;
					int p = 0;
					for (int k = 0; k <size; ++k)
					{
						
						if (bigblock[i][j][k].number() != 0 )
						{
							//�ϲ�
							if (p != 0 && bigblock[i][j][k].number() == bigblock[i][j][p - 1].number()&& flag == 1)
							{
								bigblock[i][j][p - 1].number() += bigblock[i][j][k].number();
								bigblock[i][j][k].number() = 0;
								++left;
								flag = 0;
							}
							else if(p!=k)
							{
								//����
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
						flag += bigblock[i][j][k].move(dest[i][j][k]);//ֻҪ��һ��С����䶯����flag��=0
					}
				}
			}
		}
		count++;//����ѭ������
	} while (flag);//ֱ������С���鶼����������ѭ��
	*/
	

	if (count == 1)
	{
		return false;//û��С����䶯
	}
	else
	{
		update();
		return true;//��С����䶯
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
