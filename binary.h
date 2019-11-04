/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

struct tree_node {
    char* key;
    void* data;
    struct tree_node* children[2];
};

void add_node(struct tree_node**, char*, void*);
struct tree_node* find_node(struct tree_node*, char*);
void free_tree(struct tree_node*);
void build_tindex(struct array_struct*);
void build_ptindex(struct array_struct*);
void build_nindex(struct array_struct*);
void build_pnindex(struct array_struct*);
void build_tindex_tp(struct array_struct*);
void build_nindex_tp(struct array_struct*);
