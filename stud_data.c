#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    short month, year;
}Date;

typedef struct{
    Date d;
    char* name;
}Person;

typedef struct{
    Person* p;
    char id[10];
}Student;

Person *cnstPerson(char *name, short month, short year){
    int len = strlen(name);
    Person* p = malloc(sizeof(Person));
    p->name = malloc( len + 1 );

    p->d.month = month;
    p->d.year = year;
    strcpy(p->name, name);

    return p;
} 

Student *cnstStudent(char *name,short month,short year,char *id){
    Student *stud = malloc(sizeof(Student));

    stud->p = cnstPerson(name ,month, year);
    strcpy(stud->id, id);

    return stud;
}

void destruct(Student *s){
    free(s->p->name);
    s->p->name = NULL;
    free(s->p);
    s->p = NULL;
    free(s);
    printf("\nstudent deleted X_X");
}

void printStudent(Student *s){
    printf("Name: %s\n", s->p->name);
    printf("DateOfBirth: %hd/%hd \n", s->p->d.month, s->p->d.year);
    printf("Id: %s\n", s->id);
}

int main(){
    Student* stud = cnstStudent("Francios", 7, 2006, "11174");
    
    printStudent(stud);
    destruct(stud);
    stud = NULL;

    return 0;
}