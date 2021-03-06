grammar MetaGrammar;

ruleList : singleRule * EOF ;

singleRule : name=ID '=' alternation ';' ;

alternation : concatenation ('|' concatenation)* ;

concatenation
   : element +
   ;

repetition : '{' alternation ('*' alternation) ? '}' ;

group : '(' alternation ')' ;

option : '[' alternation ']' ;

element : group
		| repetition
		| option
		| nonTerminal
		| terminal
        ;

nonTerminal: ID ;

terminal: INT | STRING;

STRING : '"' ( ~[\\"] | ESCAPE_SEQUENCE )* '"' ;

INT: '-'? DIGIT+ ;

ID : LETTER ( LETTER | DIGIT | '_' )*;

fragment LETTER : LATIN_LETTER | CYRILLIC_LETTER ;

fragment ESCAPE_SEQUENCE : '\\' [btnfr"'\\] ;

fragment LATIN_LETTER : 'a' .. 'z' | 'A' .. 'Z' ;

fragment CYRILLIC_LETTER : '\u0400'..'\u04FF' ;

fragment DIGIT : '0' .. '9' ;

WS: ( ' ' | '\t' | '\r' | '\n' ) -> channel ( HIDDEN ) ;
