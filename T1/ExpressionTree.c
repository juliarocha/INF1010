#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "ExpressionTree.h"

// funcao auxiliar para identificacao de paternidade de no
int isParent(ArvExp* parent, ArvExp* current) {
    return current->pai == parent;
}

// funcao auxiliar para identificar a possibilidade de paternidade de no
int canBeFather(ArvExp* current, ArvExp* novoNo) {
    if (isOperator(current->info)) {
        return current->dir == NULL || current->esq == NULL;
    }
    return 0;
}

// funcao auxiliar para anexacao de no
void anexNo(ArvExp* current, ArvExp* novoNo) {
    if (current->dir == NULL) 
        current->dir = novoNo;
    else 
        current->esq = novoNo;
    novoNo->pai = current;
}


// funcao de calculo da arvore de expressao
int calculate(ArvExp* arv) {
    if (arv == NULL)
        return 0;
    if (!isOperator(arv->info)) 
        return getDecimal(arv->info);
    else {
        if (arv->info == '+')
            return calculate(arv->esq) + calculate(arv->dir);
        else if (arv->info == '-')
            return calculate(arv->esq) - calculate(arv->dir);
        else if (arv->info == '*')
            return calculate(arv->esq) * calculate(arv->dir);
        else if (arv->info == '/') {
            if (calculate(arv->dir) == 0) {
                printf("\nexpressao invalida: divisão por 0\n");
                return -1;
            }
        }
            return calculate(arv->esq) / calculate(arv->dir);
    }
}

ArvExp* postToTree(char postfix[])
{ 
    int size = strlen(postfix);
    // cria no do ultimo simbolo a direita
    ArvExp* noCorrente = arv_cria (postfix[size -1], arv_criavazia(), arv_criavazia(), NULL);
    
    // define no raiz como no atual
    ArvExp* raiz = noCorrente;
    int i;
    
    // para cada simbolo da direita pra esquerda, excluindo o mais a direita
    for (i = size -2; i >= 0; --i) {
        
        // cria novo no
        ArvExp* novoNo = arv_cria (postfix[i], arv_criavazia(), arv_criavazia(), NULL);
        
        // enquanto o no corrente nao puder ser o pai
        while (!canBeFather(noCorrente, novoNo)) {
            if (noCorrente == raiz && !canBeFather(noCorrente, novoNo)) {
                printf("erro na arvore");
            }
            // no corrente passa a ser o pai
            noCorrente = noCorrente->pai;
        }
        // anexa o novo no ao no corrente
        anexNo(noCorrente, novoNo);
        
        // novo no passa a ser o no corrente
        noCorrente = novoNo;   
    }
    printf("Arvore de expressao: ");
    arv_imprime(raiz);
    printf("\nresultado da arvore de expressao: %d\n ", calculate(raiz));
    return raiz;
} 

