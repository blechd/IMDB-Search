/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "title.h"

struct array_struct* get_title(char* path) {
    FILE* fp;
    struct title_basics* titles;
    struct array_struct* arrayStruct = malloc(sizeof(struct array_struct));
    char* column;
    char* line = malloc(sizeof(char) * 1024);
    char* dir = malloc(strlen(path) + strlen("/title.basics.tsv") + 1);
    int movieCount = 0;
    int i = 0;

    strcpy(dir, path);
    strcat(dir, "/title.basics.tsv");

    fp = fopen(dir, "r");
    if (!fp) {
        fileNotFound(dir);
    }
    while (!feof(fp)) {
        fgets(line, 1024, fp);
        get_column(line, &column, 1);
        if (!strncmp(column, "movie", 5)) {
            free(column);
            get_column(line, &column, 4);
            if (!strncmp(column, "0", 1)) {
                movieCount++;
            }
            free(column);
        }
        else {
            free(column);
        }
    }

    titles = malloc(sizeof(struct title_basics) * movieCount);
    fseek(fp, 0, SEEK_SET);

    /* ignore column titles */
    fgets(line, 1024, fp);
    while (!feof(fp)) {
        fgets(line, 1024, fp);
        get_column(line, &column, 1);
        if (!strncmp(column, "movie", 5)) {
            free(column);
            get_column(line, &column, 4);
            if (!strncmp(column, "0", 1)) {
                get_column(line, &(titles[i].tconst), 0);
                reverse_string(titles[i].tconst);
                get_column(line, &(titles[i].primaryTitle), 2);
                i++;
            }
            free(column);
        }
        else {
            free(column);
        }
    }

    fclose(fp);
    free(line);
    free(dir);

    arrayStruct->arrlen = movieCount;
    arrayStruct->array = titles;
    arrayStruct->tree1 = NULL;
    arrayStruct->tree2 = NULL;
    return arrayStruct;
}
