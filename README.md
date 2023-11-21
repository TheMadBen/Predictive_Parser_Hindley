# Type Checking
[Full specification of this project](https://github.com/TheMadBen/Predictive_Parser_Hindley/blob/master/CSE340_Project3.pdf)<br>
Predictive Parser implementing Hindley Milner Type Checking<br>

# Supplementary Information
Hindley Milner Type Checking isn't exactly type checking like the name implies; it is a form of type inference.<br>
For example, g(x) = x + 1<br>
What can be inferred about the function g or about x?<br>
Given this set of rules:<br>
C1: The left hand side of an assignment should have the same type as its right hand side.<br>
C2: The operands of a binary operator (GTEQ, PLUS, MINUS, MULT, DIV, GREATER, LESS , LTEQ , EQUAL and NOTEQUAL) should have the same type (it can be any type).<br>
C3: The operand of a unary operator (NOT) should be of type bool.<br>
C4: Condition of if and while statements should be of type bool.<br>
C5: The expression that follows the switch keyword in switch_stmt should be of type int.<br>
The type of expression binary_operator op1 op2 is the same as the type of op1 and op2 if operator is PLUS, MINUS, MULT, or DIV. Note that op1 and op2 must have the same type due to C2.<br>
The type of expression binary_operator op1 op2 is bool if operator is GREATER, LESS, GTEQ, LTEQ, EQUAL, or NOTEQUAL.<br>
The type of unary_operator op is bool.<br>
NUM constants are of type int.<br>
REALNUM constants are of type real.<br>
true and false values are of type bool.<br><br>

We can infer that because 1 is if type INT that x is also of type INT. Since right hand expression just consists of x + 1, we say that the right hand side is of type INT. Then we can infer that the function g is of type INT.<br>
