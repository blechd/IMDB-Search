struct title_basics {
    char* tconst;
    char* primaryTitle;
};

struct array_struct* get_title(char*);
struct title_basics* find_primary_title(struct array_struct*, char*);
struct title_basics* find_tconst(struct array_struct*, char*);