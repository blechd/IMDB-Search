#include <stdio.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char* argv[]) {
    int i;
    struct title_principals* principals;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return -1;
    }

    principals = get_principals(argv[1]);
    for (i = 0; i < 10; i++) {
        printf("element %d: %s %s %s\n", i + 1, principals[i].tconst, principals[i].nconst, principals[i].characters);
    }
    for (i = 14648773; i < 14648783; i++) {
        printf("element %d: %s %s %s\n", i + 1, principals[i].tconst, principals[i].nconst, principals[i].characters);
    }

    return 0;
}
