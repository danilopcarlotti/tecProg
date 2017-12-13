#include <stdio.h>
#include <stdlib.h>
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

void iniciaArena(int tamanho, FILE *display);

void destroiArena();

int numAleatorio();

void escolheBase(int exercito, FILE *display);

void insereExercito(FILE *display);

void insereRobo(Maquina *m, int exercito, FILE *display);

void Atualiza(FILE *display);

void exibe_robo(int ri, FILE *display);

int insereCristais(int n, int x, int y, FILE *display);

void exibe_cristais(int x, int y, FILE *display);

void exibe_base(int x, int y, FILE *display);

void exibe_vazio(int x, int y, FILE *display);

