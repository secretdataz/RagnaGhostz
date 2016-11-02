// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _STRLIB_HPP_
#define _STRLIB_HPP_

#include <cstdarg>
#include <string>

static std::string string_vsprintf(const char* format, std::va_list args) {
	va_list tmp_args;
	va_copy(tmp_args, args);
	const int required_len = vsnprintf(nullptr, 0, format, tmp_args) + 1;
	va_end(tmp_args);

	std::string buf(required_len, '\0');
	if (std::vsnprintf(&buf[0], buf.size(), format, args) < 0) {
		throw std::runtime_error{ "string_vsprintf encoding error" };
	}
	return buf;
}

static std::string string_sprintf(const char* format, ...) {
	std::va_list args;
	va_start(args, format);
	std::string str{ string_vsprintf(format, args) };
	va_end(args);
	return str;
}

#endif