%{
#include<stdio.h>
int cc=0;
int lc=1;
int wc=0;
%}
%%
[a-zA-Z0-9]+    {
                wc+=1;
                cc+=yyleng;
                }
[\t]+           {}
\n              {lc+=1;}
.               {cc+=1;}
%%
int yywrap(){return 1;}
int main()
{
    yyin=fopen("input.txt","r");
    yylex();
    printf("char count:%d\nword count:%d\nline count:%d\n",cc,wc,lc);
    return 1;
}