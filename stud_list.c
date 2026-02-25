#include <stdio.h>
#include <stdlib.h>
#define SIZE_STD sizeof(student)

typedef struct {
    int id;
    float gpa;
}student;

student* createClass(int n){
    student* class = malloc(n * SIZE_STD);
    
    if(class == NULL){
        printf("MEMORY ALLOCATION FAILED x_x \n");
        return NULL;
    }
    printf("dont hesitate to fill up the data :33 \n");
    for(int i=0; i<n ;i++){
        printf("stud %d id: ", i+1);
        scanf("%d", &class[i].id);
        printf("stud %d gpa: ", i+1);
        scanf("%f", &class[i].gpa);
        printf("\n");
    }
    return class;
}

void findTopStudent(student* list, int n){
    float gpa_top = list[0].gpa;
    int i, id_top = list[0].id;

    for(i=1 ; i<n; i++){
        if(list[i].gpa > gpa_top){
            gpa_top = list[i].gpa;
            id_top  = list[i].id;
        }
    }
    printf("ID topStudent: %d\n", id_top);
}

int main(){
    int n;

    printf("how many students are there? :(  ");
    scanf("%d",&n);
    printf("\n");

    student* class = createClass( n );

    findTopStudent(class, n);
    free(class);
    class = NULL;
    
    return 0;
}