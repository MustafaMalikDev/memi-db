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

#ifndef SPDLOG_HEADER_ONLY
#	include <spdlog/details/periodic_worker.h>
#endif

namespace spdlog
{
namespace details
{

// stop the worker thread and join it
SPDLOG_INLINE periodic_worker::~periodic_worker()
{
	if (worker_thread_.joinable()) {
		{
			std::lock_guard<std::mutex> lock(mutex_);
			active_ = false;
		}
		cv_.notify_one();
		worker_thread_.join();
	}
}

} // namespace details
} // namespace spdlog
