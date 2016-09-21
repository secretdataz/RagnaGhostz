// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#pragma once
#ifndef rA_MD5_CRYPT_H
#define rA_MD5_CRYPT_H

#include "crypt.h"

using namespace std;

namespace rA_common {
	class MD5Crypt : public CryptInterface {
	public:
		string hash(string password, void* options);
		bool needsRehash(string hash, void* options);
		bool verify(string password, string hash, void* options);
	};
}
#endif /* !rA_MD5_CRYPT_H */
