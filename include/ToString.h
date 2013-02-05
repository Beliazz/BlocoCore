#ifndef ToString_h__
#define ToString_h__

#include "BlocoCore.h"

using namespace std;

inline string ToString(float value)
{
	stringstream stm;
	stm << value;
	return stm.str();
}
inline string ToString(double value)
{
	stringstream stm;
	stm << value;
	return stm.str();
}
inline string ToString(int value)
{
	stringstream stm;
	stm << value;
	return stm.str();
}
inline string ToString(unsigned int value)
{
	stringstream stm;
	stm << value;
	return stm.str();
}
inline string ToString(long value)
{
	stringstream stm;
	stm << value;
	return stm.str();
}
inline string ToString(unsigned long value)
{
	stringstream stm;
	stm << value;
	return stm.str();
}
inline string ToString(Vec value)
{
	string output = "";
	output += ToString(value.GetX()) + " ";
	output += ToString(value.GetY()) + " ";
	output += ToString(value.GetZ());

	return output;
}

#endif