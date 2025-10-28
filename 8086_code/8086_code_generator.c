#include <stdio.h>
#include<string.h>
typedef struct
{
    char op,op1[10],op2[10],res[10];
}Quadraple;
int main()
{
    FILE *f1;
    int i=0;
    Quadraple quad[100];
    
    f1=fopen("quad.txt","r");
    
    while(fscanf(f1," %c %s %s %s",&quad[i].op,quad[i].op1,quad[i].op2,quad[i].res)==4)
    {
        char opr[10];
        switch(quad[i].op)
        {
            case '+':strcpy(opr,"ADD");
                     break;
            case '-':strcpy(opr,"SUB");
                     break;
            case '*':strcpy(opr,"MUL");
                     break;
            case '/':strcpy(opr,"DIV");
                     break;
            default:strcpy(opr,"???");
                     break;
        }
        char *op1,*op2,*res;
        op1=quad[i].op1;
        op2=quad[i].op2;
        res=quad[i].res;
        
        if(strlen(op1)==2)
        {
            if(op1[1]=='1')
                printf("MOV AX,CH\n");
            else if(op1[1]=='2')
                printf("MOV AX,CL\n");
            else if(op1[1]=='3')
                printf("MOV AX,DH\n");
             else if(op1[1]=='4')
                printf("MOV AX,DL\n");
        }
        else
            printf("MOV AX,[%s]\n",op1);
            
        if(strlen(op2)==2)
        {
            if(op2[1]=='1')
                printf("MOV BX,CH\n");
            else if(op2[1]=='2')
                printf("MOV BX,CL\n");
            else if(op2[1]=='3')
                printf("MOV BX,DH\n");
             else if(op2[1]=='4')
                printf("MOV BX,DL\n");
        }
        else
            printf("MOV BX,[%s]\n",op2);  
            
        if(quad[i].op=='+' || quad[i].op=='-')
            printf("%s AX,BX\n",opr);
        else
            printf("%s BX\n",opr);
        
        if(res[1]=='1')
            printf("MOV CH,AX\n");
        else if(res[1]=='2')
            printf("MOV CL,AX\n");
        else if(res[1]=='3')
            printf("MOV DH,AX\n");
        else if(res[1]=='4')
            printf("MOV DL,AX\n");
        
        i++;
    }
    return 0;
}