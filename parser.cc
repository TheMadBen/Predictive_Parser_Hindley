/*
 * Created by: Joshua Elkins
 * Date: June 24th, 2023
 */

#include <iostream>
#include <string>
#include "parser.h"
#include "lexer.h"
#include "inputbuf.h"

using namespace std;

// Syntax Error Function.
void syntax_error() {
    cout << "Syntax Error\n";
    exit(1);
}

void type_mismatch(int line_num, std::string error) {
    cout << "TYPE MISMATCH " << line_num << " " << error << endl;
    exit(1);
}

/*
 * Completed Function.
 * Entry point to the program.
 */
int Parser::parse_program(){
#ifdef DEBUG
    cout << "Entered Parse Program" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type == ID){
        lexer.UngetToken(token);
        parse_global_vars();
        parse_body();
    }
    else if(token.token_type == LBRACE){
        lexer.UngetToken(token);
        parse_body();
    }
    else{
        syntax_error();
    }

    return 0;
}

/*
 * Completed Function.
 * Acts as basic entry into the global variable list.
 */
int Parser::parse_global_vars(){
#ifdef DEBUG
    cout << "Entered Parse Global Variables" << endl;
#endif
    parse_var_decl_list();

    return 0;
}

/*
 * Completed
 * Loops our variable declaration list.
 */
int Parser::parse_var_decl_list() {
#ifdef DEBUG
    cout << "Entered Parse Variable Declaration List" << endl;
#endif
    token = lexer.GetToken();
    while(token.token_type == ID){
        lexer.UngetToken(token);
        parse_var_decl();
        token = lexer.GetToken();
    }
    lexer.UngetToken(token);

    return 0;
}

/*
 * Completed Function
 * Acts as a method to handle the declaration statements.
 */
int Parser::parse_var_decl(){
#ifdef DEBUG
    cout << "Entered Parse Variable Declaration" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type != ID){
        syntax_error();
    }
    lexer.UngetToken(token);
    parse_var_list();
    token = lexer.GetToken();
    if(token.token_type != COLON){
        syntax_error();
    }
    token = lexer.GetToken();
    if(token.token_type == INT || token.token_type == REAL || token.token_type == BOO){
        lexer.UngetToken(token);
        parse_type_name();
        token = lexer.GetToken();
        if(token.token_type != SEMICOLON){
            syntax_error();
        }
    }
    else{
        syntax_error();
    }

    return 0;
}

/*
 * Completed Function
 * Acts as the gathering function for our variables
 */
int Parser::parse_var_list(){
#ifdef DEBUG
    cout << "Entered Parse Variable List" << endl;
#endif
    token = lexer.GetToken();

    if(token.token_type == ID) {
        // since we are in parse_var_list, we know that we went through parse_global_vars
        // so these are explicit declarations
        Variable variable;
        variable.line_num = token.line_no;

        map.insert({token.lexeme, variable});
        vec.push_back(token.lexeme);

        token = lexer.GetToken();
        if(token.token_type == COMMA) {
            parse_var_list();
        }
        else if(token.token_type == COLON) {
            lexer.UngetToken(token);
        }
        else {
            syntax_error();
        }
    }
    else {
        syntax_error();
    }

    return 0;
}

/*
 * Completed Function
 * Just consumes the INT, REAL, or BOO tokens
 */
int Parser::parse_type_name(){
#ifdef DEBUG
    cout << "Entered Parse Type Name" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type == INT){
        // We'll be gathering info here
        for (auto itr = map.begin(); itr != map.end(); itr++) {
            if(token.line_no == itr->second.line_num)
                itr->second.type = INT;
        }
    }
    else if(token.token_type == REAL){
        // We'll be gathering info here
        for (auto itr = map.begin(); itr != map.end(); itr++) {
            if(token.line_no == itr->second.line_num)
                itr->second.type = REAL;
        }
    }
    else if(token.token_type == BOO){
        // We'll be gathering info here
        for (auto itr = map.begin(); itr != map.end(); itr++) {
            if(token.line_no == itr->second.line_num)
                itr->second.type = BOO;
        }
    }
    else{
        syntax_error();
    }

    return 0;
}

/*
 * Completed Function
 * Acts as the method to consume braces and enter statement list
 */
int Parser::parse_body(){
#ifdef DEBUG
    cout << "Entered Parse Body" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type == LBRACE){
        parse_stmt_list();
        token = lexer.GetToken();
        if(token.token_type != RBRACE){
            syntax_error();
        }
        token = lexer.GetToken();
        if(token.token_type == END_OF_FILE) {
            lexer.UngetToken(token);

//            cout << "vector of insertion order (vec): corresponding aType" << endl;
//            for(int i = 0; i < vec.size(); i++) {
//                cout << vec[i] << "\t" << map.at(vec[i]).aType << endl;
//            }


            // at the very end this is where we want to print

            for(int i = 0; i < vec.size(); i++) {

                string type = "";
                if(map.at(vec[i]).type == INT) {
                    type = "int";
                    map.at(vec[i]).printed = true;
                    output += vec[i];
                    output += ": ";
                    output += type;
                    output += " #\n";
                }
                else if(map.at(vec[i]).type == REAL) {
                    type = "real";
                    map.at(vec[i]).printed = true;
                    output += vec[i];
                    output += ": ";
                    output += type;
                    output += " #\n";
                }
                else if(map.at(vec[i]).type == BOO) {
                    type = "bool";
                    map.at(vec[i]).printed = true;
                    output += vec[i];
                    output += ": ";
                    output += type;
                    output += " #\n";
                }
                else {
                    type = "?";
                    if(map.at(vec[i]).printed == false) { // this is where it'll be grouped

                        int first = map.at(vec[i]).aType;

                        for(int j = i; j < vec.size(); j++) {   // could be int j = 0 instead
                            if(map.at(vec[j]).aType == first) {
                                map.at(vec[j]).printed = true;
                                output += vec[j];
                                output += ", ";
                            }
                        }
                        output = output.substr(0, output.size()-2);
                        output += ": ";
                        output += type;
                        output += " #\n";
                    }

                }
            }
            // out for loop

            cout << output;
        }
        else {
            lexer.UngetToken(token);
        }
    }
    else{
        syntax_error();
    }

    return 0;
}

/*
 * Completed Function
 * Acts as our looper to enter all our statements
 */
int Parser::parse_stmt_list(){
#ifdef DEBUG
    cout << "Entered Parse Statement List" << endl;
#endif
    token = lexer.GetToken();
    while(token.token_type == ID || token.token_type == IF || token.token_type == WHILE || token.token_type == SWITCH){
        lexer.UngetToken(token);
        aInc++;
        parse_stmt();
        token = lexer.GetToken();
    }
    lexer.UngetToken(token);

    return 0;
}

/*
 * Completed Function
 * Acts as our method to enter the specific statements
 */
int Parser::parse_stmt(){
#ifdef DEBUG
    cout << "Entered Parse Statement" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type == ID){
        lexer.UngetToken(token);
        parse_assignment_stmt();
    }
    else if(token.token_type == IF){
        lexer.UngetToken(token);
        parse_if_stmt();
    }
    else if(token.token_type == WHILE){
        lexer.UngetToken(token);
        parse_while_stmt();
    }
    else if(token.token_type == SWITCH){
        lexer.UngetToken(token);
        parse_switch_stmt();
    }
    else{
        syntax_error();
    }

    return 0;
}

/*
 * Function Completed
 * Acts as our assignment statement parser
 */
int Parser::parse_assignment_stmt() {
#ifdef DEBUG
    cout << "Entered Parse Assignment Statement" << endl;
#endif
    Variable exprType;
    Variable lhsType;

    token = lexer.GetToken();
    if(token.token_type != ID){
        syntax_error();
    }
    // Do something with ID
    // this is the LHS
    // check the type of ID
    if(map.find(token.lexeme) != map.end()) {
        // found
        lhsType.lexeme = token.lexeme;
        lhsType.type = map.at(token.lexeme).type;
        lhsType.line_num = token.line_no;
        lhsType.aType = map.at(token.lexeme).aType;

        map.at(token.lexeme).line_num = token.line_no;  // update line number of id to where it was read

    }
    else {
        // not found which means that it's implicit and the first occurrence of it
        Variable variable;                  // create the variable to add to map
        variable.lexeme = token.lexeme;
        variable.type = T;
        variable.line_num = token.line_no;
        variable.aType = aInc;

        map.insert({token.lexeme, variable});
        vec.push_back(token.lexeme);

        lhsType = variable;
    }

    token = lexer.GetToken();
    if(token.token_type != EQUAL){
        syntax_error();
    }

    exprType = parse_expression();

    // at this point, we have the lhs and the rhs types, so we have to update them or throw mismatch error
    if(lhsType.type == T && (exprType.type == INT || exprType.type == REAL || exprType.type == BOO)) {
        map.at(lhsType.lexeme).type = exprType.type;  // update lhs
        lhsType.type = exprType.type;

        for(string i : vec) {   // go through the map and check if any other variables have the same aType, if so then change it
            if(map.at(i).aType == lhsType.aType) {
                map.at(i).type = lhsType.type;
            }
        }
    }
    if((lhsType.type == INT || lhsType.type == REAL || lhsType.type == BOO) && exprType.type == T) {
        map.at(exprType.lexeme).type = lhsType.type;    // update rhs (expr)
        exprType.type = lhsType.type;

        for(string i : vec) {   // go through the map and check if any other variables have the same aType, if so then change it
            if(map.at(i).aType == exprType.aType) {
                map.at(i).type = exprType.type;
            }
        }
    }
    if(lhsType.type == T && exprType.type == T) {
        int sameType = map.at(exprType.lexeme).aType;

        map.at(lhsType.lexeme).aType = lhsType.aType;
        map.at(exprType.lexeme).aType = lhsType.aType;
        exprType.aType = lhsType.aType;      // in the case they are both T, update exprType to aType of lhsType

        for(string i : vec) {
            if(map.at(i).aType == sameType) {
                map.at(i).aType = lhsType.aType;
            }
        }
    }

    if(lhsType.type != exprType.type) {
        type_mismatch(token.line_no, "C1");
    }


    token = lexer.GetToken();
    if(token.token_type != SEMICOLON){
        syntax_error();
    }

    return 0;
}

/*
 * Completed Function
 * Acts as our expression handling.
 */
Parser::Variable Parser::parse_expression(){
#ifdef DEBUG
    cout << "Entered Parse Expression" << endl;
#endif
    Variable v;
    TokenType operatorType = NL;
    Variable v1;
    Variable v2;
    int sameType;

    token = lexer.GetToken();
    if(token.token_type == NOT){
        lexer.UngetToken(token);
        parse_unary_operator();
        v = parse_expression();
        if(v.type != BOO) {
            type_mismatch(token.line_no, "C3");
        }
    }
    else if(token.token_type == PLUS || token.token_type == MINUS || token.token_type == MULT ||  token.token_type == DIV){
        lexer.UngetToken(token);
        parse_binary_operator();
        v1 = parse_expression();
        v2 = parse_expression();

        if((v1.type == INT || v1.type == REAL || v1.type == BOO) && v2.type == T) {
            sameType = map.at(v2.lexeme).aType;
            map.at(v2.lexeme).type = v1.type;
            map.at(v2.lexeme).aType = v1.aType;
            v2.type = v1.type;  // update the unknown type T

            for(string i : vec) {
                if(map.at(i).aType == sameType) {
                    map.at(i).aType = v1.aType;
                    map.at(i).type = v1.type;
                }
            }
        }

        if(v1.type == T && (v2.type == INT || v2.type == REAL || v2.type == BOO)) {
            sameType = map.at(v1.lexeme).aType;
            map.at(v1.lexeme).type = v2.type;
            map.at(v1.lexeme).aType = v2.aType;
            v1.type = v2.type;  // update the unknown type T

            for(string i : vec) {
                if(map.at(i).aType == sameType) {
                    map.at(i).aType = v2.aType;
                    map.at(i).type = v2.type;
                }
            }
        }

        if(v1.type == T && v2.type == T) {      // the type of v1 and v2 have to be the same, so update v2 to aType of v1
            sameType = map.at(v2.lexeme).aType;
            map.at(v2.lexeme).aType = v1.aType;
            v2.aType = v1.aType;  // update the unknown type T

            for(string i : vec) {
                if(map.at(i).aType == sameType) {
                    map.at(i).aType = v1.aType;
                }
            }
        }

        if(v1.type != v2.type) {
            type_mismatch(token.line_no, "C2");
        }

        v = v1;
    }
    else if(token.token_type == GREATER || token.token_type == LESS || token.token_type == GTEQ || token.token_type == LTEQ || token.token_type == EQUAL || token.token_type == NOTEQUAL){
        lexer.UngetToken(token);
        operatorType = parse_binary_operator();
        v1 = parse_expression();
        v2 = parse_expression();

        if((v1.type == INT || v1.type == REAL || v1.type == BOO) && v2.type == T) {
            sameType = map.at(v2.lexeme).aType;
            map.at(v2.lexeme).type = v1.type;
            map.at(v2.lexeme).aType = v1.aType;
            v2.type = v1.type;  // update the unknown type T

            // same as below, any v2.aType in the map has to be updated to v1.aType
            // don't forget to also change the type for those as well
            for(string i : vec) {
                if(map.at(i).aType == sameType) {
                    map.at(i).aType = v1.aType;
                    map.at(i).type = v1.type;
                }
            }
        }

        if(v1.type == T && (v2.type == INT || v2.type == REAL || v2.type == BOO)) {
            sameType = map.at(v1.lexeme).aType;
            map.at(v1.lexeme).type = v2.type;
            map.at(v1.lexeme).aType = v2.aType;
            v1.type = v2.type;  // update the unknown type T

            // same as below, any v1.aType in the map has to be updated to v2.aType
            // don't forget to also change the type for those as well
            for(string i : vec) {
                if(map.at(i).aType == sameType) {
                    map.at(i).aType = v2.aType;
                    map.at(i).type = v2.type;
                }
            }
        }

        if(v1.type == T && v2.type == T) {
            sameType = map.at(v2.lexeme).aType; // store the aType to compare to the rest of the map in order to update
            map.at(v2.lexeme).aType = v1.aType;
            v2.aType = v1.aType;  // update the unknown type T

            // any other variable that has the same aType as map.at(v2.lexeme) as to be updated to v1.aType in a for loop
            for(string i : vec) {
                if(map.at(i).aType == sameType) {
                    map.at(i).aType = v1.aType;
                }
            }
        }

        if(v1.type != v2.type) {
            type_mismatch(token.line_no, "C2");
        }
        v.type = operatorType;
    }
    else if(token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM || token.token_type == TR || token.token_type == FA){
        lexer.UngetToken(token);
        v = parse_primary();
    }
    else{
        syntax_error();
    }

    return v;
}

/*
 * Completed Function
 * Gets our NOT token
 */
int Parser::parse_unary_operator(){
#ifdef DEBUG
    cout << "Entered Parse Unary Operator" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type != NOT){
        syntax_error();
    }
    //Do something with the NOT

    return 0;
}

/*
 * Completed Function
 * Acts as our binary handler
 */
TokenType Parser::parse_binary_operator(){
#ifdef DEBUG
    cout << "Entered Binary Operator" << endl;
#endif
    TokenType type = NL;
    token = lexer.GetToken();
    if(token.token_type == PLUS || token.token_type == MINUS || token.token_type == MULT ||  token.token_type == DIV){
        // Do something with these Tokens
    }
    else if(token.token_type == GREATER || token.token_type == LESS || token.token_type == GTEQ || token.token_type == LTEQ || token.token_type == EQUAL || token.token_type == NOTEQUAL){
        // Do something with these Tokens

        type = BOO;
    }
    else{
        syntax_error();
    }

    return type;
}

/*
 * Completed Function
 * Acts as our primary handler
 */
Parser::Variable Parser::parse_primary(){
#ifdef DEBUG
    cout << "Entered Parse Primary" << endl;
#endif
    Variable v;

    token = lexer.GetToken();

    if(token.token_type == ID || token.token_type == NUM || token.token_type == REALNUM || token.token_type == TR || token.token_type == FA){
        // Do something with these Tokens
        if(map.find(token.lexeme) != map.end()) {
            // found
            v.lexeme = token.lexeme;        // this variable v will be returned where the lexeme and aType can be used in other functions
            v.type = map.at(token.lexeme).type;
            v.line_num = token.line_no;
            v.aType = map.at(token.lexeme).aType;
            map.at(token.lexeme).line_num = token.line_no;  // update the line_no so where it was read
        }
        else {
            // not found
            if(token.token_type == NUM) {
                v.type = INT;
            }
            else if(token.token_type == REALNUM) {
                v.type = REAL;
            }
            else if(token.token_type == TR || token.token_type == FA) {
                v.type = BOO;
            }
            else if(token.token_type == ID) { // is implicit
                Variable variable;              // create a new variable and add it to the map
                variable.lexeme = token.lexeme;
                variable.type = T;
                variable.line_num = token.line_no;
                aInc++;
                variable.aType = aInc;

                map.insert({token.lexeme, variable});
                vec.push_back(token.lexeme);

//                v.lexeme = token.lexeme;
//                v.type = map.at(token.lexeme).type;
//                v.line_num = token.line_no;
//                v.aType = map.at(token.lexeme).aType;
                v = variable;
            }
        }
    }
    else{
        syntax_error();
    }
    return v;
}

/*
 * Completed Function
 * Acts as our If Statement handler
 */
int Parser::parse_if_stmt(){
#ifdef DEBUG
    cout << "Entered Parse If Statement" << endl;
#endif
    Variable v;

    token = lexer.GetToken();
    if(token.token_type != IF){
        syntax_error();
    }
    token = lexer.GetToken();
    if(token.token_type != LPAREN){
        syntax_error();
    }
    v = parse_expression();

    if(v.type == T) {
        v.type = BOO;
    }
    for(string i : vec) {
        if(map[i].aType == v.aType) {
            map[i].type = v.type;
        }
    }

    if(v.type != BOO) {
        type_mismatch(token.line_no, "C4");
    }

    token = lexer.GetToken();
    if(token.token_type != RPAREN){
        syntax_error();
    }
    parse_body();

    return 0;
}

/*
 * Completed Function
 * Acts as our While Statement handler
 */
int Parser::parse_while_stmt(){
#ifdef DEBUG
    cout << "Entered Parse While Statement" << endl;
#endif
    Variable v;

    token = lexer.GetToken();
    if(token.token_type != WHILE){
        syntax_error();
    }
    token = lexer.GetToken();
    if(token.token_type != LPAREN){
        syntax_error();
    }
    v = parse_expression();

    if(v.type == T) {
        v.type = BOO;
    }
    for(string i : vec) {
        if(map[i].aType == v.aType) {
            map[i].type = v.type;
        }
    }

    if(v.type != BOO) {
        type_mismatch(token.line_no, "C4");
    }

    token = lexer.GetToken();
    if(token.token_type != RPAREN){
        syntax_error();
    }
    parse_body();

    return 0;
}

/*
 * Completed Function
 * Acts as out Switch Statement handler
 */
int Parser::parse_switch_stmt(){
#ifdef DEBUG
    cout << "Entered Switch Statement" << endl;
#endif
    Variable v;

    token = lexer.GetToken();
    if(token.token_type != SWITCH){
        syntax_error();
    }
    token = lexer.GetToken();
    if(token.token_type != LPAREN){
        syntax_error();
    }
    v = parse_expression(); // this is the condition

    if(v.type == T) {
        v.type = INT;
    }
    for(string i : vec) {
        if(map[i].aType == v.aType) {
            map[i].type = v.type;
        }
    }

    if(v.type != INT) {
        type_mismatch(token.line_no, "C5");
    }

    token = lexer.GetToken();
    if(token.token_type != RPAREN){
        syntax_error();
    }
    token = lexer.GetToken();
    if(token.token_type != LBRACE){
        syntax_error();
    }
    parse_case_list();
    token = lexer.GetToken();
    if(token.token_type != RBRACE){
        syntax_error();
    }

    return 0;
}

/*
 *
 */
int Parser::parse_case_list(){
#ifdef DEBUG
    cout << "Entered Parse Case List" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type == CASE){
        while(token.token_type == CASE){
            lexer.UngetToken(token);
            parse_case();
            token = lexer.GetToken();
        }
        lexer.UngetToken(token);
    }
    else{
        syntax_error();
    }

    return 0;
}

int Parser::parse_case(){
#ifdef DEBUG
    cout << "Entered Parse Case" << endl;
#endif
    token = lexer.GetToken();
    if(token.token_type != CASE){
        syntax_error();
    }
    token = lexer.GetToken();
    if(token.token_type != NUM){
        syntax_error();
    }
    // Do something with this
    token = lexer.GetToken();
    if(token.token_type != COLON){
        syntax_error();
    }
    parse_body();

    return 0;
}
int main() {

    Parser parser;
    parser.parse_program();

    cout << "lexeme\ttype\tline_num\taType\n";
    for (auto itr = parser.map.begin(); itr != parser.map.end(); itr++) {
        cout << itr->first << '\t' << itr->second.type << "\t" << itr->second.line_num << "\t\t"
        << itr->second.aType << '\n';
    }

    return(0);
};