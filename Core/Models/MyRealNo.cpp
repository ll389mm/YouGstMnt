#include "MyRealNo.h"
#include <math.h>
#include <stdlib.h>
using namespace std;
MyRealNo::MyRealNo(void)
{
	mantissa=0;
	expnt=0;
}

MyRealNo::~MyRealNo(void)
{
}

MyRealNo::MyRealNo(double real)
{
	int exp=0;
	double m;
	double absVal=abs(real);
	if(absVal>=10)
	{
		while(absVal>=10)
		{
			absVal/=10;
			++exp;
		}
		if (real>=0)
			m=absVal;
		else
			m=-absVal;
	}
	else if(absVal<1 && absVal>0)
	{
		while(absVal<1)
		{
			absVal*=10;
			--exp;
		}
		if (real>=0)
			m=absVal;
		else
			m=-absVal;
	}
	else
	{
		m=real;
		exp=0;
	}
	mantissa=m;
	expnt=exp;
}
MyRealNo::MyRealNo(const MyRealNo& myReal)
{
	mantissa=myReal.getM();
	expnt=myReal.getE();
}

double MyRealNo::getDouble()const
{
	return mantissa * pow(double(10),expnt);
}

MyRealNo& MyRealNo::add(MyRealNo& b)
{


	long expDif=expnt-b.getE();
    if (expDif>0)
	{
		b.transform(expDif);
		mantissa+=b.getM();
	}
	else if(expDif<0)
	{
		this->transform(-expDif);
		mantissa+=b.getM();
	}
	else
		mantissa+=b.getM();
	this->normalize();


	return *this;

}

MyRealNo& MyRealNo::multiply(const MyRealNo& b)
{

	if (mantissa==0.0 || b.getM()==0.0)
	{
		mantissa=0.0;
		expnt=0;
	}
	else
	{
		mantissa*=b.getM();
		expnt+=b.getE();
		this->normalize();
	}

		return *this;
}
MyRealNo& MyRealNo::devide(double d)
{
	mantissa/=d;
	this->normalize();
	return *this;
}

void MyRealNo::copy(MyRealNo& r)
{
	mantissa=r.getM();
	expnt=r.getE();
	this->normalize();
}
void MyRealNo::normalize()
{

	double absVal=abs(mantissa);
	if (absVal>=10)
	{
		while(absVal>=10.0)
		{
			absVal/=10;
			++expnt;
		}
	}
	else if (absVal<1.0 && absVal>0.0)
	{
		while (absVal<1)
		{
			absVal*=10;
			--expnt;
		}
		
	}
	else if(absVal==0.0)
		expnt=0;
	else;

	if (mantissa>0)
		mantissa=absVal;
	else
		mantissa=-absVal;

}

void MyRealNo::transform(long offset)
{

	mantissa/=pow(double(10),offset);
	expnt+=offset;

}

MyRealNo& MyRealNo::operator=(const MyRealNo& myReal)
{

	mantissa=myReal.mantissa;
	expnt=myReal.expnt;
	return *this;

}

