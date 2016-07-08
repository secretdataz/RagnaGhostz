// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder
#ifndef	_DES_H_
#define	_DES_H_

#include "cbasetypes.h"

/// One 64-bit block.
struct BIT64 { uint8_t b[8]; };


void des_decrypt_block(BIT64* block);
void des_decrypt(unsigned char* data, size_t size);

#endif // _DES_H_
