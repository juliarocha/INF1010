
typedef struct arvExp {
    char info;
    struct arvExp* esq;
    struct arvExp* dir;
    struct arvExp* pai;
} ArvExp;

ArvExp* arv_criavazia (void);

ArvExp* arv_cria (char info, ArvExp* sae, ArvExp* sad, ArvExp* pai);

ArvExp* arv_libera (ArvExp* a);

int arv_vazia (ArvExp* a);

int isOperator(char c);

void arv_imprime (ArvExp* a);

// void arv_percurso_preordem (ArvExp* a);
// void arv_percurso_simetrica (ArvExp* a);
// void arv_percurso_posordem (ArvExp* a);
