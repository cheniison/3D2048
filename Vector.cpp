#include "Vector.h"



Vector::Vector()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector::Vector(double, double, double)
{
}


Vector::~Vector()
{
}

void Vector::SetVector(double, double, double)
{
}

void Vector::SetVector(const Point3F & lhs, const Point3F & rhs)
{
}

Vector & Vector::operator+=(const Vector &)
{
	// TODO: �ڴ˴����� return ���
}

Vector Vector::operator+(const Vector &) const
{
	return Vector();
}

Vector & Vector::operator-=(const Vector &)
{
	// TODO: �ڴ˴����� return ���
}

Vector Vector::operator-(const Vector &) const
{
	return Vector();
}

double InnerProduct(const Vector &, const Vector &)
{
	return 0.0;
}

Vector OuterProduct(const Vector &, const Vector &)
{
	return Vector();
}

double Vector::model(const Vector &)
{
	return 0.0;
}
