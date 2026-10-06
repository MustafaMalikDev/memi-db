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

#ifndef _MEMIDB_CONFIG_H_
#define _MEMIDB_CONFIG_H_

#include "platform.h"

/*+----------------------------------------------+*/
/*+                 HELPER MACROS                +*/
/*+----------------------------------------------+*/

#define MEMI_DECLARE_SINGLETON(clazz, ...) static clazz& instance(__VA_ARGS__)

/* inspired by Qt source code */
#define MEMI_NO_COPY(clazz)           \
	clazz(const clazz&) = delete; \
	clazz& operator=(const clazz&) = delete;

#define MEMI_NO_MOVE(clazz)            \
	clazz(const clazz&&) = delete; \
	clazz& operator=(const clazz&&) = delete;

#define MEMI_NO_COPY_MOVE(clazz) \
	MEMI_NO_COPY(clazz)      \
	MEMI_NO_MOVE(clazz)

#endif /* _MEMIDB_CONFIG_H_ */
