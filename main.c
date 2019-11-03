#include <stdio.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char* argv[]) {
    struct array_struct* names, *titles, *principals;
    struct name_basics* name;
    struct title_basics* title;
    struct title_principals* principal;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return -1;
    }

    names = get_name(argv[1]);
    build_nindex(names);
    build_pnindex(names);

    titles = get_title(argv[1]);
    build_tindex(titles);
    build_ptindex(titles);

    principals = get_principals(argv[1]);
    build_tindex_tp(principals);
    build_nindex_tp(principals);

    printf("Ready\n");
    title = find_primary_title(titles, "Blade Runner");
    principal = find_tconst_tp(principals, title->tconst);
    name = find_nconst(names, principal->nconst);

    printf("name: %s\n", name->primaryName);

    name = find_primary_name(names, "Bruce Lee");
    principal = find_nconst_tp(principals, name->nconst);
    title = find_tconst(titles, principal->tconst);

    printf("title: %s\n", title->primaryTitle);

    return 0;
}
