#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct{
    int items[SIZE];
    int top;
}stack;

stack* initialize(){
    stack* s = malloc(sizeof(stack));
    s->top = -1;
    return s;
}

int isFull(stack * s){
    return s->top == SIZE - 1 ;
}

int isEmpty(stack* s){
    return s->top == -1;
}

void push(stack* s, int x){
    if(!isFull(s)){
    s->top++;
    s->items[s->top] = x;
    }
}

int pop(stack * s){
    if(!isEmpty(s)){
    int x = s->items[s->top];
    s->top--;
    return x;
    }
}

int peek(stack* s){
    if(!isEmpty(s))
    return s->items[s->top];
}

void reverse_str(char* str){
    stack* s = initialize();
    int i = 0;

    if(s == NULL) return;
    while(str[i]!='\0'){
        push(s, str[i++]);
    }
    i=0;
    while(!isEmpty(s)){
        str[i++] = pop(s); 
    }
    str[i] = '\0';
    free(s);
}

int check_sorted(stack* s){
    if(isEmpty(s)){
        printf("stack is empty, consider it SORTED :3 ");
        return 1;
    }
    if(s->top == 0){
        printf("stack contains only ONE ELEMENT ... SORTED ALREADY :3 ");
        return 1;
    }

    stack* copy = initialize();
    int x = pop(s), flag = 1;

    push(copy, x);
    while(!isEmpty(s)){
        int y = pop(s);
        
        push(copy, y);
        if(x > y){flag = 0; break;}
        x = y;
    }
    while(!isEmpty(copy))
        push(s, pop(copy));

    free(copy);
    return flag == 1;
}

void delete_even(stack *s){
    stack* copy = initialize();
    int x = 0;

    while(!isEmpty(s)){
        x = pop(s);
        if(!(x % 2 == 0))
            push(copy , x);
    }
    while(!isEmpty(copy)){
        push(s, pop(copy));
    }
    free(copy);
} 

int min_comparator(stack* s1, stack* s2) {
    if (peek(s1) < peek(s2)) return pop(s1);
    return pop(s2);
}

stack* sort_stacks(stack* s1, stack* s2) {
    stack* s3 = initialize();
    stack* result = initialize();

    while (!isEmpty(s1) && !isEmpty(s2)){
        push(s3, min_comparator(s1, s2));
    }
    while (!isEmpty(s1)) push(s3, pop(s1));
    while (!isEmpty(s2)) push(s3, pop(s2));

    while (!isEmpty(s3)) {
        push(result, pop(s3));
    }

    free(s3);
    return result;
}

int check_parantheses(stack* s) {
    stack* copy = initialize();
    int count_LP = 0, count_RP = 0, flag = 1;

    while (!isEmpty(s)) {
        int x = pop(s);
        push(copy, x);

        if (x == '(') count_LP++;
        if (x == ')') {
            count_RP++;
            if (count_RP > count_LP) flag = 0; 
        }
    }
    while (!isEmpty(copy)) {
        push(s, pop(copy));
    }
    if (flag && count_LP == count_RP && ((count_LP + count_RP) % 2 == 0)){
        return 1;
    }
    return 0;
}

void execute(int choice) {
    switch (choice){
    case 1:{
        char str[100];
        printf("Type in string to reverse: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        reverse_str(str);
        printf("Reversed string: %s", str);
        break;
    }
    case 2:{
        int i = 0, len = 0;
        stack* s = initialize();

        printf("Enter number of integers you want to store: ");
        scanf("%d", &len);
        printf("Enter stack integers one by one DESCENDINGLY(for min to be on top) :\n");
        for (i = 0; i < len; i++) {
            int p = 0;
            scanf("%d", &p);
            push(s, p);
        }
        if (check_sorted(s)) printf("Stack IS sorted\n");
        else printf("Stack is NOT sorted\n");
        break;
    }
    case 3:{
        int i = 0, len = 0;
        stack* s = initialize();
        
        printf("Enter number of integers you want to store: ");
        scanf("%d", &len);
        printf("Enter stack integers one by one  :\n");
        for (i = 0; i < len; i++) {
            int p = 0;
            scanf("%d", &p);
            push(s, p);
        }            
        delete_even(s);
        printf("new stack is\n");

        while(!isEmpty(s)){
            printf("%d ", pop(s));  
        }
        break;
    }
    case 4:{
        int i = 0, len1 = 0, len2 = 0;
        stack* s1 = initialize();
        stack* s2 = initialize();
        stack* s3 = initialize();

        printf("FOR STACK(1)\n");
        printf("Enter number of integers you want to store: ");
        scanf("%d", &len1);
        printf("Enter stack integers one by one DESCENDINGLY :\n");
        for (i = 0; i < len1; i++) {
            int p = 0;
            scanf("%d", &p);
            push(s1, p);
        }
        if (!check_sorted(s1)){
             printf("Stack(1) IS NOT sorted to merge\n");   
             break;        
        } 

        printf("FOR STACK(2)\n");
        printf("Enter number of integers you want to store: ");
        scanf("%d", &len2);
        printf("Enter stack integers one by one DESCENDINGLY :\n");
        for (i = 0; i < len2; i++) {
            int p = 0;
            scanf("%d", &p);
            push(s2, p);
        }
        if (!check_sorted(s2)){
             printf("Stack(2) IS NOT sorted\n");   
             break;        
        }          
        s3 = sort_stacks(s1, s2);
        while(!isEmpty(s3)){
            printf("%d ", pop(s3));  
        }
        break;
    }
    case 5:{
    char str[100];
    stack* s = initialize();

    printf("Type in string to check parentheses balance: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    int len = strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        push(s, str[i]);
    }
    if (check_parantheses(s)) {
        printf("Parentheses are balanced :3\n");
    } else {
        printf("Parentheses are NOT balanced :( \n");
    }
    break;
    }

    case 6:{
        printf("Exiting...\n");
        exit(0);
    }
    default:
        printf("Invalid choice. choose from (1-6) :( \n");
    }
}

int main() {
    int choice;

    printf("Go ahead, choose a function :3\n");
    printf("1) Reverse a String\n");
    printf("2) Check stack if sorted (min on top)\n");
    printf("3) Delete Even numbers in stack\n");
    printf("4) Merge two sorted stacks (min on top)\n");
    printf("5) Check balanced parentheses in string\n");
    printf("6) Exit\n");
    printf("Choice: ");

    scanf("%d", &choice);
    getchar(); 

    execute(choice);

    return 0;
}
