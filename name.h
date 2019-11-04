/* Andy Li
 * 1048672
 * ali13@uoguelph.ca
 */

struct name_basics {
    char* nconst;
    char* primaryName;
};

struct array_struct* get_name(char*);
struct name_basics* find_primary_name(struct array_struct*, char*);
struct name_basics* find_nconst(struct array_struct*, char*);
