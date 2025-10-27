#include <stdio.h>
#include<string.h>
typedef struct{
    char op,op1[10],op2[10],res[10];
}Instruction;

void eliminate_common_expression(Instruction instr[],int n);
int operands_redefined(Instruction instr[],int i,int j);
int is_common_expression(Instruction *i1,Instruction *i2);
void print_result(Instruction instr[],int n);

int main()
{
    FILE *f1;
    int i=0;
    Instruction instr[100];
    
    f1=fopen("quad.txt","r");
    
    while(fscanf(f1," %c %s %s %s",&instr[i].op,instr[i].op1,instr[i].op2,instr[i].res)==4)
    {
        i++;
    }
    
    eliminate_common_expression(instr,i);
    print_result(instr,i);
    return 0;
}
int is_common_expression(Instruction *i1,Instruction *i2)
{
    if (i1->op!=i2->op)
        return 0;
    else if(i1->op=='+' || i1->op=='*')
        return ( (strcmp(i1->op1,i2->op1)==0 && strcmp(i1->op2,i2->op2)==0)
              || (strcmp(i1->op1,i2->op2)==0 && strcmp(i1->op2,i2->op1)==0) );
    else
        return(strcmp(i1->op1,i2->op1)==0 && strcmp(i1->op2,i2->op2)==0);
}
int operands_redefined(Instruction instr[],int i,int j)
{
    for(int k=i+1;k<j;k++)
    {
        if (instr[k].op==0)
            continue;
        char *kill_var;
        if (instr[k].op=='=')
            kill_var=instr[k].op1;
        else
            kill_var=instr[k].res;
        if (strcmp(instr[i].op1,kill_var)==0 || strcmp(instr[i].op2,kill_var)==0 
        || strcmp(instr[j].op1,kill_var)==0 || strcmp(instr[j].op2,kill_var)==0)
            return 1;
    }
    return 0;
}
void eliminate_common_expression(Instruction instr[],int n)
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        if(instr[i].op==0)
            continue;
        for(j=i+1;j<n;j++)
        {
            if(instr[j].op==0)
                continue;
            if (operands_redefined(instr,i,j))
                continue;
            if (is_common_expression(&instr[i],&instr[j]))
            {
                char old_res[10];
                strcpy(old_res,instr[j].res);
                for(k=j+1;k<n;k++)
                {
                    if(strcmp(old_res,instr[k].op1)==0)
                        strcpy(instr[k].op1,instr[i].res);
                    if(strcmp(old_res,instr[k].op2)==0)
                        strcpy(instr[k].op2,instr[i].res);
                }
                instr[j].op=0;
            }
        }
    }
}
void print_result(Instruction instr[],int n)
{
    for(int i=0;i<n;i++)
    {
         if(instr[i].op!=0)
         {
             printf("%c %s %s %s\n",instr[i].op,instr[i].op1,instr[i].op2,instr[i].res);
         }
    }
}