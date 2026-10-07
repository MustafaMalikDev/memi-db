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

// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <spdlog/details/log_msg.h>
#include <spdlog/formatter.h>

namespace spdlog
{

namespace sinks
{
class SPDLOG_API sink {
public:
	virtual ~sink() = default;
	virtual void log(const details::log_msg& msg) = 0;
	virtual void flush() = 0;
	virtual void set_pattern(const std::string& pattern) = 0;
	virtual void
	set_formatter(std::unique_ptr<spdlog::formatter> sink_formatter) = 0;

	void set_level(level::level_enum log_level);
	level::level_enum level() const;
	bool should_log(level::level_enum msg_level) const;

protected:
	// sink log level - default is all
	level_t level_{ level::trace };
};

} // namespace sinks
} // namespace spdlog

#ifdef SPDLOG_HEADER_ONLY
#	include "sink-inl.h"
#endif
