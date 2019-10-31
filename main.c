#include <stdio.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char* argv[]) {
    struct array_struct* names;
    struct name_basics* found;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return -1;
    }

    names = get_name(argv[1]);
    build_nindex(names);
    found = find_primary_name(names, "Anthony Daniels");

    if (found) {
        printf("found:\n");
        printf("%p\n", (void *) found);
        printf("%s\n", found->nconst);
        printf("%s\n", found->primaryName);
    }
    else {
        printf("not found\n");
    }

    printf("\nfirst node:\n");
    printf("%p\n", (void*)(names->tree1));
    printf("%s\n", (names->tree1)->key);
    printf("%p\n", (void*)(names->tree1)->data);
    printf("%s\n", ((struct name_basics*)(names->tree1)->data)->primaryName);
    printf("%s\n", ((struct name_basics*)(names->tree1)->data)->nconst);

    return 0;
}
