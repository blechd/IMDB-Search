/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

struct array_struct {
    int arrlen;
    void* array;
    struct tree_node* tree1;
    struct tree_node* tree2;
};

void get_column(char*, char**, int);
void reverse_string(char*);
void fileNotFound(char*);
