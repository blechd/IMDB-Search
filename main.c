#include <stdio.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory\n", argv[0]);
        return -1;
    }

    get_name(argv[1]);

    return 0;
}
