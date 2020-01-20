/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name.h"
#include "common.h"

struct array_struct* get_name(char* path) {
    FILE* fp;
    struct name_basics* names;
    struct array_struct* arrayStruct = malloc(sizeof(struct array_struct));
    char* column;
    char* line = malloc(sizeof(char) * 1024);
    char* dir = malloc(strlen(path) + strlen("/name.basics.tsv") + 1);
    int actorCount = 0;
    int i = 0;

    strcpy(dir, path);
    strcat(dir, "/name.basics.tsv");

    fp = fopen(dir, "r");
    if (!fp) {
        fileNotFound(dir);
    }
    while (!feof(fp)) {
        fgets(line, 1024, fp);
        get_column(line, &column, 4);
        if (strstr(column, "actor") || strstr(column, "actress")) {
            actorCount++;
        }
        free(column);
    }
    names = malloc(sizeof(struct name_basics) * actorCount);
    fseek(fp, 0, SEEK_SET);

    /* ignore column titles */
    fgets(line, 1024, fp);
    while (!feof(fp)) {
        fgets(line, 1024, fp);
        get_column(line, &column, 4);
        if (strstr(column, "actor") || strstr(column, "actress")) {
            get_column(line, &(names[i].nconst), 0);
            reverse_string(names[i].nconst);
            get_column(line, &(names[i].primaryName), 1);
            i++;
        }
        free(column);
    }

    fclose(fp);
    free(line);
    free(dir);

    arrayStruct->arrlen = actorCount;
    arrayStruct->array = names;
    arrayStruct->tree1 = NULL;
    arrayStruct->tree2 = NULL;
    return arrayStruct;
}

