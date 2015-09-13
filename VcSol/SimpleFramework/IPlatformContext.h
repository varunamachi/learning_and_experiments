#ifndef I_PLATFORM_CONTEXT
#define I_PLATFORM_CONTEXT

class IPlatformContext {

public:
	
	virtual int majorVersion() = 0;

	virtual int minorVersion() = 0;
	
	virtual void error( char *message) = 0;
};

#endif //I_PLATFORM_CONTEXT