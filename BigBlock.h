#pragma once
#include"Point3F.h"
#include"Block.h"
#include"Vector.h"
#include<vector>

//��������
class BigBlock
{
public:
	BigBlock() = default;
	~BigBlock();
	void SetSize(int);
	bool IsFull();//�ж����������Ƿ�����
	bool IsEmpty();//�жϷ����Ƿ�Ϊ��
	bool AddNumber();//����������������,����������������Ϸ����
	bool move(const Vector&);//�����С�����ƶ����򷵻���
	Point3F cal_dest(const Block &,const Vector&);//��֪�䷽��,����С�����յ� 
	void update();//����bigblock��left
private:
	Point3F location;//����λ��
	std::vector<std::vector<std::vector<Block>>> bigblock;
	Vector direction;//��ת����
	int size;//����ı߳�
	int left;//ʣ�¿�С���������
};

