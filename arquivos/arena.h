#include "maq.h"
#include <stdio.h>

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

void escolheBase(int exercito, FILE *display);

void insereExercito(FILE *display);

void insereRobo(Maquina *m, int exercito, FILE *display);

void Atualiza();

void exibe_img(int ri, FILE *display, int tipo);