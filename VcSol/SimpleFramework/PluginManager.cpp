#include "PluginManager.h"
#include "SimpleContext.h"



PluginManager::PluginManager( std::string pluginDirPath ) :
	m_platformContext( new SimpleContext() )
{
	load( pluginDirPath );
}

PluginManager::~PluginManager()
{
	unloadAll();
	delete m_platformContext;
}

bool PluginManager::load( std::string pluginLibPath )
{
	return searchAndLoad( pluginLibPath );
}

bool PluginManager::reload( std::string pluginId )
{
	LibIter hit = m_pluginLib.find( pluginId );
	if( hit != m_pluginLib.end() ) {
		std::string libPath = hit->second.first;
		if( unload( pluginId ) ) {
			return load( libPath );
		}
	}
	return false;
}

bool PluginManager::unload( std::string pluginId )
{
	PluginIter  pit = m_plugins.find( pluginId );
	LibIter hit = m_pluginLib.find( pluginId);
	if( pit == m_plugins.end() || hit == m_pluginLib.end() ) {
		return false;
	}
	IPlugin *plugin = pit->second;
	HINSTANCE hInst = hit->second.second;
	plugin->destroy();
	m_plugins.erase( pit );
	FreeLibrary( hInst );
	m_pluginLib.erase( hit );
}

bool PluginManager::unloadAll( )
{
	try {
		PluginIter pit = m_plugins.begin();
		for( ; pit != m_plugins.end(); ++ pit ) {
			pit->second->destroy();
			delete pit->second;
		}
		m_plugins.clear();
		LibIter hit = m_pluginLib.begin();
		for( ; hit != m_pluginLib.end(); ++ hit ) {
			FreeLibrary( hit->second.second );
		}
		m_pluginLib.clear();
	} catch( ... ) {
		return false;
	}
	return true;
}

std::vector< IPlugin *> PluginManager::getLoadedPlugins()
{
	std::vector< IPlugin *> list;
	PluginIter it = m_plugins.begin();
	for( ; it != m_plugins.end(); ++ it ) {
		list.push_back( it->second );
	}
	return list;
	
}

std::ostream& operator<<( std::ostream &stream, PluginManager& pm)
{
	stream << "------------------------------------------------------------------------------"<<std::endl;
	PluginManager::PluginIter pit = pm.m_plugins.begin();
	int i = 1;
	for( ;pit != pm.m_plugins.end(); ++ pit ) {
		IPlugin *plugin = pit->second;
		std::string path = pm.m_pluginLib.find( plugin->id() )->second.first;
		stream 
			<< "Plugin[" << i <<"] " << plugin->id() << std::endl
			<< "Name	   " << plugin->name() << std::endl 
			<< "Version    " << plugin->majorVersion() <<"."<<plugin->minorVersion() << std::endl
			<< "Path       " << path << std::endl
			<< "------------------------------------------------------------------------------"<<std::endl;
	}
	return stream;
}

bool PluginManager::searchAndLoad( std::string path )
{
	DWORD result = GetFileAttributes( path.c_str() );
	if( result & FILE_ATTRIBUTE_DIRECTORY ) {
		std::string pathPattern = path + "\\*.dll";
		WIN32_FIND_DATA findData;
		HANDLE handle = FindFirstFile( pathPattern.c_str(), &findData );
		if( handle == INVALID_HANDLE_VALUE ) {
			std::cerr << "Error while loading files from "<< pathPattern << std::endl;
			return false;
		}
		bool loaded = true;
		while( FindNextFile( handle, &findData )) {
			loaded &= loadLib( path + "\\" + findData.cFileName );
		}
		return loaded;
	}
	else {
		return load( path );
	}
	return false;
}

bool PluginManager::loadLib( std::string path )
{
	typedef void *( *func ) ();
	HINSTANCE libInst = LoadLibrary( path.c_str() );
	if(  ! libInst ) {
		std::cerr << "Could not load library " << path << std::endl;
		return false;
	}
	func getObject = ( func ) GetProcAddress( libInst, "getObject" );
	if( ! getObject ) {
		std::cerr << "Incompitable plugin '" << path << "' found. Unloading...." <<
			std::endl;
		FreeLibrary( libInst );
		return false;
	}
	IPlugin *plugin = reinterpret_cast< IPlugin *>( getObject() );
	plugin->init( m_platformContext );
	m_plugins.insert( std::make_pair( plugin->id(), plugin ));
	m_pluginLib.insert( std::make_pair( plugin->id(), std::make_pair( path, libInst )));
	return true;
}
