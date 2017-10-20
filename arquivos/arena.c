#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arena.h"
#define TAMANHOARENA 6

int main(int argc, char const *argv[])
{
	Arena * are;
	are = malloc(sizeof(Arena));
	inicializaArena(are);
	return 0;
}

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
			cell[j].tipoTerreno = 0;
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

void escolheBaseArena(int Exercito, int * base)
{
	base[0] = numeroAleatorio(TAMANHOARENA);
	base[1] = numeroAleatorio(TAMANHOARENA);
}

void inicializaArena(Arena * are)
{
	are->tabuleiro = malloc(TAMANHOARENA * sizeof(Celula *));
	are->quantidadeDeRobos = 0;
	are->robos = malloc(100 * sizeof(Maquina));
	are->unidadesTempo = 0;
	inicializaMatriz(are->tabuleiro);
}

void InsereExercito(Maquina *m, Arena *are)
{
	are->robos[quantidadeDeRobos] = m;
	are->quantidadeDeRobos++;
}

void Atualiza(Arena *are)
{
	int i = 0;
	while(are->robos[i] != NULL){
		exec_maquina(are->robos[i], 50); // percorre o vetor de maquinas e executa 50 instruçoes
	}
	are->unidadesTempo++; // atualiza a contagem do tempo
}