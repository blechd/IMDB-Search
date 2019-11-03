struct title_principals {
    char* tconst;
    char* nconst;
    char* characters;
};

struct array_struct* get_principals(char*);
struct title_principals* find_tconst_tp(struct array_struct*, char*);
struct title_principals* find_nconst_tp(struct array_struct*, char*);