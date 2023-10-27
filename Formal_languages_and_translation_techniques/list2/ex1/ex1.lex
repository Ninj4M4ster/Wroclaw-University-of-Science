%{
#include <stdio.h>
int yywrap();
int yylex();
int lines_count = 0;
int words_count = 0;
%}

EMPTY_LINE ^[[:blank:]]*\n
BLANK_B ^[[:blank:]]+
BLANK_E [[:blank:]]+$  
BLANK_M [[:blank:]]+
WORD [^[:blank:]\n]+

%%

{EMPTY_LINE} printf("");
{BLANK_B} printf("");
{BLANK_M} printf(" ");
{BLANK_E} printf("");
\n {printf("\n");lines_count++;}
{WORD}  {printf(yytext); words_count++;}
%%


int yywrap() {
    printf("Lines count: %d\nWords count: %d\n", lines_count, words_count);
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