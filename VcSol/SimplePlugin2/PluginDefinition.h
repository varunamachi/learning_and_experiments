#ifndef PLUGIN_DEFINITION_H
#define PLUGIN_DEFINITION_H

#include "IPlugin.h"

class PluginDefinition : public IPlugin
{
public:
	
	PluginDefinition(void);
	
	virtual ~PluginDefinition(void);

	const char *id();

	const char *name();

	int majorVersion();

	int minorVersion();

	bool init( IPlatformContext *context );
	
	bool execute();

	bool destroy();
};

#endif //PLUGIN_DEFINITION_H