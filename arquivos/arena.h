#include "maq.h"
#include <stdbool.h>

typedef struct {
	int x;
	int y;
} Base;

typedef struct {
  int pos[2];
  int tipoTerreno; // plano ou rugoso (custo de saída x3)
  int quantidadeDeCristais;
  int baseExercito; // se é base, tem um número do exército. Se não, 0.
  bool ocupado; // se a célula está ocupada por algum robô true. Se não, false.
  Maquina *robo;
} Celula;

typedef struct {
	Celula ** tabuleiro;
	Base* bases;
	Maquina **robos; // vetor de robos na arena
	int unidadesTempo; // a cada jogada, passa-se uma unidade de tempo
	int quantidadeDeRobos;
	int quantidadeDeExercitos;
} Arena;

Arena *arena;
FILE *display;

void inicializaArena(Arena * are);

void inicializaMatriz(Celula ** matriz);

void escolheBaseArena(int Exercito, Arena * are);

int numeroAleatorio(int limite);

void Atualiza(Arena *are);

void InsereRobo(Arena *are, Maquina *m);

void InsereExercito(Arena *are);

void RemoveExercito(Maquina *m);

void insereCristais(int n, int x, int y, Arena *are);

void mostra_terreno(FILE *display, Celula * cell);

void mostra_robo(Maquina *m);

void mostra_cristais(int x, int y);