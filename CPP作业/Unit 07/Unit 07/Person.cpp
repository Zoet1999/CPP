#include "stdafx.h"
#include "Person.h"
#include <cstring>

Person::Person(char* n )
{
	strcpy(name ,n);
}
Person::Person()
{}

Person::~Person()
{
}

char* Person::getname()
{
	return name;
}
