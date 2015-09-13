#include "PluginEntry.h"
#include "PluginDefinition.h"

void *getObject()
{
	return reinterpret_cast< void *>( new PluginDefinition() );
}