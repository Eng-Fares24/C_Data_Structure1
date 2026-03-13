#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct{
    int items[MAXSIZE];
    int front;
    int rear;
}Queue;

Queue* init(){
    Queue* q = malloc(sizeof(Queue));
    q->front = q->rear = -1;
    return q;
}

int isEmpty(Queue* q){
    return  q->front == -1;
}

int isFull(Queue* q){
    return (q->rear + 1) % MAXSIZE == q->front;
}

void Enqueue(Queue* q , int x){
    if(isFull(q)){
        printf("queue is full :( ");
        return;
    }
    else if(isEmpty(q)){
        q->front = q->rear = 0;
    }
    else{
        q->rear = (q->rear + 1) % MAXSIZE;
    }
    q->items[q->rear] = x;
}

int Dequeue(Queue* q){
    int x = q->items[q->front];

    if(q->front == q->rear){
        q->front = q->rear = -1;
    }
    else{
        q->front = (q->front + 1) % MAXSIZE;
    }
    return x;
}

void display(Queue* q) {
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }
    int i = q->front;

    while (i != q->rear) {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAXSIZE; 
    }
    printf("%d\n", q->items[q->rear]); 
}

int maximum(Queue* q){
    Queue* copy = init();
    int max;
    
    if(isEmpty(q)){
        printf("Queue is empty");
        return -1;
    }
    else{
        max = Dequeue(q);
        Enqueue(copy, max);

        while(!isEmpty(q)){
            int temp = Dequeue(q);
            Enqueue(copy, temp);
            if(max < temp) max = temp;
        }
    }
    while(!isEmpty(copy)){
        Enqueue(q, Dequeue(copy));
    }
    free(copy);
    copy = NULL;
    return max;
}

void swapFirstLast(Queue* q){
    if(isEmpty(q)){
        printf("no elements to swap :( ");
        return;
    }
    else{
        int last = q->items[q->rear];
        q->items[q->rear] = q->items[q->front];
        q->items[q->front] = last;
    }
}

void insert(Queue* q, int value, int index) {
    if (isFull(q)) {
        printf("Failed to insert :( Queue is FULL\n");
        return;
    }

    if (isEmpty(q)) {
        q->items[index] = value;
        q->front = q->rear = index;
        return;
    }
    int i = q->rear;

    while (i != (index - 1 + MAXSIZE) % MAXSIZE){
        q->items[(i + 1) % MAXSIZE] = q->items[i];
        i = (i - 1 + MAXSIZE) % MAXSIZE;  
    }

    q->items[index] = value;
    q->rear = (q->rear + 1) % MAXSIZE;
}

int isOdd(int n){
    return !(n % 2 == 0);
}

void reverseOdd(Queue* q){
    int i = q->rear;
    int j = q->front;

    while(i != j && (i + 1) % MAXSIZE != j){

        while(!isOdd(q->items[i]) && i != j)
            i = (i - 1 + MAXSIZE) % MAXSIZE;

        while(!isOdd(q->items[j]) && i != j)
            j = (j + 1 + MAXSIZE) % MAXSIZE;

        if(i != j && isOdd(q->items[i]) && isOdd(q->items[j])){
            int temp = q->items[i];
            q->items[i] = q->items[j];
            q->items[j] = temp;

            i = (i - 1 + MAXSIZE) % MAXSIZE;
            j = (j + 1 + MAXSIZE) % MAXSIZE;
        }
    }
} 

void reverse(Queue* q, int k){
    int n = k/2, i, index = q->front;

    for(i = 0; i < n; i++){
        int first = (index + i) % MAXSIZE;
        int second = (index + k - 1 - i) % MAXSIZE;
        
        int temp = q->items[first];
        q->items[first] = q->items[second];
        q->items[second] = temp;
    }
}

/*void fillQueue(Queue* q){
    int x , len = 0, i;

    printf("Enter number of elements: ");
    scanf("%d", &len); 
    printf("Enter Queue elements one by one : \n");
    for(i = 0; i<len ; i++){
        printf("Element %d: ", i+1);
        scanf("%d", &x);
        Enqueue(q, x);
    }
}*/

void fillQueue(Queue* q){
    int x, len, i;
    int valid;

    do {
        printf("Enter number of elements: ");
        valid = scanf("%d", &len);

        if(valid != 1 || len <= 0 || len>100){
            printf("Invalid input. size is from ]0,100] :(\n");
            while(getchar() != '\n'); 
            valid = 0;
        }
    }while(!valid);

    printf("Enter Queue elements one by one:\n");
    for(i = 0; i < len; i++){
        do {
            printf("Element %d: ", i+1);
            valid = scanf("%d", &x);

            if(valid != 1){
                printf("Invalid input. Enter an integer\n");
                while(getchar() != '\n'); 
            }
        }while(valid != 1);

        Enqueue(q, x); 
    }
}

void execute(int choice){
    switch(choice){
        case 1:{
            Queue* q = init();
            fillQueue(q);

            int max = maximum(q);
            printf("Max element is : %d", max);

            break;
        }
        case 2:{
            Queue* q = init();
            fillQueue(q);

            swapFirstLast(q);
            printf("Queue after swapping \n");
            display(q);
            
            break;
        }        
        case 3:{
            Queue* q = init();
            fillQueue(q);

            int value=0, index=0;
            printf("Enter value to insert: ");
            scanf("%d", &value);
            printf("Enter index to insert at: ");
            scanf("%d", &index);
            insert(q, value, index);
            printf("Queue after insertion:\n");
            display(q);
        
            break;
        }
        case 4:{
            Queue* q = init();
            fillQueue(q);

            reverseOdd(q);
            printf("Queue after reverse:\n");
            display(q);

            break;
        }
        case 5:{
            Queue* q = init();
            fillQueue(q);

            int k=0;
            printf("Enter number of elements to reverse up to: ");
            scanf("%d", &k);
            reverse(q, k);
            
            printf("Queue after reversing %d elements :3 :\n", k);
            display(q);

            break;
        }
        case 6:
            exit(0);
            break;
        default :
            printf("wrong choice! insert a number from (1-6)");
    }
}

int main(){
    int choice;

    printf("Enter a function number: \n"
            "1) Maximum element in Queue.\n"
            "2) swap First and Last elements in Queue.\n"
            "3) insert at specific index in Queue.\n"
            "4) reverse ODD elements in Queue.\n"
            "5) reverse up to X elements in Queue.\n"
            "6) Exit program.\nchoice: ");
    
    scanf("%d", &choice);
    execute(choice);

    return 0;
}