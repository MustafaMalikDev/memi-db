/**
 * This file is part of the memi-db distribution (https://github.com/MustafaMalikDev/memi-db)
 * Copyright (c) 2026 Mustafa Malik.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

//
// Copyright(c) 2016-2018 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

//
// Include a bundled header-only copy of fmtlib or an external one.
// By default spdlog include its own copy.
//
#include <spdlog/tweakme.h>

#if defined(SPDLOG_USE_STD_FORMAT) // SPDLOG_USE_STD_FORMAT is defined - use std::format
#	include <format>
#elif !defined(SPDLOG_FMT_EXTERNAL)
#	if !defined(SPDLOG_COMPILED_LIB) && !defined(FMT_HEADER_ONLY)
#		define FMT_HEADER_ONLY
#	endif
#	ifndef FMT_USE_WINDOWS_H
#		define FMT_USE_WINDOWS_H 0
#	endif
// enable the 'n' flag in for backward compatibility with fmt 6.x
#	define FMT_DEPRECATED_N_SPECIFIER
// enable ostream formatting for backward compatibility with fmt 8.x
#	define FMT_DEPRECATED_OSTREAM

#	include <spdlog/fmt/bundled/core.h>
#	include <spdlog/fmt/bundled/format.h>

#else // SPDLOG_FMT_EXTERNAL is defined - use external fmtlib
#	include <fmt/core.h>
#	include <fmt/format.h>
#endif
