#include <stdio.h>
#include <stdlib.h>
#include "lib_racionais.h"

/* retorna um numero aleatorio entre min e max, inclusive.
 * a rigor esta funcao poderia estar em outro arquivo, mas
 * deixamos aqui para nao complicar demais
*/
int aleat (int min, int max)
{
    return min+rand()%(max+1-min); 
}

/* cria um racional sem valores atribuidos, so aloca o espaco */
racional *criar_r ()
{
    racional *r;

    r = malloc (sizeof(racional));
    if (r == NULL) 
            return NULL;
    return r;
}

/* libera a memoria de um racional alocado */
racional *liberar_r (racional *r){
    free(r);
    r = NULL;

    return r;
}

/* aloca espaço para um ponteiro para um racional contendo
 * numeros aleatorios no numerador e denominador.
 * Retorna o ponteiro para o racional simplificado. */
racional *sortear_r (){
    
    racional *s;

    s = malloc(sizeof(racional));
    s->num = aleat(0,100);
    s->den = aleat(0,100);

    simplifica_r(s);

    return s;
}

/* le um racional, retorna 1 em caso de sucesso ou 0 em caso de falha 
 * a qual pode ocorrer por uma entrada de racional invalido ou falha no scanf */
int ler_r (racional *r){
    
    int num, den;

    scanf("%d %d", &num, &den);

    r->num = num;
    r->den = den;

    if (valido_r) 
        return 1;
    return 0;

}

/* imprime um racional sem espaco em branco apos o numero e sem mudar de linha */
void imprimir_r (racional *r){
    
    if (r->num == 0) 
        printf("%d", r->num);
    printf("%d/%d ", r->num, r->den);
}

/* calcula o mdc pelo metodo de Euclides */
int mdc (int a, int b){
    int resto;

    if ((a!=0) && (b!=0)){
        resto=a%b;
        while (resto!=0){
            a=b;
            b=resto;
            resto=a%b;
        }
        return b;
    } else if (a==0) 
        return 1;
    return 0;
}

/* mmc = (a * b) / mdc (a, b) */
int mmc (int a, int b){
    
    int mmc, aux, i;

    for(i=2; i<=b; i++){
        aux = a*i;
        if(aux%b == 0){
            mmc=aux;
            i = b + 1;
        }
    }
    return mmc;
}

/* retorna 1 se o racional r eh valido ou 0 caso contrario */
int valido_r (racional *r){
     if (r->den == 0) 
        return 0;
    return r;
}

/* simplifica um racional para o menor denominador possivel */
/* caso o racional seja da forma n/n, retorna 1             */
void simplifica_r (racional *r){
    
    int resultado_mdc;

    resultado_mdc = mdc(r->num, r->den);
    
    
    r->num = r->num/resultado_mdc;
    r->den = r->den/resultado_mdc;
        
        if (r->num == r->den)
            return 1;
        else
            return r;
    
}

/* retorna 1 caso *r1 seja menor do que *r2 */
int menor_r (racional *r1, racional *r2){
    
    r1->num = r1->num*r2->den;
    r2->num = r2->num*r1->den;

    if (r1->num < r2->num)
        return r1->num;
    return r2->num;
}

/* retorna 1 caso os racionais *r1 e *r2 sejam iguais ou 0 caso contrario */
int iguais_r (racional *r1, racional *r){
    
    if(r1 == r)
        return 1;
    return 0;
}

/* soma dois racionais e devolve um ponteiro para o resultado */
/* retorna NULL em qualquer caso de falha                     */
racional *somar_r (racional *r1, racional *r2){

    racional *soma;
    int resultado_mmc;

    resultado_mmc = mmc;

    soma->num = r1->num*resultado_mmc + r2->num*resultado_mmc;
    soma->den = resultado_mmc;

    simplifica_r(soma);

    return soma;
}

/* subtrai dois racionais e devolve um ponteiro para o resultado */
/* retorna NULL em qualquer caso de falha                        */
racional *subtrair_r (racional *r1, racional *r2){

    racional *subtracao;
    int resultado_mmc;

    resultado_mmc = mmc;

    subtracao->num = r1->num*resultado_mmc - r2->num*resultado_mmc;
    subtracao->den = resultado_mmc;

    simplifica_r(subtracao);
    
    return subtracao;
}

/* multiplica dois racionais e devolve um ponteiro o resultado */
/* retorna NULL em qualquer caso de falha                      */
racional *multiplicar_r (racional *r1, racional *r2){

    racional *multiplica;

    multiplica->num = r1->num*r2->num;
    multiplica->den = r1->num*r2->den;

    simplifica_r(multiplica);

    return multiplica;    
}
/* divide dois racionais e devolve um ponteiro para resultado */
/* retorna NULL em qualquer caso de falha                     */
racional *dividir_r (racional *r1, racional *r2){

    racional *divide;

    divide->num = r1->num*r2->den;
    divide->den = r1->num*r2->num;

    simplifica_r(divide);

    return divide;
}

