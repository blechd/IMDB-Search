#include <stdio.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char* argv[]) {
    struct array_struct* titles;
    struct title_basics* found;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return -1;
    }

    titles = get_title(argv[1]);
    build_tindex(titles);
    found = find_primary_title(titles, "Star Wars: Episode V - The Empire Strikes Back");

    printf("found:\n");
    printf("%p\n", (void*)found);
    printf("%s\n", found->tconst);
    printf("%s\n", found->primaryTitle);

    printf("\nfirst node:\n");
    printf("%p\n", (void*)(titles->tree1));
    printf("%s\n", (titles->tree1)->key);
    printf("%p\n", (void*)(titles->tree1)->data);
    printf("%s\n", ((struct title_basics*)(titles->tree1)->data)->primaryTitle);
    printf("%s\n", ((struct title_basics*)(titles->tree1)->data)->tconst);

    return 0;
}
