/* Project Title: Infix to Postfix Expression Converter and converts into a standard notation.
   Input: A+B*C
   Output1: ABC*+
   Output2: (A+(B*C))  */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 100

char stack[MAX];
int top=-1;
char Stack[100][100];
int top1=-1;

char* infix_to_postfix(char*);
void eval_postfix(char*);
int prec(char);
void Prec(char *);
void push(char *);
char *pop(void);


int main()
{
        char exp[MAX],*p;
        printf("Enter the expression:");
        scanf("%s",exp);
        p=infix_to_postfix(exp);
        eval_postfix(p);
        return 0;
}

int prec(char c)
{
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

char* infix_to_postfix(char* s)
{
    char result[100];
    int j= 0,i=0;
    while(s[i])
    {
        char c = s[i];
        if (c == '(')
        {
            stack[++top] = c;
        }
        else if(c=='+'||c=='-'||c=='*'||c=='/')
        {
                while (top >= 0 && (prec(s[i]) < prec(stack[top]) ||
                                       prec(s[i]) == prec(stack[top]) && stack[top] != '('))
                {
                        result[j++] = stack[top--];
                }
                stack[++top] = c;
        }
        else if (c == ')')
        {
            while (top >= 0 && stack[top] != '(')
            {
                result[j++] = stack[top--];
            }

            top--;
        }
        else
       result[j++] = c;
        
        i++;
    }
    while (top >= 0)
    {
        result[j++] = stack[top--];
    }
    result[j] = '\0';
    strcpy(s,result);
    printf("the postfix expression is %s\n", result);
    return s;
}


void eval_postfix(char *exp)
{
        char op1[100],op2[50],res[50];
        int i;
    for (i = 0; exp[i] != '\0'; i++)
    {
        if (isalpha(exp[i]))
        {
            res[0] = exp[i], res[1] = '\0';
            push(res);

        }
        else if (exp[i]=='+'||exp[i]=='-'||exp[i]=='*'||exp[i]=='/')
        {
            strcpy(op2, pop());
            strcpy(op1, pop());

            res[0] = exp[i], res[1] = '\0';
            strcat(op1, res);
            strcat(op1, op2);
            Prec(op1);
            push(op1);
        }
        res[0] = '\0';
    }
    printf("%s\n",pop());
    }

void Prec(char * p)
{
    int i;
    for (i = strlen(p); i >= 0; i--)
            p[i+1] = p[i];
    p[0] = '(';
    p[strlen(p)+1]='\0';
    p[strlen(p)]=')';
}

void push(char * p)
{
    int j = 0;
    ++top1;
    while (*p != '\0')
        Stack[top1][j++] = *p++;
    Stack[top1][j] = '\0';
}

char *pop(void)
{
        char * expr = Stack[top1--];
        return expr;
}

