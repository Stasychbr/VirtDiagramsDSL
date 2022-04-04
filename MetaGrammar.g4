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

terminal: INT | STRING ;

STRING : '"' ( ~ '"' )* '"' ;

INT: '0' .. '9'+ ;

ID : LETTER ( LETTER | DIGIT | '_' )* ;

fragment LETTER : LATIN_LETTER | CYRILLIC_LETTER ;

fragment LATIN_LETTER : 'a' .. 'z' | 'A' .. 'Z' ;

fragment CYRILLIC_LETTER : '\u0400'..'\u04FF' ;

fragment DIGIT : '0' .. '8' ;

WS: ( ' ' | '\t' | '\r' | '\n' ) -> channel ( HIDDEN ) ;
