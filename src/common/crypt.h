// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder


#pragma once
#ifndef rA_CRYPT_H
#define rA_CRYPT_H

#include <iostream>
using namespace std;

namespace rA_common {
	class CryptInterface {
	public:
		virtual string hash(string password, void* options) = 0;
		virtual bool needsRehash(string hash, void* options) = 0;
		virtual bool verify(string password, string hash, void* options) = 0;
	};
}

#endif /* !rA_CRYPT_H */
