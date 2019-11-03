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
        if (strcmp(root->key, key) < 0) {
            return find_node(root->children[0], key);
        }
        else if (strcmp(root->key, key) > 0) {
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
        add_node(&(arrayStruct->tree1),
                ((struct title_basics*)(arrayStruct->array))[i].tconst,
                &(((struct title_basics*)(arrayStruct->array))[i]));
    }
}

void build_ptindex(struct array_struct* arrayStruct) {
    int i;
    for (i = 0; i < arrayStruct->arrlen; i++) {
        add_node(&(arrayStruct->tree2),
                 ((struct title_basics*)(arrayStruct->array))[i].primaryTitle,
                 &(((struct title_basics*)(arrayStruct->array))[i]));
    }
}

struct title_basics* find_primary_title(struct array_struct* arrayStruct, char* title) {
    return (struct title_basics*)find_node(arrayStruct->tree2, title);
}

struct title_basics* find_tconst(struct array_struct* arrayStruct, char* tconst) {
    return (struct title_basics*)find_node(arrayStruct->tree1, tconst);
}

void build_nindex(struct array_struct* arrayStruct) {
    int i;
    for (i = 0; i < arrayStruct->arrlen; i++) {
        add_node(&(arrayStruct->tree1),
                 ((struct name_basics*)(arrayStruct->array))[i].nconst,
                 &(((struct name_basics*)(arrayStruct->array))[i]));
    }
}

void build_pnindex(struct array_struct* arrayStruct) {
    int i;
    for (i = 0; i < arrayStruct->arrlen; i++) {
        add_node(&(arrayStruct->tree2),
                 ((struct name_basics*)(arrayStruct->array))[i].primaryName,
                 &(((struct name_basics*)(arrayStruct->array))[i]));
    }
}

struct name_basics* find_primary_name(struct array_struct* arrayStruct, char* name) {
    return (struct name_basics*)find_node(arrayStruct->tree2, name);
}

struct name_basics* find_nconst(struct array_struct* arrayStruct, char* nconst) {
    return (struct name_basics*)find_node(arrayStruct->tree1, nconst);
}

void build_tindex_tp(struct array_struct* arrayStruct) {
    int i;
    for (i = 0; i < arrayStruct->arrlen; i++) {
        add_node(&(arrayStruct->tree1),
                 ((struct title_principals*)(arrayStruct->array))[i].tconst,
                 &(((struct title_principals*)(arrayStruct->array))[i]));
    }
}

void build_nindex_tp(struct array_struct* arrayStruct) {
    int i;
    for (i = 0; i < arrayStruct->arrlen; i++) {
        add_node(&(arrayStruct->tree2),
                 ((struct title_principals*)(arrayStruct->array))[i].nconst,
                 &(((struct title_principals*)(arrayStruct->array))[i]));
    }
}

struct title_principals* find_tconst_tp(struct array_struct* arrayStruct, char* tconst) {
    return (struct title_principals*)find_node(arrayStruct->tree1, tconst);
}

struct title_principals* find_nconst_tp(struct array_struct* arrayStruct, char* nconst) {
    return (struct title_principals*)find_node(arrayStruct->tree2, nconst);
}
