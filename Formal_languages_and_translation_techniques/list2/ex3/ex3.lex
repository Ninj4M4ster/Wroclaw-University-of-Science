%{
#include <stdio.h>
#include<string.h>
int yywrap();
int yylex();
int start_state = 0;
%}
%x STRING_STATE SINGLE_LINE_COMMENT MULTILINE_COMMENT NO_DOXYGEN


STRING_SIGN \"
CHAR_SIGN \'
SINGLE_LINE_START \/\/
COMMENT_CONTINUATION .*\\\n
ALL_TO_END .*
DOXYGEN_1 \/\/!
DOXYGEN_2 \/\*\*
DOXYGEN_3 \/\/\/
DOXYGEN_4 \/\*!
MULTILINE_START \/\*
MULTILINE_END .*\*\/

%%

<INITIAL,NO_DOXYGEN>{CHAR_SIGN} {printf("'"); BEGIN(STRING_STATE);}
<STRING_STATE>{CHAR_SIGN} {printf("'"); BEGIN(start_state);}
<INITIAL,NO_DOXYGEN>{STRING_SIGN} {printf("\""); BEGIN(STRING_STATE);}
<STRING_STATE>{STRING_SIGN} {printf("\""); BEGIN(start_state);}
<NO_DOXYGEN>{DOXYGEN_1} {printf(yytext);}
<NO_DOXYGEN>{DOXYGEN_2} {printf(yytext);}
<NO_DOXYGEN>{DOXYGEN_3} {printf(yytext);}
<NO_DOXYGEN>{DOXYGEN_4} {printf(yytext);}
<INITIAL,NO_DOXYGEN>{SINGLE_LINE_START} {printf(""); BEGIN(SINGLE_LINE_COMMENT);}
<SINGLE_LINE_COMMENT>{COMMENT_CONTINUATION} {printf("");}
<SINGLE_LINE_COMMENT>{ALL_TO_END} {printf(""); BEGIN(start_state);}
<INITIAL,NO_DOXYGEN>{MULTILINE_START} {BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>{MULTILINE_END} {printf(""); BEGIN(start_state);}
<MULTILINE_COMMENT>{ALL_TO_END} {printf("");}

%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    if(argc > 2 && strcmp(argv[2], "-nd") == 0) {
        start_state = NO_DOXYGEN;
        yyin = fopen(argv[1], "r");
    } else if(argc > 1){
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    BEGIN(start_state);
    yylex();
}