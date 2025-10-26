/*** 
            OPERATOR PRECEDENCE PARSER FOR GRAMMER
            E->E+E|E-E|E*E|E/E|E^E|(E)|id
*/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
char *corrected_ip;
char stack[100];
int top=-1,ip=0,length;
char handles[7][4]={"E+E","E-E","E*E","E/E","E^E",")E(","i"};
char lasthandle[4];
char precedence[9][9]={
    /*         +   -   *   /   ^   i   (   )   $    */
    /* + */   '>','>','<','<','<','<','<','>','>',
    /* - */   '>','>','<','<','<','<','<','>','>',
    /* * */   '>','>','>','>','<','<','<','>','>',
    /* / */   '>','>','>','>','<','<','<','>','>',
    /* ^ */   '>','>','>','>','<','<','<','>','>',
    /* i */   '>','>','>','>','>','e','e','>','>',
    /* ( */   '<','<','<','<','<','<','<','>','e',
    /* ) */   '>','>','>','>','>','e','e','>','>',
    /* $ */   '<','<','<','<','<','<','<','<','<'
            
};
int get_index(char ch);
void shift();
int reduce();
void correct(char input[]);
void disp_stack();
void disp_input();
int main()
{
   char input[100];
   printf("enter string to parse:");
   scanf("%s",input);
   correct(input);
   stack[++top]='$';
   stack[top+1]='\0';
   length=strlen(corrected_ip);
   printf("STACK\t\tINPUT\tACTION\n");
   disp_stack();
   printf("\t\t");
   disp_input();
   printf("\n");
   while(ip<length)
   {
       shift();
       disp_stack();
       printf("\t\t");
       disp_input();
       printf("\tShift\n");
       if(precedence[get_index(stack[top])][get_index(corrected_ip[ip])]=='>')
       {
            while (reduce())
            {
                disp_stack();
                printf("\t\t");
                disp_input();
                printf("\tReduce:E->%s\n",lasthandle);
            }
       }
   }
   if(strcmp(stack,"$E$")==0)
        printf("%s accepted\n",corrected_ip);
   else
        printf("%s rejected\n",corrected_ip);
}
int get_index(char ch)
{
    switch(ch)
    {
        case '+':return 0;
        case '-':return 1;
        case '*':return 2;
        case '/':return 3;
        case '^':return 4;
        case 'i':return 5;
        case '(':return 6;
        case ')':return 7;
        case '$':return 8;
        default:return -1;
    }
}
void shift()
{
    stack[++top]=*(corrected_ip+ip);
    ip+=1;
    stack[top+1]='\0';
}
int reduce()
{
    int j,k,found=0,handle_len;
    for(j=0;j<7;j++)
    {
        handle_len=strlen(handles[j]);
        if(stack[top]==handles[j][0] && top+1>=handle_len)
        {
            found=1;
            for(k=0;k<handle_len;k++)
            {
                if (stack[top-k]!=handles[j][k])
                {
                    found=0;
                    break;
                }
            }
            if(found)
            {
                stack[top-k+1]='E';
                top=top-k+1;
                stack[top+1]='\0';
                strcpy(lasthandle,handles[j]);
                return 1;
            }   
        }
    }
    return 0;
}
void disp_stack()
{
    for(int j=0;j<=top;j++)
        printf("%c",stack[j]);
}
void disp_input()
{
    for(int j=ip;j<length;j++)
        printf("%c",*(corrected_ip+j));
}
void correct(char *input)
{
    corrected_ip=(char *)malloc(sizeof(char)*100);
    int j=0,k=0;
    for(j=0;j<strlen(input);)
    {
        if(isalnum(input[j]))
        {
            while (j<strlen(input) && isalnum(input[j]))
                j++;
            corrected_ip[k]='i';
            k++;
        }
        else if( input[j]=='+' || input[j]=='-'|| input[j]=='*'|| input[j]=='/'|| input[j]=='^'||  input[j]=='('|| input[j]==')'|| input[j]=='$')
            corrected_ip[k++]=input[j++];
        else
            j++;
    }
    corrected_ip[k++]='$';
    corrected_ip[k]='\0';
}