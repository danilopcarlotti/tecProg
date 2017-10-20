#include "pilha.h"

#define MAXMEM 100

typedef struct {
  Pilha pil;
  Pilha exec;
  Pilha rbp;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int pos[2]; // posição na arena
  int cristais; // quantidade de cristais
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);
