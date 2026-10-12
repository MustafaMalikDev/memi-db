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

#ifndef _MEMIDB_QUERY_MSQL_H_
#define _MEMIDB_QUERY_MSQL_H_

#include "config.h"
#include <string>

namespace memi
{

enum class msql_query_option : uint8_t {
	QUERY_OPTION_PING_OP,
	QUERY_OPTION_GET_OP,
	QUERY_OPTION_SET_OP,
	QUERY_OPTION_UPDATE_OP,
	QUERY_OPTION_DELETE_OP
};

enum class msql_query_error : uint8_t {
	QUERY_ERROR_KEY_NOT_FOUND,
	QUERY_ERROR_KEY_INVALID,
	QUERY_ERROR_VALUE_NOT_FOUND,
	QUERY_ERROR_INVALID_OP,
	QUERY_ERROR_INVALID_SYNTAX,
	QUERY_ERROR_UNKNOWN,
	QUERY_ERROR_QUERY_OK
};

typedef struct msql_query_operation_rule {
	std::string_view op_name;
	bool             require_key;
	bool require_kv; /* no need for a value field because key must be set to handle the value */

	static msql_query_operation_rule empty_query() noexcept;
	static msql_query_operation_rule
	get_op_from_name(const std::string& str) noexcept;

	bool operator==(const msql_query_operation_rule& other);
	bool operator!=(const msql_query_operation_rule& other);
} msql_query_operation_t;

typedef struct msql_query_exec_output {
	std::string      op_name;
	std::string      key;
	std::string      value;
	msql_query_error error_code;

	bool has_output;
	bool is_executed_ok;

	const char* get_error_message() const noexcept;
} msql_query_output_t;

class msql_query final {
public:
	msql_query(const std::string& raw);
	msql_query(const std::string&& raw);
	~msql_query();

	MEMI_NO_COPY_MOVE(msql_query);

private:
	MEMI_FORCE_USE msql_query_error parse();

public:
	MEMI_FORCE_USE msql_query_output_t execute();

private:
	std::string         m_raw_query;
	msql_query_output_t m_info;
	msql_query_option   m_option;
};

}

#endif /* _MEMIDB_QUERY_MSQL_H_ */
