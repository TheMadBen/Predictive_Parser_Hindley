#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "inputbuf.h"
#include "parser.h"

using namespace std;

void Parser::syntax_error() {
    cout << "\nSyntax Error ";
}

void Parser::parse_program() {
    token = lexer.GetToken();

    if(token.token_type == ID) { // first of global_vars
        lexer.UngetToken(token);
        cout << "\n Rule parsed: program -> global_vars scope \n";
        parse_global_vars();
        parse_body();
    }
    else if(token.token_type == LBRACE) { // global_vars -> epsilon = first of body
        lexer.UngetToken(token);
        cout << "\n Rule parsed: global_vars -> epsilon \n";
        parse_body();
    }
    else {
        syntax_error();
        cout << "in parse_program\n";
    }
}

void Parser::parse_global_vars() {
    token = lexer.GetToken();

    if(token.token_type == ID) {
        lexer.UngetToken(token);
        cout << "\n Rule parsed: globalVars -> var_decl_list \n";
        parse_var_decl_list();
    }
    else {
        syntax_error();
        cout << "in parse_global_vars\n";
    }
}

void Parser::parse_var_decl_list() {
    token = lexer.GetToken();

    while(token.token_type == ID) {
        lexer.UngetToken(token);
        parse_var_decl();
        if(token.token_type != ID) {
            cout << "\n Rule Parsed: var_decl_list -> var_decl \n";
        }
        else {
            cout << "\n Rule Parsed: var_decl_list -> var_decl var_decl_list \n";
        }
    }
    lexer.UngetToken(token);
}

void Parser::parse_var_decl() {
    token = lexer.GetToken();

    if(token.token_type == ID) {
        lexer.UngetToken(token);
        parse_var_list();

        token = lexer.GetToken();
        if(token.token_type == COLON) {
            parse_type_name();

            token = lexer.GetToken();
            if(token.token_type == SEMICOLON) {
                cout << "\n Rule parsed: var_decl -> var_list COLON type_name SEMICOLON";
            }
            else {
                syntax_error();
                cout << "in parse_var_decl - 3\n";
            }
        }
        else {
            syntax_error();
            cout << "in parse_var_decl - 2\n";
        }
    }
    else {
        syntax_error();
        cout << "in parse_var_decl - 1\n";
    }
}

void Parser::parse_var_list() {
    token = lexer.GetToken();

    if(token.token_type == ID) {
        token = lexer.GetToken();
        if(token.token_type == COMMA) {
            cout << "\n Rule Parsed: var_list -> ID COMMA var_list \n";
            parse_var_list();
        }
        else if(token.token_type == COLON) {
            lexer.UngetToken(token);
            cout << "\n Rule Parsed: var_list -> ID \n";
        }
        else {
            syntax_error();
            cout << "in parse_var_list - 2\n";
        }
    }
    else {
        syntax_error();
        cout << "in parse_var_list - 1\n";
    }
}

void Parser::parse_type_name() {
    token = lexer.GetToken();

}

void Parser::parse_body() {
    token = lexer.GetToken();

}

void Parser::parse_stmt_list() {
    token = lexer.GetToken();

}

void Parser::parse_stmt() {
    token = lexer.GetToken();

}

void Parser::parse_assignment_stmt() {
    token = lexer.GetToken();

}

void Parser::parse_expression() {
    token = lexer.GetToken();


}

void Parser::parse_unary_operator() {
    token = lexer.GetToken();

}

void Parser::parse_binary_operator() {
    token = lexer.GetToken();

}

void Parser::parse_primary() {
    token = lexer.GetToken();

}

void Parser::parse_if_stmt() {
    token = lexer.GetToken();

}

void Parser::parse_while_stmt() {
    token = lexer.GetToken();

}

void Parser::parse_switch_stmt() {
    token = lexer.GetToken();

}

void Parser::parse_case_list() {
    token = lexer.GetToken();

}

void Parser::parse_case() {
    token = lexer.GetToken();

}

int main() {

    Parser parser;
    parser.parse_program();

    return(0);
};