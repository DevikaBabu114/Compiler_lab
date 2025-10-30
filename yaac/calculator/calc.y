%{
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
int yylex(void);
int yyerror(char *s);
%}
%union{
    int ival;
    float fval;
}
%token <fval> NUMBER 
%token PLUS MINUS MUL DIV LPAREN RPAREN
%type <fval> expr

%left PLUS MINUS
%left MUL DIV
%%
input:

        |input line
        ;
line:
        expr '\n' {printf("result:%.2f\n",$1);}
        ;
expr:
        NUMBER  {$$=$1;}
        | expr PLUS expr {$$=$1+$3;}
        | expr MINUS expr {$$=$1-$3;}
        | expr MUL expr {$$=$1*$3;}
        | expr DIV expr {
                            if($3!=0)
                            $$=$1/$3;
                            else
                            yyerror("cannot divide by 0");
                        }
        | LPAREN expr RPAREN {$$=$2;}

%%
int yyerror(char *s)          {fprintf(stderr,"%s\n",s);}
int main()
{
    printf("enter:");
    yyparse();
    return 0;
}