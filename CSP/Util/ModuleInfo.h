#pragma once
#include "util.h"

#if !defined (_MSC_VER) && !defined HANDLE
#define HANDLE void*
#endif

class CModuleInfo
{
	HANDLE module;
public:
	std::string szModuleFullPath;
	std::string szModulePath;
	std::string szModuleName;

	CModuleInfo(void);
	virtual ~CModuleInfo(void);
	static HANDLE getApplicationModule();
	HANDLE getModule();
	void init(HANDLE module);
};
