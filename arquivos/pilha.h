#include <stdio.h>
#include "instr.h"
#define PILMAX 99

typedef struct {
  int topo;
  OPERANDO val[PILMAX+1];
} Pilha;

Pilha *cria_pilha();
void destroi_pilha(Pilha *p);
void empilha(Pilha *p, OPERANDO op);
void empilhaInt(Pilha *p, int i);
OPERANDO desempilha(Pilha *p);
void imprime(Pilha *p, int n);
