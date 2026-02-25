#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat(const char* a, const char* b) {
    int len_a = strlen(a), len_b = strlen(b);
    char* c = malloc(len_a + len_b + 1);

    if (c == NULL) {
        printf("MEMORY ALLOCATION FAILED :(\n");
        return NULL;
    }

    for (int i = 0; i < len_a; i++)
        c[i] = a[i];

    for (int j = 0; j < len_b; j++)
        c[len_a + j] = b[j];

    c[len_a + len_b] = '\0';
    return c;
}

int main() {
    const char *str1 = "lol:3 ", *str2 = "APPRECIATE YOU SAMI!!";
    char* cat = concat(str1, str2);

    if (cat != NULL)
        printf("%s\n", cat);

    free(cat);
    cat = NULL;

    return 0;
}