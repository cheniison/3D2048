#pragma once
#include"Point3F.h"

//无起点的向量
class Vector
{
public:
	Vector();
	Vector(double, double, double);
	Vector(const Point3F &);
	virtual ~Vector();
	void SetVector(double, double, double); 
	void SetVector(const Point3F &lhs,const Point3F &rhs);//rhs指向lhs
	Vector& operator+=(const Vector&);
	Vector operator+(const Vector&)const;
	Vector& operator-=(const Vector&);
	Vector operator-(const Vector&)const;
	operator Point3F() const;//将向量强制转换成点
	double model(const Vector&);//求模
	Vector cal_unit_vector();//求单位向量
	friend double InnerProduct(const Vector&, const Vector&);//内积
	friend Vector OuterProduct(const Vector&, const Vector&);//外积
	friend Vector operator*(double, const Vector&);//数乘
	friend Vector operator*(const Vector&, double);//数乘重载
protected:
	Point3F direct;//向量的大小和方向
};

