#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <common.h>
#include "principals.h"

struct title_principals* get_principals(char* path) {
    FILE* fp;
    struct title_principals* principals;
    char* column;
    char* line = malloc(sizeof(char) * 1024);
    char* dir = malloc(strlen(path) + strlen("/title.principals.tsv") + 1);
    int principalCount = 0;
    int i = 0;

    strcpy(dir, path);
    strcat(dir, "/title.principals.tsv");
    printf("Opening: %s\n", dir);

    fp = fopen(dir, "r");
    while (!feof(fp)) {
        fgets(line, 1024, fp);
        get_column(line, &column, 3);
        if (!strncmp(column, "actor", 5) || !strncmp(column, "actress", 7)) {
            principalCount++;
        }
        free(column);
    }

    printf("number of titles: %d\n", principalCount);
    principals = malloc(sizeof(struct title_principals) * principalCount);
    fseek(fp, 0, SEEK_SET);

    /* ignore column titles */
    fgets(line, 1024, fp);
    while (!feof(fp)) {
        fgets(line, 1024, fp);
        get_column(line, &column, 3);
        if (!strncmp(column, "actor", 5) || !strncmp(column, "actress", 7)) {
            get_column(line, &(principals[i].tconst), 0);
            get_column(line, &(principals[i].nconst), 2);
            get_column(line, &(principals[i].characters), 5);
            i++;
        }
        free(column);
    }

    fclose(fp);
    free(line);
    free(dir);
    return principals;
}
