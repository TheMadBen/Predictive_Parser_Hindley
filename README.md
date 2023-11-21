# Type Checking
[Full specification of this project](https://github.com/TheMadBen/Predictive_Parser_Hindley/blob/master/CSE340_Project3.pdf)<br>
Predictive Parser implementing Hindley Milner Type Checking<br>
This program will infer whether a type is int, real, or bool.<br>

# Supplementary Information
Hindley Milner Type Checking isn't exactly type checking like the name implies; it is a form of type inference.<br>
For example, g(x) = x + 1<br>
What can be inferred about the function g or about x?<br>
Given this set of rules:<br><br>
C1: The left hand side of an assignment should have the same type as its right hand side.<br>
C2: The operands of a binary operator (GTEQ, PLUS, MINUS, MULT, DIV, GREATER, LESS , LTEQ , EQUAL and NOTEQUAL) should have the same type (it can be any type).<br>
C3: The operand of a unary operator (NOT) should be of type bool.<br>
C4: Condition of if and while statements should be of type bool.<br>
C5: The expression that follows the switch keyword in switch_stmt should be of type int.<br><br>
The type of expression binary_operator op1 op2 is the same as the type of op1 and op2 if operator is PLUS, MINUS, MULT, or DIV. Note that op1 and op2 must have the same type due to C2.<br>
The type of expression binary_operator op1 op2 is bool if operator is GREATER, LESS, GTEQ, LTEQ, EQUAL, or NOTEQUAL.<br>
The type of unary_operator op is bool.<br>
NUM constants are of type int.<br>
REALNUM constants are of type real.<br>
true and false values are of type bool.<br><br>

We can infer that because 1 is if type INT that x is also of type INT. Since right hand expression just consists of x + 1, we say that the right hand side is of type INT. Then we can infer that the function g is of type INT.<br><br>

There are the lexer files that recognizes the following tokens:<br><br>
INT = “int”<br>
REAL = “real”<br>
BOO = “bool”<br>
TRUE = “true”<br>
FALSE = “false”<br>
IF = “if”<br>
WHILE = “while”<br>
SWITCH = “switch”<br>
CASE = “case”<br>
NOT = “!”<br>
PLUS = “+”<br>
MINUS = “-”<br>
MULT = “*”<br>
DIV = “/”<br>
GREATER = “>”<br>
LESS = “<”<br>
GTEQ = “>=”<br>
LTEQ = “<=”<br>
NOTEQUAL = “<>”<br>
LPAREN = “(”<br>
RPAREN = “)”<br>
NUM = (pdigit digit*) + 0<br>
REALNUM = NUM “.” digit digit*<br>
PUBLIC = “public”<br>
PRIVATE = “private”<br>
EQUAL = “=”<br>
COLON = “:”<br>
COMMA = “,”<br>
SEMICOLON = “;”<br>
LBRACE = “{”<br>
RBRACE = “}”<br>
ID = letter (letter + digit)*<br><br>

Our input/language adheres to these rules:<br><br>
program -> global_vars body<br>
global_vars -> ε<br>
global_vars -> var_decl_list<br>
var_decl_list -> var_decl<br>
var_decl_list -> var_decl var_decl_list<br>
var_decl -> var_list COLON type_name SEMICOLON<br>
var_list -> ID<br>
var_list -> ID COMMA var_list<br>
type_name -> INT<br>
type_name -> REAL<br>
type_name -> BOOL<br>
body -> LBRACE stmt_list RBRACE<br>
stmt_list -> stmt<br>
stmt_list -> stmt stmt_list<br>
stmt -> assignment_stmt<br>
stmt -> if_stmt<br>
stmt -> while_stmt<br>
stmt -> switch_stmt<br>
assignment_stmt -> ID EQUAL expression SEMICOLON<br>
expression -> primary<br>
expression -> binary_operator expression expression<br>
expression -> unary_operator expression<br>
unary_operator -> NOT<br>
binary_operator -> PLUS | MINUS | MULT | DIV<br>
binary_operator -> GREATER | LESS | GTEQ | LTEQ | EQUAL | NOTEQUAL<br>
primary -> ID<br>
primary -> NUM<br>
primary -> REALNUM<br>
primary -> TRUE<br>
primary -> FALSE<br>
if_stmt -> IF LPAREN expression RPAREN body<br>
while_stmt -> WHILE LPAREN expression RPAREN body<br>
switch_stmt -> SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE<br>
case_list -> case<br>
case_list -> case case_list<br>
case -> CASE NUM COLON body<br>


