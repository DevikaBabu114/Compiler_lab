/*
FIND FIRST AND FOLLOW OF A GRAMMER
Test case:
E->E+T
E->T
T->T*F
T->F
F->i
F->(E)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SYM 50
#define MAX_RHS 20
#define MAX_PROD 50
#define MAX_LEN 100

char NT[MAX_SYM];
int NT_count=0;

int c_first[MAX_SYM],c_follow[MAX_SYM];
char first[MAX_SYM][MAX_LEN],follow[MAX_SYM][MAX_LEN];

typedef struct
{
	char lhs;
	char rhs[MAX_RHS][MAX_LEN];
	int rhs_count;
} Production;
Production prods[MAX_PROD];
int prod_count=0;

int is_NT(char ch);
int index_NT(char ch);
int contains(char *set,int count,char ch);
void add_to_set(char *set,int *count,char ch);
void add_to_NT(char ch);
int find_prod(char ch);
void compute_first();
void compute_follow();

int main()
{
	int i,n,j;
	char lhs,rhs[MAX_LEN],line[MAX_LEN+3];
	printf("no of productions:");
	scanf("%d",&n);
	printf("enter productions in form A->ab(use # for epsilon):\n");
	for(i=0; i<n; i++)
	{
		scanf("%s",line);
		lhs=line[0];
		if(line[1]!='-'|| line[2]!='>')
		{
			i--;
			printf("invalid format");
			continue;
		}
		strcpy(rhs,line+3);
		int lhs_ind=find_prod(lhs);
		int rhs_ind=prods[lhs_ind].rhs_count++;
		strcpy(prods[lhs_ind].rhs[rhs_ind],rhs);
		add_to_NT(lhs);
	}
	printf("entered productions:\n");
	for(i=0; i<prod_count; i++)
	{
		printf("%c->",prods[i].lhs);
		for(j=0; j<prods[i].rhs_count; j++)
		{
			printf("%s",prods[i].rhs[j]);
			if (j<prods[i].rhs_count-1)
				printf("|");
		}
		printf("\n");
	}
	for(i=0; i<NT_count; i++)
	{
		c_first[i]=0;
		c_follow[i]=0;
	}
	compute_first();
	add_to_set(follow[0],&c_follow[0],'$');
	compute_follow();
    printf("FIRST\n");
	for(i=0; i<NT_count; i++)
	{
		printf("FIRST(%c):",NT[i]);
		for(j=0; j<c_first[i]; j++)
		{
			printf("%c ",first[i][j]);
		}
		printf("\n");
	}
	printf("FOLLOW\n");
	for(i=0; i<NT_count; i++)
	{
		printf("FOLLOW(%c):",NT[i]);
		for(j=0; j<c_follow[i]; j++)
		{
			printf("%c ",follow[i][j]);
		}
		printf("\n");
	}

}

int is_NT(char ch)
{
	return (ch<='Z'&&ch>='A');
}
int index_NT(char ch)
{
	for(int i=0; i<NT_count; i++)
	{
		if(NT[i]==ch)
			return i;
	}
	return -1;
}
int contains(char *set,int count,char ch)
{
	for(int i=0; i<count; i++)
	{
		if(set[i]==ch)
			return 1;
	}
	return 0;
}
void add_to_set(char *set,int *count,char ch)
{
    if (!contains(set, *count, ch))
	    set[(*count)++]=ch;
}
void add_to_NT(char ch)
{
	if(index_NT(ch)==-1)
		NT[NT_count++]=ch;
}
int find_prod(char ch)
{
	for(int i=0; i<prod_count; i++)
	{
		if (prods[i].lhs==ch)
			return i;
	}
	prods[prod_count].lhs=ch;
	prods[prod_count].rhs_count=0;
	return prod_count++;
}
void compute_first()
{
	int i,j,k,x,changed;
	do {
		changed=0;
		for(i=0; i<prod_count; i++)
		{
			int i_ind=index_NT(prods[i].lhs);
			for(j=0; j<prods[i].rhs_count; j++)
			{
				char *rhs=prods[i].rhs[j];
				int k=0,eps_prev=1;
				while(rhs[k]&&eps_prev)
				{
					char ch=rhs[k];
					eps_prev=0;
					if(!is_NT(ch))
					{
						if(!contains(first[i_ind],c_first[i_ind],ch))
						{
							add_to_set(first[i_ind],&c_first[i_ind],ch);
							changed=1;
						}
						break;
					}
					else
					{
						int ch_ind=index_NT(ch);
						for(x=0; x<c_first[ch_ind]; x++)
						{
							char f=first[ch_ind][x];
							if(f!='#'&&!contains(first[i_ind],c_first[i_ind],f))
							{
								add_to_set(first[i_ind],&c_first[i_ind],f);
								changed=1;
							}
						}
						if(contains(first[ch_ind],c_first[ch_ind],'#'))
						{
							eps_prev=1;
						}

					}
					k++;
				}
				if(eps_prev==1)
				{
					if(!contains(first[i_ind],c_first[i_ind],'#'))
					{
						add_to_set(first[i_ind],&c_first[i_ind],'#');
						changed=1;
					}
				}
			}
		}
	} while(changed==1);
}
void compute_follow()
{
	int i,j,k,l,x,changed;
	do {
		changed=0;
		for(i=0; i<prod_count; i++)
		{
			char a=prods[i].lhs;
			int a_ind=index_NT(a);
			for(j=0;j<prods[i].rhs_count;j++)
			{
			    char *rhs=prods[i].rhs[j];
			    int length=strlen(rhs);
			    for(k=0;k<length;k++)
			    {
			        char ch=rhs[k];
			        if(!is_NT(ch))
			            continue;
			        int ch_ind=index_NT(ch);
			        l=1;
			        int eps_next=1;
			        while(k+l<length && eps_next)
			        {
			            eps_next=0;
			            char next=rhs[k+l];
			            if(!is_NT(next))
			            {
			                if(!contains(follow[ch_ind],c_follow[ch_ind],next))
			                {
			                    add_to_set(follow[ch_ind],&c_follow[ch_ind],next);
			                    changed=1;
			                }
			                break;
			            }
			            else
			            {
			                int next_ind=index_NT(next);
    						for(x=0; x<c_first[next_ind]; x++)
    						{
    							char f=first[next_ind][x];
    							if(f!='#'&&!contains(follow[ch_ind],c_follow[ch_ind],f))
    							{
    								add_to_set(follow[ch_ind],&c_follow[ch_ind],f);
    								changed=1;
    							}
    						}
    						if(contains(first[next_ind],c_first[next_ind],'#'))
    						{
    							eps_next=1;
    						}
			            }
			            l++;
			        }
			        if(k+l==length && eps_next)
			        {
			            for(x=0; x<c_follow[a_ind]; x++)
    						{
    							char f=follow[a_ind][x];
    							if(!contains(follow[ch_ind],c_follow[ch_ind],f))
    							{
    								add_to_set(follow[ch_ind],&c_follow[ch_ind],f);
    								changed=1;
    							}
    						}
			        }
			    }
			}
		}
	} while(changed==1);
}