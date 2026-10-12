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
#include <iostream>

/**
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
	case msql_query_error::QUERY_ERROR_INVALID_OP:
		return "Invalid / Unsupported operation executed";
	case msql_query_error::QUERY_ERROR_UNKNOWN:
		return "Unknown error occurred. This may be a bug!";
	case msql_query_error::QUERY_ERROR_INVALID_SYNTAX:
		return "Invalid query syntax found";
	default:
		return "Unknown error occurred. This may be a bug!";
	}
}

msql_query::msql_query(const std::string& raw)
	: m_raw_query(raw)
{
}

msql_query::~msql_query() = default;

msql_query_error msql_query::parse()
{
	if (m_raw_query.empty()) {
		return msql_query_error::QUERY_ERROR_INVALID_SYNTAX;
	}

	std::vector<std::string> tokens = split(" ", m_raw_query);
	for (const std::string& str : tokens) {
		std::cout << str << '\n';
	}

	return msql_query_error::QUERY_ERROR_INVALID_SYNTAX;
}

msql_query_output_t msql_query::execute()
{
	parse();
	return m_info;
}

}
