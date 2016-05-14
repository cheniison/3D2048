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

bool Point3F::operator==(const Point3F & rhs) const
{
	if (fabs(x - rhs.x) < 1e-6&&fabs(y - rhs.y) < 1e-6&&fabs(z - rhs.z) < 1e-6)
	{
		return true;
	}
	return false;
}

bool Point3F::operator!=(const Point3F & rhs) const
{
	return !(*this == rhs);
}

double GetDistance(const Point3F &lhs, const Point3F &rhs)
{
	Point3F tmp = rhs - lhs;

	return sqrt(tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
}
