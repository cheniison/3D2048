#pragma once
class Point3F
{
	
public:
	Point3F() = default;
	Point3F(double sx, double sy, double sz);
	~Point3F();	
	// ��������
	void SetPoint(double sx, double sy, double sz);
	Point3F & operator+=(const Point3F & rhs);
	Point3F operator+(const Point3F & rhs) const;
	Point3F & operator-=(const Point3F & rhs);
	Point3F operator-(const Point3F & rhs) const;
	friend double GetDistance(const Point3F &, const Point3F &);
private:
	double x;
	double y;
	double z;
};

