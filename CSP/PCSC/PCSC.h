#if defined __linux__ || defined __APPLE__
#include <PCSC/winscard.h>
#include <PCSC/wintypes.h>
#endif

#if defined _WIN32 || defined _WIN64
#include <winscard.h>
#endif

#include "../Util/Array.h"
#include <vector>
#include <thread>

class safeConnection {
public:
	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;
	safeConnection(SCARDCONTEXT hContext, LPCSTR szReader, DWORD dwShareMode);
	safeConnection(SCARDHANDLE hCard);
	~safeConnection();
	operator SCARDHANDLE();
};

class safeTransaction{
	SCARDHANDLE hCard;
	bool locked;
	DWORD dwDisposition;
public:
	safeTransaction(safeConnection &conn, DWORD dwDisposition);
	void unlock();
	bool isLocked();
	~safeTransaction();
};

class readerMonitor {
	SCARDCONTEXT hContext;
	std::thread Thread;
	void *appData;
	void(*readerEvent)(std::string &reader, bool insert,void *appData);
	bool stopMonitor;
public:
	readerMonitor(void(*readerEvent)(std::string &reader, bool insert, void* appData), void* appData);
	~readerMonitor();
};
