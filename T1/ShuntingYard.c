
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "Pilha.h"
#include "ShuntingYard.h"

const char LEFT_PARENTESIS = '(';
const char RIGHT_PARENTESIS = ')';

// funcao auxiliar para precedencia de operacoes
int Prec (char input)
{
  if (input == '*' || input == '/')
    return 2;
  return 1;
}

// funcao auxiliar para identificacao de operador
int isOperand (char c)
{
  if (c == '-' || c == '+' || c == '/' || c == '*')
    return 1;
  return 0;
}

// funcao auxiliar para imprimir o shunting yard levando em consideracao numeros maiores do que 9
void imprime_shuntingYard(char* output) {
    int a;
    for(a=0; output[a]; ++a) {
        if (!isOperand(output[a])) {
            if (output[a]>= 97 && output[a]<107)
                printf("%d ", (int)(output[a]) - 87); // entre 10 e 19
            else 
                printf("%d ", (int)(output[a]) - '0'); 
        } else 
            printf("%c ", output[a]); 
    }
    printf("\n");
}


void inToPost (char *expression, char *output)
{
  Pilha *s = pilha_cria ();
  char *out = malloc (sizeof (expression));

  // enquanto a expressao for possivel de iterar 
  int i, k;
  for (i = 0, k = -1; expression[i]; ++i)
    {
        // tratamento de espaços em branco
        if (expression[i] == ' ')
            ++i;

        // se eh um operando 
        if (isOperand (expression[i]))
	    {
	            // enquanto existir um operando no topo da pilha e for com precedencia maior ou igual
	       while (!pilha_vazia (s) && Prec (expression[i]) < Prec (pilha_topo (s)) && pilha_topo(s) != LEFT_PARENTESIS)
		        out[++k] = pilha_pop (s);
	        // se nao, adiciona na pilha   
	        pilha_push (s, expression[i]);
	    }

        // se eh um parentesis aberto (, adiciona na pilha
        else if (expression[i] == LEFT_PARENTESIS)
	        pilha_push (s, expression[i]);

        // se eh um parentesis fechado ) 
        else if (expression[i] == RIGHT_PARENTESIS)
	    {
	        // enquanto o ( nao estiver no topo da pilha, adiciona na saida
	        while (!pilha_vazia (s) && pilha_topo (s) != LEFT_PARENTESIS)
	            out[++k] = pilha_pop (s);

	        // se nao acha o parentesis que fecha, a expressao eh invalida
	        if (!pilha_vazia (s) && pilha_topo (s) != LEFT_PARENTESIS)
	            return;		// expressao invalida              
	        else
	            // remove '(' da pilha 
	            pilha_pop (s);
	    }

        // eh um numero, adiciona na saida
        else
        {
	        // para numeros maiores que 9
	        if (!isOperand(expression[i]) &&
	            i < (strlen(expression) -1) &&
	            (!isOperand(expression[i + 1]) && expression[i + 1] != LEFT_PARENTESIS && expression[i + 1] != RIGHT_PARENTESIS && expression[i + 1] != ' '))
	           out[++k] = (int)expression[i] + (int)expression[++i];
	        else 
	           out[++k] = expression[i];
	    }

    }
    // adiciona os operadores restantes na pilha na saida
    while (!pilha_vazia (s))
        out[++k] = pilha_pop (s);

    out[++k] = '\0';
    strcpy (output, out);
    return;
}

/* Obs: numeros acima de 9 são tratados como char
e apenas convertidos a decimal no calculo da arvore de expressao
por conta do armazenamento em char usado pelo shunting yard 
*/
