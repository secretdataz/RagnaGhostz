// Copyright (c) rAthena Dev Team - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _CPPSTRLIB_HPP_
#define _CPPSTRLIB_HPP_

#include <cstdarg>
#include <string>

std::string string_vsprintf(std::string format, std::va_list args);
std::string string_sprintf(std::string format, ...);

#endif
