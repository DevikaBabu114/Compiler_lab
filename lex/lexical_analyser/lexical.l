%{
#include<stdio.h>
#include<string.h>
int lc=1;
%}
numbers [0-9]+(\.[0-9]+)?
strliteral \"[^\"]*\"
key    if|else|void|int|float|for|do|while
identifier [a-zA-Z_][a-zA-Z0-9_]*
relop   (<=|>=|==|!=|<|>)
%%
{numbers}      {printf("%d\t%s\tNumber\n",lc,yytext);}
{key}           {printf("%d\t%s\tKeyword\n",lc,yytext);}
{strliteral}   {printf("%d\t%s\tString literal\n",lc,yytext);}
{identifier}   {printf("%d\t%s\tIdentifier\n",lc,yytext);}
{relop}         {
                    printf("%d\t%s\tRelop-",lc,yytext);
                    if(strcmp(yytext,"<")==0)
                        printf("LT\n");
                    else if(strcmp(yytext,"<=")==0)
                        printf("LE\n");
                    else if(strcmp(yytext,">")==0)
                        printf("GT\n");
                    else if(strcmp(yytext,">=")==0)
                        printf("GE\n");
                    else if(strcmp(yytext,"==")==0)
                        printf("EQ\n");
                    else if(strcmp(yytext,"!=")==0)
                        printf("NE\n");
                }
[+\-*/%]       {printf("%d\t%s\tArithmetic op\n",lc,yytext);}
"="             {printf("%d\t%s\tAssignment op\n",lc,yytext);}
[\{\}\(\);]       {printf("%d\t%s\tDelimiter\n",lc,yytext);}
[\t]+              {}
\n              {lc++;}
.               {}
%%
int yywrap()    {return 1;}
int main()
{
    yyin=fopen("input.txt","r");
    yylex();
    return 0;
}