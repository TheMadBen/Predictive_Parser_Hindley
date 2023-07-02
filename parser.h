/*
 * Created by Joshua Elkins
 *
 */
#ifndef __PARSER__H__
#define __PARSER__H__

#include <vector>
#include <string>
#include <unordered_map>
#include <vector>

#include "inputbuf.h"
#include "lexer.h"

class Parser {
	public:
		LexicalAnalyzer lexer;
		Token token;
		TokenType tempTokenType;
		int parse_program();

        struct Variable {
            std::string lexeme = "";
            TokenType type = NL;
            int line_num = 0;
            int aType = 0;
            bool printed = false;
        };
        int aInc = 0;

        std::string output = "";
        bool cont = false;

        std::unordered_map<std::string, Variable> map;   // map each ID to a struct variable
        std::vector<std::string> vec; // string vector to keep track of the order in which the variables were added

        std::vector<int> vecType;

	private:
        int parse_global_vars();
        int parse_var_decl_list();
        int parse_var_decl();
        int parse_var_list();
        int parse_type_name();
        int parse_body();
        int parse_stmt_list();
        int parse_stmt();
        int parse_assignment_stmt();
        Variable parse_expression();
        int parse_unary_operator();
        TokenType parse_binary_operator();
        Variable parse_primary();
        int parse_if_stmt();
        int parse_while_stmt();
        int parse_switch_stmt();
        int parse_case_list();
        int parse_case();

















};

#endif  //__PARSER__H__

