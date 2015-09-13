#ifndef PLUGIN_DEF_H
#define PLUGIN_DEF_H

#include "IPlugin.h"

class PluginDef : public IPlugin
{
public:
	const char *id();

	const char *name();

	int majorVersion();

	int minorVersion();

	bool init( IPlatformContext *context );
	
	bool execute();

	bool destroy();

	virtual ~PluginDef(void) {

	}
};

#endif 
