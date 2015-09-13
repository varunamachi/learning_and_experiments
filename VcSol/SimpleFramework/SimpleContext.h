#ifndef SIMPLE_CONTEXT_H
#define SIMPLE_CONTEXT_H

#include "IPlatformContext.h"

class SimpleContext : public IPlatformContext
{
public:
	
	int majorVersion();

	int minorVersion();

	void error( char *message );

	virtual ~SimpleContext(void);
};

#endif //SIMPLE_CONTEXT_H