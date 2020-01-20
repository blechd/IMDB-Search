/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

void notfoundError() {
    fprintf(stderr, "Error: Not found.\n");
}

/* returns pointer to substring of argument */
char* trimWhitespace(char* string) {
    char* end;

    while (isspace(*string)) {
        string++;
    }

    end = string + strlen(string) - 1;
    while (end > string && isspace(*end)) {
        end--;
    }

    end[1] = 0;
    return string;
}

void getQuery(char** query, int* option) {
    char* line = calloc(256, 1);

    printf("> ");
    fgets(line, 256, stdin);
    line[strlen(line) - 1] = 0;
    *query = malloc(250);

    if (!strchr(line, ' ')) { /* if no space found in input */
        *option = 0;
        sscanf(line, "%s", *query);
    } else {
        strncpy(*query, strchr(line, ' ') + 1, 250);
    }

    if (!strncmp(line, "name", 4)) {
        *option = -1;
    }
    else if (!strncmp(line, "title", 5)) {
        *option = 1;
    }
    else {
        *option = 0;
    }
    free(line);
}

int main(int argc, char* argv[]) {
    struct array_struct* names, *titles, *principals;
    struct name_basics* name;
    struct title_basics* title;
    struct tree_node* principal;
    int i;

    char* query = NULL;
    /* option will be negative for "name" command,
     * zero for invalid choice,
     * positive for "title" command */
    int option = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return -1;
    }

    printf("Building name trees...\n");
    names = get_name(argv[1]);
    build_nindex(names);
    build_pnindex(names);

    printf("Building title trees...\n");
    titles = get_title(argv[1]);
    build_tindex(titles);
    build_ptindex(titles);

    printf("Building principal trees...");
    principals = get_principals(argv[1]);
    build_tindex_tp(principals);
    build_nindex_tp(principals);

    while (1) {
        getQuery(&query, &option);
        if (option == 0) {
            if (!strncmp(query, "exit", 4)) {
                free(query);
                break;
            }
            printf("Invalid option, please try again.\n");
        }
        else if (option < 0) { /* find titles given name */
            char* trimmed = trimWhitespace(query);
            name = find_primary_name(names, trimmed);
            if (name) {
                principal = find_nconst_tp(principals, name->nconst);
                if (!principal) {
                    notfoundError();
                }
                while (principal) {
                    title = find_tconst(titles, ((struct title_principals*)(principal->data))->tconst);
                    if (title) {
                        printf("%s : %s", title->primaryTitle, ((struct title_principals*)(principal->data))->characters);
                    }
                    principal = principal->children[1]; /* values that are equal get put in the right child */
                }
            } else notfoundError();
        }
        else if (option > 0) { /* find name given title */
            char* trimmed = trimWhitespace(query);
            title = find_primary_title(titles, trimmed);
            if (title) {
                principal = find_tconst_tp(principals, title->tconst);
                if (!principal) {
                    notfoundError();
                }
                while (principal) {
                    name = find_nconst(names, ((struct title_principals*)(principal->data))->nconst);
                    if (name) {
                        printf("%s : %s", name->primaryName, ((struct title_principals*)(principal->data))->characters);
                    }
                    principal = principal->children[1];
                }
            } else notfoundError();
        }
        free(query);
    }

    /* free memory */
    free_tree(names->tree1);
    free_tree(names->tree2);
    for (i = 0; i < names->arrlen; i++) {
        free(((struct name_basics*)(names->array))[i].nconst);
        free(((struct name_basics*)(names->array))[i].primaryName);
    }
    free(names->array);

    free_tree(titles->tree1);
    free_tree(titles->tree2);
    for (i = 0; i < titles->arrlen; i++) {
        free(((struct title_basics*)(titles->array))[i].tconst);
        free(((struct title_basics*)(titles->array))[i].primaryTitle);
    }
    free(titles->array);

    free_tree(principals->tree1);
    free_tree(principals->tree2);
    for (i = 0; i < principals->arrlen; i++) {
        free(((struct title_principals*)(principals->array))[i].tconst);
        free(((struct title_principals*)(principals->array))[i].nconst);
        free(((struct title_principals*)(principals->array))[i].characters);
    }
    free(principals->array);

    return 0;
}
