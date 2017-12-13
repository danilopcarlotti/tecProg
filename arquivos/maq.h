#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXMEM 100
#define MAXFRM 30

typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int bp[MAXFRM];
  int ib;
  Posicao pos;
  int exercito;
  int vida;
  int cristal;
  int id;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n, FILE *display);

int new_frame(Maquina *m, int pos);

int del_frame(Maquina *m);

void Sistema(Maquina *m, OPERANDO op, FILE *display);
