#pragma once
#include"Point3F.h"

//����������
class Vector
{
public:
	Vector();
	Vector(double, double, double);
	Vector(const Point3F &);
	virtual ~Vector();
	void SetVector(double, double, double); 
	void SetVector(const Point3F &lhs,const Point3F &rhs);//rhsָ��lhs
	Vector& operator+=(const Vector&);
	Vector operator+(const Vector&)const;
	Vector& operator-=(const Vector&);
	Vector operator-(const Vector&)const;
	operator Point3F() const;//������ǿ��ת���ɵ�
	double model(const Vector&);//��ģ
	Vector cal_unit_vector();//��λ����
	friend double InnerProduct(const Vector&, const Vector&);//�ڻ�
	friend Vector OuterProduct(const Vector&, const Vector&);//���
	friend Vector operator*(double, const Vector&);//����
	friend Vector operator*(const Vector&, double);//��������
	Vector rotatef(double x,double y,double z);//������ת
protected:
	Point3F direct;//�����Ĵ�С�ͷ���
};

