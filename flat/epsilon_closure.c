#include<string.h>
#include<stdlib.h>
#include<stdio.h>
char tr[100][3];
typedef struct{
    char s;
    char c[100];
    int len;
}closure;
closure a[100];
int count=0;
void main()
{
    int nt,i,j,changed,k,m,n;
    printf("enter no of transitions:");
    scanf("%d",&nt);
    printf("enter transition in form A+b->B(use # for epsilon):\n");
    getchar();
    for(i=0;i<nt;i++)
    {
        scanf("%c+%c->%c",&tr[i][0],&tr[i][1],&tr[i][2]);
        getchar();
        int found=0;
        for(j=0;j<count;j++)
        {
            if (a[j].s==tr[i][0])
            {
                found=1;
                break;
            }
        }
        if(!found)
        {
            a[count].s=tr[i][0];
            a[count].len=0;
            count++;
        }
        found=0;
        for(j=0;j<count;j++)
        {
            if (a[j].s==tr[i][2])
            {
                found=1;
                break;
            }
        }
        if(!found)
        {
            a[count].s=tr[i][2];
            a[count].len=0;
            count++;
        }
    }
    for(i=0;i<count;i++)
    {
        a[i].c[0]=a[i].s;
        a[i].len++;
    }
    do
    {
        changed=0;
        for(i=0;i<count;i++)
        {
            char current=a[i].s;
            for(j=0;j<nt;j++)
            {
                if(tr[j][0]==current && tr[j][1]=='#')
                {
                    char next=tr[j][2];
                    int next_ind=-1;
                    for(k=0;k<count;k++)
                    {
                        if(a[k].s==next)
                        {
                            next_ind=k;
                            break;
                        }
                    }
                    if(next_ind!=-1)
                    {
                        for(m=0;m<a[next_ind].len;m++)
                        {
                            char to_add=a[next_ind].c[m];
                            int present=0;
                            for(n=0;n<a[i].len;n++)
                            {
                                if (a[i].c[n]==to_add)
                                {
                                    present=1;
                                    break;
                                }
                            }
                            if(!present)
                            {
                                int ind=a[i].len;
                                a[i].c[ind]=to_add;
                                a[i].len++;
                                changed=1;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
    for(i=0;i<count;i++)
    {
        printf("\nEPSILON CLOSURE(%c):",a[i].s);
        for(j=0;j<a[i].len;j++)
            printf("%c ",a[i].c[j]);
    }
    printf("\n");

}