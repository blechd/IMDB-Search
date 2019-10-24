#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name.h"

struct name_basics* get_name(char* path) {
    FILE* fp;
    char* line = malloc(sizeof(char) * 256);
    char* dir = malloc(strlen(path) + strlen("/name.basics.tsv") + 1);
    strcpy(dir, path);
    strcat(dir, "/name.basics.tsv");

    fp = fopen(dir, "r");
    while(!feof(fp)) {
        fgets(line, 256, fp);
        printf("%s", line);
    }
    fclose(fp);
    free(line);
    free(dir);
    return NULL;
}
