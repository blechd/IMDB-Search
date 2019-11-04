/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

struct title_principals {
    char* tconst;
    char* nconst;
    char* characters;
};

struct array_struct* get_principals(char*);
struct tree_node* find_tconst_tp(struct array_struct*, char*);
struct tree_node* find_nconst_tp(struct array_struct*, char*);