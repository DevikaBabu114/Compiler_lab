/*** 
            RECURSIVE DESCENT PARSER FOR GRAMMER
            E->E+E|E-E|E*E|E/E|E^E|(E)|i
            Conveted grammer after eliminating ambiguity,left recurion
            performed left factoring
            E  → T E'
            E' → +T E' | -T E' | ε
            T  → G T'
            T' → *G T' | /G T' | ε
            G  → F G'
            G' → ^G | ε
            F  → i | (E)

*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
int err=0,ip=0;
char input[100];
void E();
void Eprime();
void T();
void Tprime();
void G();
void Gprime();
void F();
int main()
{
   printf("enter string to parse:");
   scanf("%s",input);
   E();
   if (ip==strlen(input)&&err==0)
        printf("%s successfully parsed\n",input);
   else
        printf("%s rejected\n",input);
}
void E()
{
    T();
    Eprime();
}
void Eprime()
{
    if (input[ip]=='+'||input[ip]=='-')
    {
        ip+=1;
        T();
        Eprime();
    }
}
void T()
{
    G();
    Tprime();
}
void Tprime()
{
    if (input[ip]=='*'||input[ip]=='/')
    {
        ip+=1;
        G();
        Tprime();
    }
}
void G()
{
    F();
    Gprime();
}
void Gprime()
{
    if (input[ip]=='^')
    {
        ip+=1;
        G();
    }
}
void F()
{
    if(input[ip]=='i') 
        ip+=1;
    else if(input[ip]=='(')
    {
        ip+=1;
        E();
        if (input[ip]==')')
        {
            ip+=1;
        }
        else
        {
            printf("missing paranthesis\n%s rejected\n",input);
            err=1;
            exit(1);
        }

    }
    else
    {
        printf("invalid format\n%s rejected\n",input);
        err=1;
        exit(1);
    }
}