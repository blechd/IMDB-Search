#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name.h"
#include "common.h"

struct name_basics* get_name(char* path) {
    FILE* fp;
    char* column;
    char* line = malloc(sizeof(char) * 1024);
    char* dir = malloc(strlen(path) + strlen("/name.basics.tsv") + 1);
    int actorCount = 0;
    strcpy(dir, path);
    strcat(dir, "/name.basics.tsv");

    fp = fopen(dir, "r");
    while(!feof(fp)) {
        fgets(line, 1024, fp);
        get_column(line, &column, 4);
        if (strstr(column, "actor") || strstr(column, "actress")) {
            actorCount++;
        }
        free(column);
    }
    printf("# of actors: %d\n", actorCount);
    fclose(fp);
    free(line);
    free(dir);
    return NULL;
}

