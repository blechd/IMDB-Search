#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"

void add_node(struct tree_node** root, char* key, void* structAddress) {
    if (*root) {
        if (strcmp((*root)->key, key) < 0) {
            add_node(&((*root)->children[0]), key, structAddress);
        }
        else {
            add_node(&((*root)->children[1]), key, structAddress);
        }
    }
    else {
        *root = malloc(sizeof(struct tree_node));
        (*root)->key = key;
        (*root)->data = structAddress;
        (*root)->children[0] = NULL;
        (*root)->children[1] = NULL;
    }
}

void* find_node(struct tree_node* root, char* key) {
    if (root) {
        if (strncmp(root->key, key, strlen(key)) < 0) {
            return find_node(root->children[0], key);
        }
        else if (strncmp(root->key, key, strlen(key)) > 0) {
            return find_node(root->children[1], key);
        }
        else {
            return root->data;
        }
    }
    else {
        return NULL;
    }
}

void build_tindex(struct array_struct* arrayStruct) {
    int i;
    for (i = 0; i < arrayStruct->arrlen; i++) {
        /* TODO fix this godforsaken mess */
        add_node(&(arrayStruct->tree1), ((struct title_basics*)(arrayStruct->array))[i].primaryTitle, &(((struct title_basics*)(arrayStruct->array))[i]));
    }
}

struct title_basics* find_primary_title(struct array_struct* arrayStruct, char* title) {
    return (struct title_basics*)find_node(arrayStruct->tree1, title);
}
