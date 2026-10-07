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
#	include <spdlog/async_logger.h>
#endif

#include <spdlog/details/thread_pool.h>
#include <spdlog/sinks/sink.h>

#include <memory>
#include <string>

SPDLOG_INLINE
spdlog::async_logger::async_logger(std::string logger_name,
				   sinks_init_list sinks_list,
				   std::weak_ptr<details::thread_pool> tp,
				   async_overflow_policy overflow_policy)
	: async_logger(std::move(logger_name), sinks_list.begin(),
		       sinks_list.end(), std::move(tp), overflow_policy)
{
}

SPDLOG_INLINE
spdlog::async_logger::async_logger(std::string logger_name,
				   sink_ptr single_sink,
				   std::weak_ptr<details::thread_pool> tp,
				   async_overflow_policy overflow_policy)
	: async_logger(std::move(logger_name), { std::move(single_sink) },
		       std::move(tp), overflow_policy)
{
}

// send the log message to the thread pool
SPDLOG_INLINE void spdlog::async_logger::sink_it_(const details::log_msg& msg){
	SPDLOG_TRY{ if (auto pool_ptr = thread_pool_.lock()){
		pool_ptr -> post_log(shared_from_this(), msg, overflow_policy_);
}
else
{
	throw_spdlog_ex("async log: thread pool doesn't exist anymore");
}
}
SPDLOG_LOGGER_CATCH(msg.source)
}

// send flush request to the thread pool
SPDLOG_INLINE void spdlog::async_logger::flush_(){
	SPDLOG_TRY{ auto pool_ptr = thread_pool_.lock();
if (!pool_ptr) {
	throw_spdlog_ex("async flush: thread pool doesn't exist anymore");
}

std::future<void> future =
	pool_ptr->post_flush(shared_from_this(), overflow_policy_);
// Wait for the flush operation to complete.
// This might throw exception if the flush message get dropped because of overflow.
future.get();
}
SPDLOG_LOGGER_CATCH(source_loc())
}

//
// backend functions - called from the thread pool to do the actual job
//
SPDLOG_INLINE void
spdlog::async_logger::backend_sink_it_(const details::log_msg& msg)
{
	for (auto& sink : sinks_) {
		if (sink->should_log(msg.level)) {
			SPDLOG_TRY
			{
				sink->log(msg);
			}
			SPDLOG_LOGGER_CATCH(msg.source)
		}
	}

	if (should_flush_(msg)) {
		backend_flush_();
	}
}

SPDLOG_INLINE void spdlog::async_logger::backend_flush_()
{
	for (auto& sink : sinks_) {
		SPDLOG_TRY
		{
			sink->flush();
		}
		SPDLOG_LOGGER_CATCH(source_loc())
	}
}

SPDLOG_INLINE std::shared_ptr<spdlog::logger>
spdlog::async_logger::clone(std::string new_name)
{
	auto cloned = std::make_shared<spdlog::async_logger>(*this);
	cloned->name_ = std::move(new_name);
	return cloned;
}
