/*
 * Created by Joshua Elkins
 *
 */
#ifndef __PARSER__H__
#define __PARSER__H__

#include <vector>
#include <string>
#include <unordered_map>

#include "inputbuf.h"
#include "lexer.h"

class Parser {
	public:
		LexicalAnalyzer lexer;
		Token token;
		TokenType tempTokenType;
		void parse_program();

        std::unordered_map<std::string, TokenType> map;   // map each ID to a tokentype where NULL was added as a tokentype

	private:
        void syntax_error();

        void parse_global_vars();
        void parse_var_decl_list();
        void parse_var_decl();
        void parse_var_list();
        void parse_type_name();
        void parse_body();
        void parse_stmt_list();
        void parse_stmt();
        void parse_assignment_stmt();
        void parse_expression();
        void parse_unary_operator();
        void parse_binary_operator();
        void parse_primary();
        void parse_if_stmt();
        void parse_while_stmt();
        void parse_switch_stmt();
        void parse_case_list();
        void parse_case();

















};

#endif  //__PARSER__H__

