// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#pragma once
#ifndef _ENUM_OPERATOR_H_
#define _ENUM_OPERATOR_H_

#include <cstdint>

#define ENUM_OP(op, type, inttype) \
type operator op (type lhs, type rhs) { \
	return static_cast<type>(static_cast<inttype>(lhs) op static_cast<inttype>(rhs)); \
}

#define ENUM_OP_INT32(op, type) ENUM_OP(op, type, int32_t)
#define ENUM_OP_UINT32(op, type) ENUM_OP(op, type, uint32_t)
#define ENUM_OP_INT64(op, type) ENUM_OP(op, type, int64_t)
#define ENUM_OP_UINT64(op, type) ENUM_OP(op, type, uint64_t)

#define ENUM_COP_INT32(op, type) ENUM_COP(op, type, int32_t)

#define ENUM_ENABLE_BITWISE_OPERATORS(type) \
	ENUM_OP_INT32(|, type); \
	ENUM_OP_INT32(&, type);

#endif
