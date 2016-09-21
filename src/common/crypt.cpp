// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "crypt.h"

using namespace std;

namespace rA_common {
	class PlainTextCrypt : public CryptInterface {
	public:
		string hash(string password, void* options) {
			return password;
		}

		bool needsRehash(string hash, void* options) {
			return false;
		}

		bool verify(string password, string hash, void* options) {
			return password == hash;
		}
	};
}
