%{
#include "y.tab.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
%}
%%
[0-9]+(\.[0-9]+)?       {
                            yylval.fval=atof(yytext);
                            return NUMBER;
                        }
"+"                       return PLUS;
"-"                       return MINUS;
"*"                       return MUL;
"/"                       return DIV;
"("                       return LPAREN;
")"                       return RPAREN;
[ \t]+                  {}
\n                      return '\n';
.                       printf("invalid character %s",yytext);
%%
int yywrap()            {return 1;}