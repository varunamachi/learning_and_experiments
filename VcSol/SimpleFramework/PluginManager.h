#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include "IPlugin.h"


class PluginManager
{
	typedef std::map< std::string, std::pair< std::string, HINSTANCE > >::iterator LibIter;

	typedef std::map< std::string, IPlugin *>::iterator PluginIter;
public:
	PluginManager( std::string pluginDirPath );

	virtual ~PluginManager(void);

	bool load( std::string pluginLibPath );

	bool reload( std::string pluginId );

	bool unload( std::string pluginId );

	bool unloadAll( );

	std::vector< IPlugin *> getLoadedPlugins();

	friend std::ostream& operator<<( std::ostream &stream, PluginManager& pm);

private:

	bool searchAndLoad( std::string path );

	bool loadLib( std::string path );

	std::map< std::string, IPlugin *> m_plugins;

	std::map< std::string, std::pair< std::string, HINSTANCE > > m_pluginLib;

	IPlatformContext *m_platformContext;
};

#endif //PLUGIN_MANAGER_H