%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int yywrap();
%}

%%

[ \t]+      ;
[0-9]+      { yylval.llival = atoll(yytext); return INTEGER;} 
[-+*/()^\n\\#]   { return *yytext;} 
.           { yyerror();}


%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    if(argc > 1){
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    int result_code = yyparse();
    // fclose(yyin);
    return result_code;
    }

