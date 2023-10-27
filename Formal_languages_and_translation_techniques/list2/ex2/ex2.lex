%{
#include <stdio.h>
int yywrap();
int yylex();
int yybegin(int state);
%}
%x COMMENT_STATE

COMMENT_START <!--
COMMENT_END -->
SIGN .
NEW_LINE \n

%%

<INITIAL>{COMMENT_START} {printf(""); BEGIN(COMMENT_STATE);}
<COMMENT_STATE>{COMMENT_END} {BEGIN(0);}
<COMMENT_STATE>{SIGN} {printf("");}
<COMMENT_STATE>{NEW_LINE} {printf("");}

%%


int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    if(argc > 1) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    yylex();
}