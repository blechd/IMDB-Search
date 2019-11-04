/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

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

struct tree_node* find_node(struct tree_node* root, char* key) {
    if (root) {
        if (!strcmp(root->key, key)) {
            return root;
        }
        else if (strcmp(root->key, key) < 0) {
            return find_node(root->children[0], key);
        }
        else { /* strcmp(root->key, key) > 0 */
            return find_node(root->children[1], key);
        }
    }
    else {
        return NULL;
    }
}

void free_tree(struct tree_node* root) {
    if (root) {
        free_tree(root->children[0]);
        free_tree(root->children[1]);
        free(root);
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
    struct tree_node* found = find_node(arrayStruct->tree2, title);
    if (!found) return NULL;
    return (struct title_basics*)(found->data);
}

struct title_basics* find_tconst(struct array_struct* arrayStruct, char* tconst) {
    struct tree_node* found = find_node(arrayStruct->tree1, tconst);
    if (!found) return NULL;
    return (struct title_basics*)(found->data);
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
    struct tree_node* found = find_node(arrayStruct->tree2, name);
    if (!found) return NULL;
    return (struct name_basics*)(found->data);
}

struct name_basics* find_nconst(struct array_struct* arrayStruct, char* nconst) {
    struct tree_node* found = find_node(arrayStruct->tree1, nconst);
    if (!found) return NULL;
    return (struct name_basics*)(found->data);
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

struct tree_node* find_tconst_tp(struct array_struct* arrayStruct, char* tconst) {
    return find_node(arrayStruct->tree1, tconst);
}

struct tree_node* find_nconst_tp(struct array_struct* arrayStruct, char* nconst) {
    return find_node(arrayStruct->tree2, nconst);
}
