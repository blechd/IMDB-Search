#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void get_column(char* line, char** column, int columnNum) {
    int i = 0;
    int colCount = 0;
    int tabBefore = 0, tabAfter = 0;
    char* lineStart = line;
    /*printf("%s", line);*/

    while (1) {
        if (!strncmp(line, "\t", 1)) {
            colCount++;
            if (colCount == columnNum) {
                tabBefore = i;
                lineStart = line + 1;
            } else if (colCount == columnNum + 1) {
                tabAfter = i;
                break;
            }
        }

        i++;
        line++;
    }

    *column = malloc(tabAfter - tabBefore);
    strncpy(*column, lineStart, tabAfter - tabBefore - 1);
    (*column)[tabAfter - tabBefore - 1] = '\0';
}
