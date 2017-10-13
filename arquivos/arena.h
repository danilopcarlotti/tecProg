#include "pilha.h"
#include <stdbool.h>

typedef struct {
  int posX;
  int posY;
  int tipoTerreno; // plano ou rugoso (custo de saída x3)
  int quantidadeDeCristais;
  int baseExercito; // se é base, tem um número do exército. Se não, 0.
  bool ocupado; // se a célula está ocupada por algum robô true. Se não, false.
} Celula;

typedef struct {
	Celula ** tabuleiro;
	int ** bases;
	int quantidadeDeExercitos;
	int ** exercitos;
	int unidadesTempo; // a cada jogada, passa-se uma unidade de tempo
	int quantidadeDeRobos;
} Arena;

void inicializaArena(Arena * are);

void inicializaMatriz(Celula ** matriz);

void escolheBaseArena(int Exercito, int * base,Arena * are);

void posicionaExercito(int Exercito,Arena * are);

int numeroAleatorio(int limite);