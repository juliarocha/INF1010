#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "ArvExp.h"

ArvExp* arv_criavazia (void)
{
    return NULL;
}

ArvExp* arv_cria (char info, ArvExp* sae, ArvExp* sad, ArvExp* pai)
{
    ArvExp* p=(ArvExp*)malloc(sizeof(ArvExp));
    if(p==NULL) exit(1);
    p->info = info;
    p->esq = sae;
    p->dir = sad;
    p->pai = pai;
    return p;
}

ArvExp* arv_libera (ArvExp* a){
    if (!arv_vazia(a)){
        arv_libera(a->esq); /* libera sae */
        arv_libera(a->dir); /* libera sad */
        free(a); /* libera raiz */
    }
    return NULL;
}

int arv_vazia (ArvExp* a)
{
    return a==NULL;
}

// funcao auxiliar para identificar operador
int isOperator(char c) 
{ 
    if (c == '+' || c == '-' || c == '*' || c == '/') 
        return 1; 
    return 0; 
} 

// funcao auxiliar para conversao de char para int levando em consideracao numeros acima de 9
int getDecimal(char charValue) {
    if (charValue>= 97 && charValue<107)
        return (int)(charValue) - 87; // entre 10 e 19
    return (int)(charValue) - '0';
}

void arv_imprime (ArvExp* a)
{
    if (!arv_vazia(a)){
        if (!isOperator(a->info))
            printf("(%d ",getDecimal(a->info));
        else 
            printf("(%c ",a->info);
        arv_imprime(a->esq); 
        arv_imprime(a->dir); 
        printf(")");
    }
    else
        printf("() ");
}

// void arv_percurso_preordem (ArvExp* a)
// {
//     if (!arv_vazia(a)){
//         printf("(%c ",a->info); 
//         arv_percurso_preordem(a->esq);
//         arv_percurso_preordem(a->dir);
//     }
//     else
//         printf("* ");
// }

// void arv_percurso_simetrica (ArvExp* a)
// {
//     if (!arv_vazia(a)){
//         arv_percurso_simetrica(a->esq);
//         printf("(%c ",a->info); 
//         arv_percurso_simetrica(a->dir);
//     }
//     else
//         printf("* ");
// }

// void arv_percurso_posordem (ArvExp* a)
// {
//     if (!arv_vazia(a)){
//         arv_percurso_posordem(a->esq);
//         arv_percurso_posordem(a->dir);
//         printf("(%c ",a->info); 
//     }
//     else
//         printf("* ");
// }

