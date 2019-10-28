#include <stdio.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char* argv[]) {
    int i;
    struct name_basics* names;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return -1;
    }

    names = get_name(argv[1]);
    for (i = 0; i < 10; i++) {
        printf("element %d: %s %s\n", i + 1, names[i].nconst, names[i].primaryName);
    }
    for (i = 10000; i < 10010; i++) {
        printf("element %d: %s %s\n", i + 1, names[i].nconst, names[i].primaryName);
    }

    return 0;
}
