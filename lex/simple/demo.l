%{
#include<stdio.h>
%}
%%
abc     {printf("ABC");}
\n      {ECHO;}
.       {ECHO;}
%%
int yywrap()    {return 1;}
int main()      
{
    printf("enter string:");
    yylex();
    return 0;
}