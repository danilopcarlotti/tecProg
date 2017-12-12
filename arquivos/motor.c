#include <stdio.h>
#include "compila.tab.h"
#include "arena.h"

INSTR p1[2000];

int compilador(FILE *, INSTR *);

int main(int ac, char **av) {
  FILE *p = stdin;
  FILE *display;
  int res;
  display = popen("./apres", "w");
  if (display == NULL) {
  fprintf(stderr,"Não encontrei o programa de exibição\n");
  return 1;
  }
  ac --; av++;
  if (ac>0)
	p = fopen(*av,"r");
  res = compilador(p, p1);
  if (res) return 1;
  iniciaArena(5);
  insereExercito();
  Maquina *maq = cria_maquina(p1);
  //exec_maquina(maq, 1000);
  insereRobo(maq, 1, display);
  Atualiza();
  //destroi_maquina(maq);
  destroiArena();
  pclose(display);
  return 0;
}
