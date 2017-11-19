#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arena.h"
#define TAMANHOARENA 6

void inicializaMatriz(Celula ** matriz)
{
	for (int i = 0; i < TAMANHOARENA; ++i)
	{
		Celula * cell;
		cell = malloc(TAMANHOARENA * sizeof(Celula));
		matriz[i] = cell;
		for (int j = 0; j < TAMANHOARENA; ++j)
		{
			cell[j].pos[0] = i;
			cell[j].pos[1] = j;
			cell[j].tipoTerreno = numeroAleatorio(1); // 0 - terreno plano e 1 - terreno rugoso;
			cell[j].quantidadeDeCristais = 0;
			cell[j].baseExercito = -1;
			cell[j].ocupado = false;
		}
	}
}

int numeroAleatorio(int limite)
{
	srand (time(NULL));
	return rand() % limite;
}

void escolheBaseArena(int exercito, Arena *are)
{
	int x, y;
	x = numeroAleatorio(TAMANHOARENA);
	y = numeroAleatorio(TAMANHOARENA);
	if (are->tabuleiro[x][y].baseExercito < 0){
		are->tabuleiro[x][y].baseExercito = exercito;
		are->bases[exercito].x = x;
		are->bases[exercito].y = y;
	}
}

void inicializaArena(Arena * are)
{
	are->tabuleiro = malloc(TAMANHOARENA * sizeof(Celula *));
	are->quantidadeDeRobos = 0;
	are->robos = malloc(100 * sizeof(Maquina *));
	int i = 0;
	are->unidadesTempo = 0;
	are->bases = malloc(6 * sizeof(Base));
	are->quantidadeDeExercitos = 0;
	inicializaMatriz(are->tabuleiro);
	for (int i = 0; i < TAMANHOARENA; ++i)
	{
		for (int j = 0; j < TAMANHOARENA; ++j)
		{
			insereCristais(numeroAleatorio(4), i, j, are);
		}
	]
}

void InsereRobo(Arena *are, Maquina *m)
{
	are->robos[are->quantidadeDeRobos] = m;
	are->quantidadeDeRobos++;
}

void InsereExercito(Arena *are) 
{
	if (are->quantidadeDeExercitos < 5){
		escolheBaseArena(are->quantidadeDeExercitos, are);
		are->quantidadeDeExercitos++;
	}
}

void Atualiza(Arena *are)
{
	int i = 0;
	while(i <= are->quantidadeDeRobos){
		if (are->robos[i]->ocupacao != 0) {
		exec_maquina(are->robos[i], 0);
		}
		else{
		exec_maquina(are->robos[i], 50); // percorre o vetor de maquinas e executa 50 instruçoes
		}
		i++;
	}
	are->unidadesTempo++; // atualiza a contagem do tempo
}

void Sistema(Maquina *m, AC acao, int op){
	int x,y;
	switch(op){
		case 0:
			x = -1;
			y = -1;
			break;
		case 1:
			x = -1;
			y = 0;
			break;
		case 2:
			x = -1;
			y = 1;
			break;
		case 3:
			x = 0;
			y = 1;
			break;
		case 4:
			x = -1;
			y = 0;
			break;
		case 5:
			x = 0;
			y = -1;
			break;
	}
	x = m->pos[0] + x;
	y = m->pos[1] + y;

	switch(acao){
		case MOVER:
			if (!arena->tabuleiro[x][y].ocupado){
				arena->tabuleiro[m->pos[0]][m->pos[1]].ocupado = false;
				m->pos[0] = x;
				m->pos[1] = y;
				arena->tabuleiro[x][y].ocupado = true;
				arena->tabuleiro[x][y].robo = m;
			}
			break;
		case COLETAR:
			if (arena->tabuleiro[x][y].quantidadeDeCristais > 0){
				m->cristais++;
				arena->tabuleiro[x][y].quantidadeDeCristais--;
			}
			break;
		case ATACAR:

			break;
	}

}

void insereCristais(int n, int x, int y, Arena *are)
{
	are->tabuleiro[x][y].quantidadeDeCristais = n;
}