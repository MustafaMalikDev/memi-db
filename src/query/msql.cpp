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

#include "query/msql.h"
#include "util/string.h"
#include "spdlog/spdlog.h"
#include <iostream>

static const std::vector<memi::msql_query_operation_t> g_operations = {
	{ .op_name = "PING", .require_key = false, .require_kv = false },
	{ .op_name = "GET", .require_key = true, .require_kv = false },
	{ .op_name = "SET", .require_key = true, .require_kv = true },
	{ .op_name = "UPDATE", .require_key = true, .require_kv = true },
	{ .op_name = "DELETE", .require_key = true, .require_kv = false }
};

/**
 * 	MEMI SIMPLE QUERY LANGUAGE (MSQL)
 *  ACCEPTABLE QUERY SYNTAX
 *  QUERY SYNTAX MUST BE UPPER CASE ONLY
 *  
 *  CONSTRAINTS (-1 FOR THE NULL TERMINATOR):
 *      QUERY KEYS MAX LEN 127 CHARS
 *      QUERY STATEMENT MAX LEN 255
 *      ONLY 1 QUERY PER REQUEST
 * 
 *  SYNTAX RULES:
 *      OP <KEY> <VALUE>
 *      OP <KEY>
 *      OP
 *  
 *  GET / SET OPERATIONS:
 *      GET <KEY>
 *          RETURNS VALUE
 *      
 *      SET <KEY> <VALUE> (NOTE THAT K,V IS SPLIT BY A WHITESPACE)
 *          RETURNS OK | ERROR <MSG> 
 * 
 *  UPDATE / DELETE OPERATIONS:
 *      UPD <KEY> <NEW VALUE>
 *          RETURNS OK | ERROR <MSG>
 *      
 *      DEL <KEY>
 *          RETURNS OK | ERROR <MSG>
 * 
 *  MISC OPERATIONS:
 *      PING
 *          RETURNS PONG <RESPONSE MILLIS>MS
 * 
 *      AUTHOR
 *          RETURNS <LIST OF AUTHORS>
 * 
 */

namespace memi
{

const char* msql_query_output_t::get_error_message() const noexcept
{
	switch (error_code) {
	case msql_query_error::QUERY_ERROR_KEY_NOT_FOUND:
		return "Could not find key";
	case msql_query_error::QUERY_ERROR_KEY_INVALID:
		return "Invalid key provided";
	case msql_query_error::QUERY_ERROR_VALUE_NOT_FOUND:
		return "Expected value to be set";
	case msql_query_error::QUERY_ERROR_INVALID_OP:
		return "Invalid / Unsupported operation executed";
	case msql_query_error::QUERY_ERROR_UNKNOWN:
		return "Unknown error occurred. This may be a bug!";
	case msql_query_error::QUERY_ERROR_INVALID_SYNTAX:
		return "Invalid query syntax found";
	case msql_query_error::QUERY_ERROR_QUERY_OK:
		return "Query OK";
	default:
		return "Unknown error occurred. This may be a bug!";
	}
}

bool msql_query_operation_t::operator==(const msql_query_operation_t& other)
{
	return (op_name == other.op_name) &&
	       (require_key == other.require_key) &&
	       (require_kv == other.require_kv);
}

bool msql_query_operation_t::operator!=(const msql_query_operation_t& other)
{
	return (op_name != other.op_name) &&
	       (require_key != other.require_key) &&
	       (require_kv != other.require_kv);
}

msql_query_operation_rule msql_query_operation_t::empty_query() noexcept
{
	return { .op_name = "", .require_key = false, .require_kv = false };
}

msql_query_operation_rule
msql_query_operation_t::get_op_from_name(const std::string& str) noexcept
{
	MEMI_RETURN_QUICK_IF(str.empty(), empty_query())

	for (msql_query_operation_t op : g_operations) {
		if (op.op_name == str) {
			return op;
		}
	}

	return empty_query();
}

msql_query::msql_query(const std::string& raw)
        : m_raw_query(raw)
{
}

msql_query::msql_query(const std::string&& raw)
        : m_raw_query(raw)
{
}

msql_query::~msql_query() = default;

msql_query_error msql_query::parse()
{
	if (m_raw_query.empty()) {
		return msql_query_error::QUERY_ERROR_INVALID_SYNTAX;
	}

	/**
	 *	expected tokens: OP (operation i.e GET/SET etc) KEY (optional, depends on the OP) 
	 *	VALUE (optional, depends on the OP)
	*/
	const std::vector<std::string> tokens        = split(" ", m_raw_query);
	const size_t                   tokens_count  = tokens.size();
	size_t                         current_index = 0;

	MEMI_RETURN_QUICK_IF(tokens.empty(),
	                     msql_query_error::QUERY_ERROR_UNKNOWN)

	const std::string&     first_op = tokens.at(0);
	msql_query_operation_t op =
	        msql_query_operation_t::get_op_from_name(first_op);

	if (op == msql_query_operation_t::empty_query()) {
		return msql_query_error::QUERY_ERROR_INVALID_OP;
	}

	m_info.op_name = op.op_name;

	if (op.require_key) {
		current_index++;
		MEMI_RETURN_QUICK_IF(
		        current_index >= tokens_count,
		        msql_query_error::QUERY_ERROR_KEY_NOT_FOUND)

		const std::string& key_token = tokens.at(current_index);
		MEMI_RETURN_QUICK_IF(key_token.empty(),
		                     msql_query_error::QUERY_ERROR_KEY_INVALID)

		m_info.key = key_token;
	}

	if (op.require_kv) {
		current_index++;
		MEMI_RETURN_QUICK_IF(
		        current_index >= tokens_count,
		        msql_query_error::QUERY_ERROR_VALUE_NOT_FOUND)

		const std::string& value_token = tokens.at(current_index);
		MEMI_RETURN_QUICK_IF(
		        value_token.empty(),
		        msql_query_error::QUERY_ERROR_VALUE_NOT_FOUND)

		m_info.value = value_token;
	}

	msql_query_error err_code = msql_query_error::QUERY_ERROR_QUERY_OK;
	m_info.error_code         = err_code;

	return err_code;
}

msql_query_output_t msql_query::execute()
{
	msql_query_error err = parse();

	if (m_info.error_code != msql_query_error::QUERY_ERROR_QUERY_OK) {
		std::cout << m_info.get_error_message() << '\n';
	} else {
		std::cout << "operation: " << m_info.op_name << '\n';
		std::cout << "key: " << m_info.key << '\n';
		std::cout << "value: " << m_info.value << '\n';
	}

	return m_info;
}

}
