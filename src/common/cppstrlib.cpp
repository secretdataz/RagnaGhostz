// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include <cstdarg>
#include <string>

#include "cppstrlib.hpp"

std::string string_vsprintf(std::string format, std::va_list args) {
	va_list tmp_args;
	va_copy(tmp_args, args);
	const int required_len = std::vsnprintf(nullptr, 0, format.c_str(), tmp_args);
	va_end(tmp_args);

	std::string buf(required_len + 1, '\0');
	if (std::vsnprintf(&buf[0], buf.size(), format.c_str(), args) < 0) {
		throw std::runtime_error{ "string_vsprintf encoding error" };
	}
	return std::string(buf.c_str());
}

std::string string_sprintf(std::string format, ...) {
	std::va_list args;
	va_start(args, format);
	std::string str{ string_vsprintf(format, args) };
	va_end(args);
	return str;
}
