#include "pilha.h"

#define MAXMEM 100

typedef struct {
  int pos1[2];
  int pos2[2];
  int pos3[2];
  int pos4[2];
  int pos5[2];
  int pos6[2];
} Vizinhanca;

typedef struct {
  Pilha pil;
  Pilha exec;
  Pilha rbp;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int pos[2]; // posição na arena
  int exercito; //qual exercito pertence
  int cristais; // quantidade de cristais
  int saude;
  Vizinhanca * v;
  int ocupacao;
} Maquina;

Maquina *cria_maquina(INSTR *p, int exercito, int x, int y);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

void Sistema(Maquina *m, AC acao, int op);

Vizinhanca *cria_vizinhanca(int x, int y);
