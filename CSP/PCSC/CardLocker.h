#pragma once

#if defined __linux__ || defined __APPLE__
#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>
#endif

#if defined _WIN32 || defined _WIN64
#include <winscard.h>
#endif

#include "token.h"
#include "../Util/SyncroMutex.h"

class CCardLocker
{
	SCARDHANDLE hCard;
public:
	CCardLocker(SCARDHANDLE card);
	~CCardLocker(void);
	void Lock();
	void Unlock();
};
