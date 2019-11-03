#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void get_column(char* line, char** column, int columnNum) {
    int i = 0;
    int colCount = 0;
    int tabBefore = 0, tabAfter = 0;
    char* lineStart = line;

    while (1) {
        if (!strncmp(line, "\t", 1)) {
            colCount++;
            if (colCount == columnNum) {
                if (columnNum != 0) {
                    tabBefore = i + 1;
                    lineStart = line + 1;
                }
            } else if (colCount == columnNum + 1) {
                tabAfter = i;
                break;
            }
        }

        i++;
        line++;
    }

    *column = malloc(tabAfter - tabBefore + 1);
    strncpy(*column, lineStart, tabAfter - tabBefore);
    (*column)[tabAfter - tabBefore] = '\0';
}

void reverse_string(char* string) {
    int start = 0;
    int end = strlen(string) - 1;
    char temp;

    do {
        temp = string[start];
        string[start] = string[end];
        string[end] = temp;
    } while (start++ < end--);
}
