grammar MetaGrammar;

rulelist : rule_ * EOF ;

rule_ : name=ID '=' alternation;

alternation : concatenation ('|' concatenation)* ;

concatenation
   : element +
   ;

repetition : '{' alternation '}' ;

group : '(' alternation ')' ;

option : '[' alternation ']' ;

element : group # GroupLabel
        | repetition # RepetitionLabel
        | option #OptionLabel
        | ID # NonTerminalLabel
        | INT # TerminalLabel
        | STRING # TerminalLabel
        ;

STRING : '"' ( ~ '"' )* '"' ;

INT: '0' .. '9'+ ;

ID : LETTER ( LETTER | DIGIT | '_' )* ;

fragment LETTER : 'a' .. 'z' | 'A' .. 'Z';

fragment DIGIT : '0' .. '9' ;

WS: ( ' ' | '\t' | '\r' | '\n' ) -> channel ( HIDDEN ) ;