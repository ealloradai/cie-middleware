#pragma once

#if defined __linux__ || defined __APPLE__
#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>
#endif

#if defined _WIN32 || defined _WIN64
#include <winscard.h>
#endif

class CCardContext
{
public:
	SCARDCONTEXT hContext;

	CCardContext(void);
	~CCardContext(void);

	operator SCARDCONTEXT();
	void validate();
	void renew();

private:
	void getContext();

};
