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

#ifndef _MEMIDB_PLATFORM_H_
#define _MEMIDB_PLATFORM_H_

/*+----------------------------------------------+*/
/*+                  OS PLATFORM                 +*/
/*+----------------------------------------------+*/
#if defined(__APPLE__)
#	include <TargetConditionals.h>
#	if defined(TARGET_OS_MAC) || defined(TARGET_OS_OSX)
#		define MEMI_PLAT_OSX
#	else
#		error Unsupported macOS platform
#	endif
#elif defined(__linux__) || defined(__linux) || defined(linux)
#	define MEMI_PLAT_LINUX
#elif defined(_WIN32) || defined(_WIN64)
#	define MEMI_PLAT_WINDOWS
#else
#	error Unknown platform. memi-db only supports macOS (aarch64), Linux and Windows (32/64 bit)
#endif

/*+----------------------------------------------+*/
/*+                CPU ARCHITECTURE              +*/
/*+----------------------------------------------+*/
#if defined(__x86_64__) || defined(_M_X64)
#	define MEMI_ARCH_x86_64
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#	define MEMI_ARCH_x86_32
#elif defined(__aarch64__) || defined(_M_ARM64)
#	define MEMI_ARCH_ARM64
#else
#	error Unsupported CPU Architecture
#endif

#endif /* _MEMIDB_PLATFORM_H_ */
