#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node * next;
} node;

typedef struct {
    node* head;
} linkedList;

linkedList* initialize() {
    linkedList* L = malloc(sizeof(linkedList));
    if(L == NULL){
        printf("failed to allocate linked list:(");
        exit(1);
    }
    L->head = NULL;
    return L;
}

node* create_node(int value){
    node* n = malloc(sizeof(node));
    if(n == NULL){
        printf("allocation for new node failed :(");
        return NULL;
    }
    n->data = value;
    n->next = NULL;
    return n;
}

void insertAtEnd(linkedList* l, int value){
    node* n = create_node(value);

    if(l->head == NULL){
        l->head = n;
    }
    else{
        node* temp = l->head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = n;
    }
}

void insertAtBeginning(linkedList* l, int value){
    node* n = create_node(value);
    n->data = value;
    n->next = l->head;
    l->head = n;
}

int digit_input() {
    int ip;
    char term;
    
    while (scanf("%d%c", &ip, &term) != 2 || term != '\n') {
        printf("Non_Integers are NOT allowed :(\nRe-enter: ");
        if (term != '\n') {
            while (getchar() != '\n');
        }
    }
    return ip;
}

void fill(linkedList* l) {
    printf("Enter num of elements: ");
    int size = digit_input();
    while(size <= 0) {
        printf("size MUST be more than zero\nRe_enter: ");
        size = digit_input(); 
    }

    printf("Fill elements one by one :)\n");
    for (int i = 0; i < size; i++) {
        printf("Element (%d): ", i);
        int x = digit_input();
        insertAtEnd(l, x);
    }
}

void displayList(linkedList*l){
    if(l->head == NULL ){
        printf("list is EMPTY :( !"); return;
    }
    node* temp = l->head;
    while(temp != NULL){
        printf("%d  ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

node* search(linkedList* l, int value) {
    if (l->head == NULL) return NULL;
    int i=0;
    node* temp = l->head;

    while (temp != NULL) {
        if (temp->data == value){
            displayList(l); 
            printf("value found at index (%d) :)", i);
            return temp;
        }
        temp = temp->next;
        i++;
    }
    return NULL;
}

void insert(linkedList* l, int index, int value){
    int ia;
    if(index < 0){
        printf("Invalid Index :( ! \nRe-enter index: ");
        ia = digit_input();
        insert(l, ia, value);
        return;
    }
    if(index == 0){
        insertAtBeginning(l, value);
        return;
    }

    node* prev = l->head;
    int x = 0;

    while (prev != NULL && x < index - 1) {
        prev = prev->next;
        x++;
    }
    if(prev == NULL) {
        int ia;
        printf("Index out of bound :( ! \nRe-enter index: ");
        ia = digit_input();
        insert(l, ia, value);
        return;
    }
    node* n = create_node(value);
    n->next = prev->next;
    prev->next = n;
    prev = NULL;
}

int identical(linkedList* x, linkedList* y) {
    node* t1 = x->head;
    node* t2 = y->head;

    while (t1 != NULL && t2 != NULL) {
        if (t1->data != t2->data) return 0;
        t1 = t1->next;
        t2 = t2->next;
    }

    return (t1 == NULL && t2 == NULL);
}

linkedList* merge(linkedList* l1, linkedList* l2) {
    linkedList* res = initialize();
    node* t1 = l1->head;
    node* t2 = l2->head;

    while (t1 != NULL && t2 != NULL){
        if (t1->data <= t2->data) {
            insertAtEnd(res, t1->data);
            t1 = t1->next;
        }
        else{
            insertAtEnd(res, t2->data);
            t2 = t2->next;
        }
    }

    while (t1 != NULL) {
        insertAtEnd(res, t1->data);
        t1 = t1->next;
    }
    while (t2 != NULL) {
        insertAtEnd(res, t2->data);
        t2 = t2->next;
    }

    return res;
}

linkedList* intersection(linkedList* x, linkedList* y) {
    linkedList* res = initialize();
    node* t1 = x->head;
    node* t2 = y->head;

    while (t1 != NULL && t2 != NULL) {
        if (t1->data == t2->data) {
            insertAtEnd(res, t1->data);
            t1 = t1->next;
            t2 = t2->next;
        } 
        else if(t1->data < t2->data) {
            t1 = t1->next;
        } 
        else {
            t2 = t2->next;
        }
    }
    return res;
}

void choice(int num){
    switch(num){
        case 1:{
            linkedList* l = initialize();
            fill(l);

            int value;
            printf("enter value to search for: ");
            value = digit_input();
            node* np = search(l, value);
            if(np == NULL) printf("value not found :(");
            break; 
        }
        case 2:{
            linkedList* l = initialize();
            int value, index;
            fill(l);

            printf("enter value to insert: ");
            value = digit_input();
            printf("enter index to insert at: ");
            index = digit_input();

            insert(l, index, value);
            printf("your new list is :3\n");
            displayList(l);
            break;
        }
        case 3:{
            linkedList* l1 = initialize();
            linkedList* l2 = initialize();
            printf("\nFOR LIST(1):\n");
            fill(l1);
            printf("\nFOR LIST(2):\n"); 
            fill(l2);

            if (identical(l1, l2)) {
                printf("Lists are identical !! :33 heh\n");
            }
            else{
                printf("Lists are NOT Identical :((( unlucky\n");
            }
            break;
        }
        case 4:{
            linkedList* l1 = initialize();
            linkedList* l2 = initialize();
            printf("\nFOR LIST(1):\n");
            fill(l1);
            printf("\nFOR LIST(2):\n"); 
            fill(l2);

            linkedList* res = merge(l1, l2);
            printf("your new list is :3\n");
            displayList(res);            
            break;
        }
        case 5:{
            linkedList* l1 = initialize();
            linkedList* l2 = initialize();
            printf("\nFOR LIST(1):\n");
            fill(l1);
            printf("\nFOR LIST(2):\n"); 
            fill(l2);

            linkedList* res = intersection(l1, l2);
            if(res->head == NULL) printf("no intersection :( ");
            else{
                printf("your new list is :3\n");
                displayList(res);            
            }
            break;
        }
        case 6:{
            printf("exiting...");
            exit(0);
        }
        default:{
            printf("WRONG CHOICE :(\nchoose(1-6) only");
        }
    }
}

int main(){
    printf("\nChoose one of the following :3\n");
    printf("1) SEARCH for a value\n"
           "2) INSERT at specicific index\n"
           "3) IDENTICAL check for 2 lists\n"
           "4) MERGE 2 lists\n"
           "5) INTERSECTION common values in 2 lists\n"
           "6) EXIT :( \n\nChoice: ");

    int ip = digit_input();
    choice(ip);

    return 0;
}