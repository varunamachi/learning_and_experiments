#include "SimpleContext.h"

#include <iostream>


int SimpleContext::minorVersion() 
{
	return 0;
}

int SimpleContext::majorVersion()
{
	return 1;
}


void SimpleContext::error( char *message ) 
{
	std::cerr << "ERROR: "<< message << std::endl;
}


SimpleContext::~SimpleContext(void)
{
}
