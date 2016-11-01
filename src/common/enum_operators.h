/*
Copyright (c) 2013, Yuri Yaryshev (aka Lord Odin)

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
Usage sample:

#indlude "enum_flags.h"

ENUM_FLAGS(foo_t)
enum class foo_t
	{
	 none			= 0x00
	,a				= 0x01
	,b				= 0x02
	};
	
ENUM_FLAGS(foo2_t)
enum class foo2_t
	{
	 none			= 0x00
	,d				= 0x01
	,e				= 0x02
	};	

int _tmain(int argc, _TCHAR* argv[])
	{
	if(flags(foo_t::a & foo_t::b)) {};
	// if(flags(foo2_t::d & foo_t::b)) {};	// Type safety test - won't compile if uncomment
	};

*/

#ifndef __ENUM_OPERATORS_H__
#define __ENUM_OPERATORS_H__

/*
Use this line before header, if you don't want flags(T x) function to be implemented for your enum.
#define USE_ENUM_FLAGS_FUNCTION 0
*/

#ifndef USE_ENUM_FLAGS_FUNCTION
#define USE_ENUM_FLAGS_FUNCTION 1
#endif


#define ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T) \
enum class T : INT_T; \
inline T	operator	&	(T x, T y)		{	return static_cast<T>	(static_cast<INT_T>(x) & static_cast<INT_T>(y));	}; \
inline T	operator	&	(T x, INT_T y)		{	return static_cast<T>	(static_cast<INT_T>(x) & y);	}; \
inline T	operator	|	(T x, T y)		{	return static_cast<T>	(static_cast<INT_T>(x) | static_cast<INT_T>(y));	}; \
inline T	operator	|	(T x, INT_T y)		{	return static_cast<T>	(static_cast<INT_T>(x) | y);	}; \
inline T	operator	^	(T x, T y)		{	return static_cast<T>	(static_cast<INT_T>(x) ^ static_cast<INT_T>(y));	}; \
inline T	operator	~	(T x)			{	return static_cast<T>	(~static_cast<INT_T>(x));							}; \
inline T&	operator	&=	(T& x, T y)		{	x = x & y;	return x;	}; \
inline T&	operator	|=	(T& x, T y)		{	x = x | y;	return x;	}; \
inline T&	operator	&=	(T& x, INT_T y) { x = x & static_cast<T>(y);	return x; }; \
inline T&	operator	|=	(T& x, INT_T y) { x = x | static_cast<T>(y);	return x; }; \
inline INT_T	operator	&=	(INT_T x, T& y) { x = x & static_cast<INT_T>(y);	return x; }; \
inline INT_T	operator	|=	(INT_T x, T& y) { x = x | static_cast<INT_T>(y);	return x; }; \
inline T&	operator	^=	(T& x, T y)		{	x = x ^ y;	return x;	}; \
inline T	operator	&	(INT_T x, T y)	{ return static_cast<T>(x & static_cast<INT_T>(y)); } \
inline T	operator	|	(INT_T x, T y)	{ return static_cast<T>(x | static_cast<INT_T>(y)); }

#if(USE_ENUM_FLAGS_FUNCTION)

	#define ENUM_FLAGS_EX(T,INT_T) ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T) \
	inline bool			flags(T x)			{	return static_cast<INT_T>(x) != 0;};

#else

	#define ENUM_FLAGS_EX(T,INT_T) ENUM_FLAGS_EX_NO_FLAGS_FUNC(T,INT_T) 

#endif

#define ENUM_FLAGS(T) ENUM_FLAGS_EX(T,intptr_t)

// Operators that return boolean [Secretdataz]
#define ENUM_BOOL_OP(OP, T, INT_T) inline bool operator OP (T lhs, T rhs) { return static_cast<INT_T>(lhs) OP static_cast<INT_T>(rhs); }
#define ENUM_COMPARISON_OPERATORS(T, INT_T) \
enum class T : INT_T; \
ENUM_BOOL_OP(>, T, INT_T); \
ENUM_BOOL_OP(>=, T, INT_T); \
ENUM_BOOL_OP(<, T, INT_T); \
ENUM_BOOL_OP(<=, T, INT_T); \
inline bool operator == (T x, INT_T y) { return static_cast<INT_T>(x) == y; } \
inline bool operator == (INT_T x, T y) { return static_cast<INT_T>(y) == x; } \
inline bool operator ! (T x) { return static_cast<INT_T>(x) == 0; }
#endif