/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/*
Júlia Affonso Figueiredo Rocha
1710635

LINK TO GCC ONLINE: https://onlinegdb.com/BJNIq1ZtU
 */


#include <stdio.h>
#include <stdlib.h>
#include "ShuntingYard.h"
#include "ExpressionTree.h"

#define MAX_SIZE 256

int main(void)
{
    printf("Entre com a expressão: \nPressione enter ao terminar...\n");
    printf("Operacoes aceitas: +, -, /, *\n");
    int k = -1;
    char *in = malloc (sizeof (MAX_SIZE));
    char get;
    scanf("%c", &get);
    while (get != '\n') {
        in[++k] = get;
        scanf("%c", &get);
    }
    in[++k] = '\0';
    printf("Expressão a ser calculada: %s\n", in);
    char* output = malloc(sizeof(in));
    inToPost(in, output);
    printf("notação em postfix: ");
    imprime_shuntingYard(output);
    postToTree(output);
    return 0;
}

/*
Obs: o uso de caracteres diferentes para as operacoes vai resultar em erro,
Atenção ao uso de caracteres especiais
Suas equivalencias:
x -> *
– -> -
% -> /
÷ -> / 
*/
