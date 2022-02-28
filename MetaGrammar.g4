grammar MetaGrammar;

rulelist : rule_ * EOF ;

rule_ : name=ID '=' chain;

chain : alternation;

alternation : element ('|' element)* ;

element : ID | INT | STRING ;


STRING : ( '%s' | '%i' )? '"' ( ~ '"' )* '"' ;

INT: '0' .. '9'+ ;

ID : LETTER ( LETTER | DIGIT | '_' )* ;

fragment LETTER : 'a' .. 'z' | 'A' .. 'Z';

fragment DIGIT : '0' .. '9' ;

WS: ( ' ' | '\t' | '\r' | '\n' ) -> channel ( HIDDEN );