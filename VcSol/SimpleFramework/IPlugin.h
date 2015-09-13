#ifndef I_PLUGIN_H
#define I_PLUGIN_H

#include "IPlatformContext.h"

class IPlugin
{
public:
	virtual const char *id() = 0;

	virtual const char *name() = 0;

	virtual int majorVersion() = 0;

	virtual int minorVersion() = 0;

	virtual bool init( IPlatformContext *context ) = 0;
	
	virtual bool execute() = 0;

	virtual bool destroy() = 0;
};


#endif //I_PLUGIN_H