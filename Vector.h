#pragma once
#include"Point3F.h"

//无起点的向量
class Vector
{
public:
	Vector();
	Vector(double, double, double);
	virtual ~Vector();
	void SetVector(double, double, double); 
	void SetVector(const Point3F &lhs,const Point3F &rhs);//rhs指向lhs
	Vector& operator+=(const Vector&);
	Vector operator+(const Vector&)const;
	Vector& operator-=(const Vector&);
	Vector operator-(const Vector&)const;
	double model(const Vector&);//求模
	friend double InnerProduct(const Vector&, const Vector&);//内积
	friend Vector OuterProduct(const Vector&, const Vector&);//外积
	
protected:
	Point3F direct;//向量的大小和方向
};

