A simple C++ program to simulate parts of a compiler for RPAL - The Right Reference Pedagogic Algorithm Language. This program takes in a RPAL program as input and performs lexical anlysis
and passes the tokens to syntax analyser, which will give an abstract syntax tree as the output. The AST is later parsed and standardized into a standardized tree.

To run parser type p1 -ast /src/to/program


To get the ST representation, type p1 -st /src/to/program



LEXICAL GRAMMAR FOR RPAL

Identifier -> Letter (Letter | Digit | ’_’)* => ’<IDENTIFIER>’;
Integer -> Digit+ => ’<INTEGER>’;
Operator -> Operator_symbol+ => ’<OPERATOR>’;
String -> ’’’’
( ’\’ ’t’ | ’\’ ’n’ | ’\’ ’\’ | ’\’ ’’’’
| ’(’ | ’)’ | ’;’ | ’,’
|’’
| Letter | Digit | Operator_symbol
)* ’’’’ => ’<STRING>’;
Spaces -> ( ’ ’ | ht | Eol )+ => ’<DELETE>’;
Comment -> ’//’
( ’’’’ | ’(’ | ’)’ | ’;’ | ’,’ | ’\’ | ’ ’
| ht | Letter | Digit | Operator_symbol
)* Eol => ’<DELETE>’;
Punction -> ’(’ => ’(’
-> ’)’ => ’)’
-> ’;’ => ’;’
-> ’,’ => ’,’;
Letter -> ’A’..’Z’ | ’a’..’z’;
Digit -> ’0’..’9’;
Operator_symbol
-> ’+’ | ’-’ | ’*’ | ’<’ | ’>’ | ’&’ | ’.’
| ’@’ | ’/’ | ’:’ | ’=’ | ’˜’ | ’|’ | ’$’
| ’!’ | ’#’ | ’%’ | ’ˆ’ | ’_’ | ’[’ | ’]’
| ’{’ | ’}’ | ’"’ | ’‘’ | ’?’;


RPAL parsing grammar


# Expressions ############################################
E -> ’let’ D ’in’ E => ’let’
-> ’fn’ Vb+ ’.’ E => ’lambda’
-> Ew;
Ew -> T ’where’ Dr => ’where’
-> T;
# Tuple Expressions ######################################
T -> Ta ( ’,’ Ta )+ => ’tau’
-> Ta ;
Ta -> Ta ’aug’ Tc => ’aug’
-> Tc ;
Tc -> B ’->’ Tc ’|’ Tc => ’->’
-> B ;
# Boolean Expressions ####################################
B ->B’or’ Bt => ’or’
-> Bt ;
Bt -> Bt ’&’ Bs => ’&’
-> Bs ;
Bs -> ’not’ Bp => ’not’
-> Bp ;
Bp -> A (’gr’ | ’>’ ) A => ’gr’
-> A (’ge’ | ’>=’) A => ’ge’
-> A (’ls’ | ’<’ ) A => ’ls’
-> A (’le’ | ’<=’) A => ’le’
-> A ’eq’ A => ’eq’
-> A ’ne’ A => ’ne’
-> A ;
# Arithmetic Expressions #################################
A ->A’+’ At => ’+’
-> A ’-’ At => ’-’
-> ’+’ At
-> ’-’ At => ’neg’
-> At ;
At -> At ’*’ Af => ’*’
-> At ’/’ Af => ’/’
-> Af ;
Af -> Ap ’**’ Af => ’**’
-> Ap ;
Ap -> Ap ’@’ ’<IDENTIFIER>’ R => ’@’
-> R ;
# Rators And Rands #######################################
R ->RRn => ’gamma’
-> Rn ;
Rn -> ’<IDENTIFIER>’
-> ’<INTEGER>’
-> ’<STRING>’
-> ’true’ => ’true’
-> ’false’ => ’false’
-> ’nil’ => ’nil’
-> ’(’ E ’)’
-> ’dummy’ => ’dummy’ ;
# Definitions ############################################
D -> Da ’within’ D => ’within’
-> Da ;
Da -> Dr ( ’and’ Dr )+ => ’and’
-> Dr ;
Dr -> ’rec’ Db => ’rec’
-> Db ;
Db -> Vl ’=’ E => ’=’
-> ’<IDENTIFIER>’ Vb+ ’=’ E => ’fcn_form’
-> ’(’ D ’)’ ;
# Variables ##############################################
Vb -> ’<IDENTIFIER>’
-> ’(’ Vl ’)’
-> ’(’ ’)’ => ’()’;
Vl -> ’<IDENTIFIER>’ list ’,’ => ’,’?;



