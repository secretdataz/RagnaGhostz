// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include <iostream>
#include "crypt.h"
#include "md5calc.h"

using namespace std;

namespace rA_common {
	// TODO: Also refactor md5calc if needed [Secretdataz]
	class MD5Crypt : public CryptInterface {
	public:
		string hash(string password, void* options) {
			char md5str[32 + 1];
			MD5_String(password.c_str(), md5str);
			return md5str;
		}

		// TODO: Implements a logic on this if needed [Secretdataz]
		bool needsRehash(string hash, void* options) {
			return false;
		}

		bool verify(string password, string hash, void* options) {
			string tmpStr;
			char md5str[32 + 1];
			MD5_String(password.c_str(), md5str);
			return hash.compare(md5str) == 0;
		}
		
	};
}
