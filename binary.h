struct tree_node {
    char* key;
    void* data;
    struct tree_node* children[2];
};

void add_node(struct tree_node**, char*, void*);
void* find_node(struct tree_node*, char*);
void build_tindex(struct array_struct*);
void build_ptindex(struct array_struct*);
void build_nindex(struct array_struct*);
void build_pnindex(struct array_struct*);
void build_tindex_tp(struct array_struct*);
void build_nindex_tp(struct array_struct*);
