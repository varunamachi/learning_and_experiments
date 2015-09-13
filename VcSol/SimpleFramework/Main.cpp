#include <iostream>
#include "PluginManager.h"

void main()
{	
	PluginManager pman("..\\Release");
	std::cout << pman << std::endl;
	pman.unloadAll();
	getchar();
}