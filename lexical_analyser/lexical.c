#include<stdio.h>
#include<string.h>
#include<ctype.h>

char keywords[32][12] = {
    "char", "int", "float", "double", "void",
    "short", "long", "signed", "unsigned",
    "auto", "static", "extern", "register", "typedef",
    "if", "else", "switch", "case", "default",
    "for", "do", "while", "goto", "continue", "break", "return",
    "struct", "union", "enum",
    "const", "sizeof", "volatile"
};
// Function to trim leading and trailing spaces
void trim(char *str) {
    int start = 0, end = strlen(str) - 1;
    while(str[start] && isspace((unsigned char)str[start])) start++; // leading spaces
    while(end >= start && isspace((unsigned char)str[end])) end--;   // trailing spaces

    // Shift trimmed string to the start
    int i, j = 0;
    for(i = start; i <= end; i++)
        str[j++] = str[i];
    str[j] = '\0';
}

int main() {
    FILE *f1,*f2,*f3;
    f1 = fopen("input.txt","r");
    f2 = fopen("output.txt","w");
    f3 = fopen("symtab.txt","w+");

    int line=1, id=0;
    char ch, next;
    

    while((ch=fgetc(f1))!=EOF) {

        // Newline handling
        if(ch == '\n') { line++; continue; }

        // Preprocessor directive
        if(ch == '#') {
            char directive[100];
            int i = 0;
            directive[i++] = ch;
            while((next=fgetc(f1))!='\n' && next!=EOF) directive[i++] = next;
            directive[i] = '\0';
        
            trim(directive);  // Trim spaces
            fprintf(f2,"%d\t%s\tPreprocessor directive\n",line,directive);
            line++;
            continue;
        }

        // Single-line or multi-line comments
        if(ch == '/') {
            next = fgetc(f1);
            if(next == '/') {
                while((ch=fgetc(f1))!='\n' && ch!=EOF);
                line++;
                continue;
            }
            if(next == '*') {
                while(1) {
                    ch = fgetc(f1);
                    if(ch==EOF) break;
                    if(ch=='*' && (next=fgetc(f1))=='/') break;
                    if(ch=='\n') line++;
                }
                continue;
            }
            else ungetc(next,f1);
        }

        // String literal
        if(ch == '"') {
            char literal[100];
            int i=0;
            literal[i++] = ch;
            while((next=fgetc(f1))!='"' && next!=EOF) {
                literal[i++] = next;
                if(next=='\n') line++;
            }
            literal[i++] = '"';
            literal[i] = '\0';
            fprintf(f2,"%d\t%s\tString literal\n",line,literal);
            continue;
        }

        // Character literal
        if(ch == '\'') {
            char literal[10];
            int i=0;
            literal[i++] = ch;
            while((next=fgetc(f1))!='\'' && next!=EOF) literal[i++] = next;
            literal[i++] = '\'';
            literal[i] = '\0';
            fprintf(f2,"%d\t%s\tChar literal\n",line,literal);
            continue;
        }

        // Numbers
        if(isdigit(ch)) {
            char number[100];
            int i=0, decimal=0;
            number[i++] = ch;
            while((next=fgetc(f1))!=EOF && (isdigit(next)||((next=='.')&&!decimal))) {
                if(next=='.') decimal=1;
                number[i++] = next;
            }
            number[i] = '\0';
            ungetc(next,f1);
            fprintf(f2,"%d\t%s\tNumber\n",line,number);
            continue;
        }

        // Identifiers or keywords
        if(isalpha(ch)||ch=='_') {
            char identifier[100];
            int i=0;
            identifier[i++] = ch;
            while((next=fgetc(f1))!=EOF && (isalnum(next)||next=='_')) identifier[i++] = next;
            identifier[i] = '\0';
            ungetc(next,f1);

            // Check keyword
            int is_keyword=0,j;
            for(j=0;j<32;j++) if(strcmp(keywords[j],identifier)==0) { is_keyword=1; break; }

            if(is_keyword) {
                fprintf(f2,"%d\t%s\tKeyword\n",line,keywords[j]);
            } else {
                // Symbol table handling
                rewind(f3);
                int ind;
                char variable[100];
                int present=0;
                while(fscanf(f3,"%d %s",&ind,variable) != EOF) {
                    if(strcmp(variable,identifier)==0) { present=1; break; }
                }
                if(present) fprintf(f2,"%d\t%s\tIdentifier %d\n",line,identifier,ind);
                else {
                    fprintf(f2,"%d\t%s\tIdentifier %d\n",line,identifier,id);
                    fprintf(f3,"%d\t%s\n",id,identifier);
                    id++;
                }
            }
            continue;
        }

        // Operators
        if(ch=='+'|| ch=='-'|| ch=='*'|| ch=='/'|| ch=='%'|| ch=='='||ch=='<'||ch=='>'||ch=='!') {
            next=fgetc(f1);
            if(ch=='+'&&next=='+') fprintf(f2,"%d\t%c%c\tIncrement operator\n",line,ch,next);
            else if(ch=='-'&&next=='-') fprintf(f2,"%d\t%c%c\tDecrement operator\n",line,ch,next);
            else if(next=='=') {
                if(ch=='!') fprintf(f2,"%d\t%c%c\tNE operator\n",line,ch,next);
                else if(ch=='<') fprintf(f2,"%d\t%c%c\tLE operator\n",line,ch,next);
                else if(ch=='>') fprintf(f2,"%d\t%c%c\tGE operator\n",line,ch,next);
                else if(ch=='=') fprintf(f2,"%d\t%c%c\tEQ operator\n",line,ch,next);
            } else {
                if(ch=='<') fprintf(f2,"%d\t%c\tLT operator\n",line,ch);
                else if(ch=='>') fprintf(f2,"%d\t%c\tGT operator\n",line,ch);
                else if(ch=='=') fprintf(f2,"%d\t%c\tAssignment operator\n",line,ch);
                else fprintf(f2,"%d\t%c\tArithmetic operator\n",line,ch);
                ungetc(next,f1);
            }
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}