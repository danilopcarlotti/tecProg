#include "maq.h"

typedef struct {
	Celula **tabuleiro;
	Posicao bases[6];
	Maquina **robos; // vetor de robos na arena
	int tempo; // a cada jogada, passa-se uma unidade de tempo
	int nRobos;
	int nExercitos;
	int tamanho;
} Arena;

Arena *arena;

void iniciaArena(int tamanho);

void destroiArena();

int numAleatorio();

void escolheBase(int exercito);

void insereExercito();

void insereRobo(Maquina *m, int exercito);

void Atualiza();