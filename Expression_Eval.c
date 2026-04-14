#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct node{
    float data;
    struct node* next;
}node;

typedef struct {
    node *top;
}stack;

stack *initialize ()
{
    stack *s=malloc(sizeof(stack));
    s->top =NULL;
    return s;
} 

node* NewNode(float value){
    node* n = malloc(sizeof(node));
    n->data = value;
    n->next = NULL;
    return n;
}

float pop (stack *s)
{
    node *n=s->top;
    float data =n->data;
    s->top = s->top->next;
    free(n);
    return data;
}

int isEmpty (stack *s)
{
   return s->top == NULL ;
}

void push(stack* s, float value){
    node* n = NewNode(value);
    n->next = s->top;
    s->top = n;
}

float peek(stack* s){
    return s->top->data;
}

int priority(char c) {
    switch (c) {
        case '^': return 3;
        case '*': case '/': case '%': return 2;
        case '+': case '-': return 1;
        case '(': return 0; 
        default:  return -1;
    }
}

float evaluate (char x , float op1 , float op2 ){
    switch (x){
    case '+': return op1 + op2 ;
    case '-': return op1 - op2 ;
    case '*': return op1 * op2;
    case '^': return pow (op1 , op2) ;
    case '%': return fmodf(op1 , op2) ;
    case '/': return op1 / op2 ;
    }
}

char* infixToPostfix(char* infix){
    int lenExp = strlen(infix);
    char* postfix = malloc(lenExp * 2 + 1); 
    if (!postfix) return NULL;
    postfix[0] = '\0'; 

    stack* s = initialize();
    char* ptr;
    char* tok = strtok_r(infix, " ", &ptr);

    while(tok != NULL){
        if(isdigit(tok[0]) || (tok[0] == '-' && strlen(tok) > 1)){
            strcat(postfix, tok);
            strcat(postfix, " ");
        }
        else if(tok[0] == '('){
            push(s, '(');
        }
        else if(tok[0] == ')'){
            while(!isEmpty(s) && peek(s) != '('){
                char tStr[2] = {pop(s), '\0'};
                strcat(postfix, tStr);
                strcat(postfix, " ");
            }
            if(!isEmpty(s)) pop(s); 
        }      
        else{
            while(!isEmpty(s) && peek(s) != '(' && priority(peek(s)) >= priority(tok[0])){
                char tStr[2] = {pop(s), '\0'};
                strcat(postfix, tStr);
                strcat(postfix, " ");
            }
            push(s, tok[0]);
        }
        tok = strtok_r(NULL, " ", &ptr);
    }
    while(!isEmpty(s)){
        char tStr[2] = {pop(s), '\0'};
        strcat(postfix, tStr);
        strcat(postfix, " ");
    }
    free(s);
    return postfix;
}

float evalualatePostfix (char * postfix)
{
    stack *s=initialize();
    if(s == NULL){
        printf(" memory location error ");
        exit(1);
    }

    float op1,op2, result ,x;
    char *token =strtok(postfix," ");
    while( token != NULL){
            if(strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || strcmp(token, "%") == 0 || strcmp(token, "^") == 0)
            {
                   op2=pop(s);
                   op1=pop(s);
                   result = evaluate(token [0] , op1 , op2 );
                   push(s , result);
            }
            else
            {
               x=atof(token);
               push (s,x);

            }
        token=strtok(NULL," ");
    }

    result = pop(s);
    free (s);
    return result;
}

int main(){
    char str[200];
    printf("Enter expression to evaluate :3! : ");
    fgets(str, 199, stdin);
    str[strcspn(str, "\n")] = 0;
    char* postFix = infixToPostfix(str);
    float  res = evalualatePostfix(postFix);
    printf("result is : %.6f !", res);

    return 0;
}