#ifndef MYREALNO_H
#define MYREALNO_H

#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;
class MyRealNo
{
public:
	MyRealNo(void);
	~MyRealNo(void);
	MyRealNo(double real);
	MyRealNo(const MyRealNo& myReal);

public:

	double getM()const
	{
		return mantissa;
	}
	long getE()const
	{
		return expnt;
	}
	void setM(double d)
	{
		mantissa=d;
	}
	void setE(long e)
	{
		expnt=e;
	}
	double getDouble()const;

public:
	MyRealNo& add(MyRealNo& b);
	MyRealNo& multiply(const MyRealNo& b);
	MyRealNo& devide(double d);
	void copy(MyRealNo& r);

private:
    void normalize();//
    void transform(long offset);//

public:
	MyRealNo& operator=(const MyRealNo& myReal);

private:
    double mantissa; //
	long expnt;

};

#endif
