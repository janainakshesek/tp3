#include <stdio.h>
#include <stdlib.h>
#include "lib_racionais.h"
#define MAX 100

/* le um inteiro na faixa [0..MAX-1] */
int ler_tamanho ()
{
    int tam;
    scanf("%d", &tam);
    return tam;
}

/* imprime os racionais apontados pelo vetor de ponteiros para racionais */
void imprimir_vetor_racional (racional **w, int tam)
{
    int i;
    
    for(i=0; i<tam;i++){
        imprimir_r(w[i]); 
    }
    printf("\n");
}

/* retorna um vetor de tam ponteiros para numeros racionais validos gerados aleatoriamente */
/* retorna NULL em caso de falha                                                           */
racional** aleatorio_vetor_racional (int tam)
{
    racional **v;
    int i;

    v = malloc(tam*sizeof(racional));

    for(i=0; i<tam; i++)
        v[i] = sortear_r();
     
    return v;
}

/* retorna um vetor de tam ponteiros para numeros racionais que apontam em ordem crescente para os 
 * racionais apontados pelo vetor recebido no parametro. Defina outras funcoes para te ajudar caso
 * ache necessario */
racional** ordenar_vetor_racional (racional **v, int tam)
{
    int i, j, menor;
    racional *aux, **ordenado;

    ordenado = malloc(tam*sizeof(racional));

    for(i=0; i<tam; i++)
        ordenado[i] = v[i];

    for(j=0; j<tam; j++){
        menor = j;
      
        for(i=j+1; i<tam; i++) {
            if(menor_r(ordenado[i], ordenado[menor])==1)
                menor = i;
        }

        aux = ordenado[j];
        ordenado[j] = ordenado[menor];
        ordenado[menor] = aux;
    }
    return ordenado;
}

int main ()
{
    racional **v, **w;
    /* v e w são vetores de ponteiros para racionais (racional *)
       alternativamente poderia ser declarado como racional *v[] */
    
    int tam, i;

    /* inicializa semente randomica                            */
    /* o parametro eh 0 para facilitar os testes               */
    /* depois pode trocar para, por exemplo, srand (time (0)); */
    srand (0);

    /* ler o tamanho do vetor de racionais */
    tam = ler_tamanho ();

    /* aloca v com tam ponteiros para racional */
    v = aleatorio_vetor_racional (tam);
    /*  lembre-se que a funcao acima retorna NULL em caso de falha */

    /* chama a funcao para ordenar o vetor */
    w = ordenar_vetor_racional (v, tam); 
    /*  lembre-se que a funcao acima retorna 0 em caso de falha */

    /* imprime o vetor ordenado */
    imprimir_vetor_racional (w, tam);

    /* libera toda memoria alocada dinamicamente        */
    /* nao esqueca de testar com valgrind para conferir */
    /* coloque aqui seu codigo */

    for (i=0; i<tam; i++)
        liberar_r(w[i]);

    free(w);
    w=NULL;
    free(v);
    v=NULL; 

    return 0;
}
