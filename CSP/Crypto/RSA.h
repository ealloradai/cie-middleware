#pragma once

#ifdef WIN32
#include <bcrypt.h>
#else
#include <openssl/bn.h>
#include <openssl/rsa.h>
#endif

#include "../Util/util.h"
#include "../Util/Array.h"

class CRSA
{
#ifdef WIN32
	BCRYPT_KEY_HANDLE key;
#else
	RSA* keyPriv;
#endif

public:
	CRSA(ByteArray &mod, ByteArray &exp);
	~CRSA(void);

	ByteDynArray RSA_PURE(ByteArray &data);
	void GenerateKey(DWORD size, ByteDynArray &module, ByteDynArray &pubexp, ByteDynArray &privexp);
	size_t KeySize;
};
