#pragma once
#include"Point3F.h"

//����������
class Vector
{
public:
	Vector();
	Vector(double, double, double);
	virtual ~Vector();
	void SetVector(double, double, double); 
	void SetVector(const Point3F &lhs,const Point3F &rhs);//rhsָ��lhs
	Vector& operator+=(const Vector&);
	Vector operator+(const Vector&)const;
	Vector& operator-=(const Vector&);
	Vector operator-(const Vector&)const;
	double model(const Vector&);//��ģ
	friend double InnerProduct(const Vector&, const Vector&);//�ڻ�
	friend Vector OuterProduct(const Vector&, const Vector&);//���
	
protected:
	Point3F direct;//�����Ĵ�С�ͷ���
};

