#include "PluginDef.h"
#include "IPlatformContext.h"
#include <iostream>


const char *PluginDef::id()
{	
	return "AFB156EB-7D54-4F14-BC11-4A5658E7BDBC";
}

const char *PluginDef::name() 
{
	return "Test1";
}

int PluginDef::majorVersion()
{
	return 1;
}

int PluginDef::minorVersion()
{
	return 0;
}

bool PluginDef::init( IPlatformContext *context )
{
	std::cout << "Initiating plugin: Test plugin" << std::endl
			<< "Platform version: " 
			<< context->majorVersion() << "." << context->minorVersion() 
			<< std::endl;
	return true;
}

	
bool PluginDef::execute()
{
	std::cout << "Executing plugin: Test plugin" << std::endl 
		<<"....Done. " << std::endl;
	return true;
}

bool PluginDef::destroy()
{
	std::cout << "Destroyed Test plugin" <<std::endl;	
	return true;
}