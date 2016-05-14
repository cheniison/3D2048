#pragma once
#include "Vector.h"
#include"Point3F.h"
//����������
class VectorWithStartPoint :
	public Vector
{
public:
	VectorWithStartPoint() = default;
	VectorWithStartPoint(double, double, double, double);
	VectorWithStartPoint(const Vector&,const Point3F&);
	virtual ~VectorWithStartPoint();
private:
	Point3F StartPoint;//���������
};

