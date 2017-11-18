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
  int saude;
  int exercito;
  Vizinhanca v;
  int ocupacao
} Maquina;

typedef struct {
  int pos1[2];
  int pos2[2];
  int pos3[2];
  int pos4[2];
  int pos5[2];
  int pos6[2]
} Vizinhanca

Maquina *cria_maquina(INSTR *p, int x, int y, int exercito);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

Vizinhanca *cria_vizinhanca(int x, int y);
