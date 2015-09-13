#include "PluginDefinition.h"
#include "IPlugin.h"
#include "IPlatformContext.h"
#include <iostream>

PluginDefinition::PluginDefinition(void)
{

}

PluginDefinition::~PluginDefinition(void)
{

}

const char *PluginDefinition::id()
{
	return "724F5DFA-5715-4F86-8B5D-BB4185840FDA";
}

const char *PluginDefinition::name()
{
	return "Test2";
}

int PluginDefinition::majorVersion()
{
	return 1;
}

int PluginDefinition::minorVersion()
{
	return 0;
}

bool PluginDefinition::init( IPlatformContext *context )
{
		std::cout << "Initiating plugin: Test plugin" << std::endl
			<< "Platform version: " 
			<< context->majorVersion() << "." << context->minorVersion() 
			<< std::endl;
		return true;
}

	
bool PluginDefinition::execute()
{
	std::cout << "Executing plugin: Test plugin" << std::endl 
		<<"....Done. " << std::endl;
	return true;
}

bool PluginDefinition::destroy()
{
	std::cout << "Destroyed Test plugin" <<std::endl;	
	return true;
}
