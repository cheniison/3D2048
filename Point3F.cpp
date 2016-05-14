#include "Point3F.h"
#include<cmath>



Point3F::Point3F(double sx, double sy, double sz):
	x(sx),y(sy),z(sz){}

Point3F::~Point3F()
{
}

void Point3F::SetPoint(double sx, double sy, double sz)
{
	x = sx;
	y = sy;
	z = sz;
}

Point3F & Point3F::operator+=(const Point3F & rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Point3F Point3F::operator+(const Point3F & rhs) const
{
	Point3F tmp(*this);
	tmp += rhs;
	return tmp;
}

Point3F & Point3F::operator-=(const Point3F & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Point3F Point3F::operator-(const Point3F & rhs) const
{
	Point3F tmp(*this);
	tmp -= rhs;
	return tmp;
}

double GetDistance(const Point3F &lhs, const Point3F &rhs)
{
	Point3F tmp = rhs - lhs;

	return sqrt(tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
}
