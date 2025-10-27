/* 
        Intermediate code generation- 3 ADDRESS CODE,QUADRAPLE,TRIPLE
        User inputs set of arthmetic expressions
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char input[100],post[100],s[100],q[100];
int top=-1,front=-1;

void postfix();
int precedence(char ch);
void print_file(char *filename);

int main()
{
   FILE *fp2,*fp3,*fp4;
   char ind='1';
   int n,k=0;
   fp2=fopen("3addr.txt","w");
   fp3=fopen("quad.txt","w");
   fp4=fopen("triple.txt","w");
   fprintf(fp2,"RES\t=\tOP1\tOP\tOP2\n");
   fprintf(fp3,"OP\tOP1\tOP2\tRES\n");
   fprintf(fp4,"IN\tOP\tOP1\tOP2\n");
   printf("no of expresiion:");
   scanf("%d",&n);
   while(k<n)
   {
       printf("enter expression:");
       scanf("%s",input);
       postfix();
       printf("infix:%s\npostfix:%s\n",input,post);
       int i=0;
       while(post[i]!='\0')
       {
           if (precedence(post[i])>=0)
           {
               char a=q[front--];
               char b=q[front--];
               if(isdigit(a)&&isdigit(b))
               {
                   fprintf(fp2,"t%c\t=\tt%c\t%c\tt%c\n",ind,b,post[i],a);
                   fprintf(fp3,"%c\tt%c\tt%c\tt%c\n",post[i],b,a,ind);
               }
               else if(isdigit(a))
               {
                   fprintf(fp2,"t%c\t=\t%c\t%c\tt%c\n",ind,b,post[i],a);
                   fprintf(fp3,"%c\t%c\tt%c\tt%c\n",post[i],b,a,ind);
               }
               else if(isdigit(b))
               {
                   fprintf(fp2,"t%c\t=\tt%c\t%c\t%c\n",ind,b,post[i],a);
                   fprintf(fp3,"%c\tt%c\t%c\tt%c\n",post[i],b,a,ind);
               }
               else
               {
                   fprintf(fp2,"t%c\t=\t%c\t%c\t%c\n",ind,b,post[i],a);
                   fprintf(fp3,"%c\t%c\t%c\tt%c\n",post[i],b,a,ind);
               }
               fprintf(fp4,"%c\t%c\t%c\t%c\n",ind,post[i],b,a);
               q[++front]=ind;
               ind++;
           }
           else
           {
               q[++front]=post[i];
           }
           i++;
       }
       k++;
   }
   fclose(fp2);
   fclose(fp3);
   fclose(fp4);
    
    printf("3 ADDRESS CODE\n");
    print_file("3addr.txt");
    printf("QUADRAPLE\n");
    print_file("quad.txt");
    printf("TRIPLE\n");
    print_file("triple.txt");
}

int precedence(char ch)
{
    if(ch=='=')
        return 0;
    else if(ch=='+' || ch =='-')
        return 1;
    else if(ch=='*' || ch =='/')
        return 2;
    else if(ch=='^')
        return 3;
    else
        return -1;
}

void postfix()
{
    int i=0,p=0;
    while(input[i]!='\0')
    {
        if (input[i]=='(')
            s[++top]=input[i];
        else if(isalnum(input[i]))
            post[p++]=input[i];
        else if(precedence(input[i])>=0)
        {
            while(top>=0 && precedence(s[top])>=precedence(input[i]))
                post[p++]=s[top--];
            s[++top]=input[i];
        }
        else if(input[i]==')')
        {
            while(s[top]!='(')
                post[p++]=s[top--];
            top--;
        }
        i++;
    }
    while(top!=-1)
        post[p++]=s[top--];
    post[p]='\0';
}
void print_file(char *filename)
{
    FILE *f1;
    char line[100];
    f1=fopen(filename,"r");
    while(fgets(line,sizeof(line),f1))
        printf("%s\n",line);
    fclose(f1);
}