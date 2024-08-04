#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX 50
enum sType{operand,operator,leftbracket,rightbracket,terminate};
char stack[MAX];
int top=-1;
int isempty();
int isfull();
void push(char);
char pop();
int precedence(char);
int findprecedence(char,char);
enum sType finddymbolType(char);
void main()
{
    char infix[50],postfix[50],scanchar,stkchar;
    int i=0,j=0,len;
    printf("\nEnter the infix expression =");
    gets(infix);
    len=strlen(infix);
    while(i<len)
    {
        scanchar=infix[i];
        switch(finddymbolType(scanchar))
        {
            case operand:
                postfix[j++]=scanchar;
                break;
            case operator:
                if(isempty())
                    push(scanchar);
                else
                {
                    do
                    {
                        /* code */
                        stkchar=pop();
                        if(findprecedence(stkchar,scanchar))
                        {
                            postfix[j++]=stkchar;
                        }
                        else
                            break;
                    } while (!isempty());
                    if(!findprecedence(stkchar,scanchar))
                    {
                        push(stkchar);
                        push(scanchar);
                    }
                    else
                        push(scanchar);  //when stack is empty
                    
                }
                break;
                case leftbracket:
                    push(scanchar);
                    break;
                case rightbracket:
                    stkchar=pop();
                    while(stkchar!='(')
                    {
                        postfix[j++]=stkchar;
                        stkchar=pop();
                    }
                    break;
                case terminate:
                    printf("\nWrong input.......");
                    return;
        }
        ++i;
    }
    while(!isempty())
    {
        postfix[j++]=pop();
    }
    postfix[j]='\0';
    printf("\nPostfix Expression is : ");
    printf("%s\n",postfix);
}
int isempty()
{
    if(top==-1)
        return 1;
    else
        return 0;
}
int isfull()
{
    if(top==MAX-1)
        return 1;
    else
        return 0;
}
void push(char c)
{
    if(isfull)
        return;
    else
        stack[++top]=c;
}
char pop()
{
    char item;
    if(!isempty())
        item=stack[top--];
    return(item);
}
int findprecedence(char c1,char c2)
{
    if(precedence(c1)>=precedence(c2))
        return 1;
    else 
        return 0;
}
int precedence(char c)
{
    int priority;
    switch(c)
    {
        case '(':
            priority=0;
            break;
        case '+':
        case '-':
            priority=1;
            break;
        case '*':
        case '/':
            priority=2;
            break;
    }
    return(priority);
}
enum sType finddymbolType(char c)
{
    enum sType symbol;
    if(isalpha(c))
        symbol=operand;
    else
    {
        switch (c)
        {
            case '+':
            case '-':
            case '*':
            case '/':
                symbol=operator;
                break;
            case '(':
                symbol=leftbracket;
                break;
            case ')':
                symbol=rightbracket;
                break;
            default:
                symbol=terminate;
        }
    }
    return(symbol);
}