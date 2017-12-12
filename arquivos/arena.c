#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void iniciaArena(int tamanho) {
	arena = malloc(sizeof(Arena));
	Celula **tabuleiro;
	int i,j;
	arena->tabuleiro = malloc (tamanho * sizeof(Celula *));
	for(i = 0; i < tamanho; i++){
		arena->tabuleiro[i] = malloc (tamanho * sizeof(Celula)); //inicializa as celulas do tabuleiro
		for (j = 0; j < tamanho; j++){
			arena->tabuleiro[i][j].base = 0;
			arena->tabuleiro[i][j].cristais = 0;
			arena->tabuleiro[i][j].ocupado = -1;
		}
	}
	arena->robos = malloc (10 * sizeof(Maquina *)); //inicializa o vetor de robos
	arena->tempo = 0;								//inicia o tempo 
	arena->nExercitos = 0;			
	arena->nRobos = 0;
	arena->tamanho = tamanho;
}

void destroiArena() {
	int i;
	for (i = 0; i < arena->tamanho; i++)
		free(arena->tabuleiro[i]);
	free(arena->tabuleiro);
	for (i = 0; i < arena->nRobos; i++)
		destroi_maquina(arena->robos[i]);
	free(arena->robos);
	free(arena);
}

int numAleatorio() {
	srand (time(NULL));
	return rand();
}

void escolheBase(int exercito) {
	int x,y;
	x = 0; // TODO: definir a base de um outro jeito
	y = 0;
	arena->bases[exercito].x = x;
	arena->bases[exercito].y = y;
	//printf("base do exercito %d (%d,%d)\n", exercito, x, y);
	arena->tabuleiro[x][y].base = exercito;
}

void insereExercito() {
	if (arena->nExercitos <= 5 ) {
		escolheBase(++arena->nExercitos);
	}
}

void insereRobo(Maquina *m, int exercito) {
	if (exercito <= arena->nExercitos) {
		Posicao p;
		arena->robos[arena->nRobos] = m;   										//insere a maquina no vetor de nRobos
		arena->robos[arena->nRobos]->exercito = exercito;						//atribui o exercito à maquina
		arena->robos[arena->nRobos]->vida = 10;									//atribui a vida à maquina
		arena->robos[arena->nRobos]->cristal = 0;								//atribui o numero de cristais carregado pela maquina
		arena->robos[arena->nRobos]->pos = arena->bases[exercito];				//atribui a posiçao do robo na base do exercito
		arena->robos[arena->nRobos]->id = arena->nRobos;						//define o id da maquina como o indice do vetor robos
		p = arena->robos[arena->nRobos]->pos;									//
		arena->tabuleiro[p.x][p.y].ocupado = arena->robos[arena->nRobos]->id;	//define a posição da maquina no tabuleiro como ocupada
		arena->nRobos++;
		//printf("Robo %d, vida: %d, cristais: %d \n", arena->nRobos - 1, arena->robos[arena->nRobos - 1]->vida, arena->robos[arena->nRobos - 1]->cristal);
	} else {
		printf("ERRO: exercito %d não existe \n", exercito);
	}
}

void removeRobo(int i) {
	free(arena->robos[i]); 
}

void Atualiza() {
	int i = 0;
	while (i < arena->nRobos) {
		if (arena->robos[i] != NULL)
			exec_maquina(arena->robos[i], 100);
		i++;
	}
	arena->tempo++;
}

void Sistema(Maquina *m, OPERANDO op){
	int x,y;
	switch(op.val.n){  
		case 0:
			x = -1;
			y = 0;
			break;
		case 1:
			x = -1;
			y = 1;
			break;
		case 2:
			x = 0;
			y = 1;
			break;
		case 3:
			x = 1;
			y = 0;
			break;
		case 4:
			x = 1;
			y = -1;
			break;
		case 5:
			x = 0;
			y = -1;
			break;
	}
	x = m->pos.x + x;
	y = m->pos.y + y;

	if (x >= 0 && x < arena->tamanho && y >= 0 && y < arena->tamanho){  //x e y dentro do tabuleiro
		switch(op.t) {
			case ATK: 
				printf("Ataca %d\n", op.val.n);
				if (arena->tabuleiro[x][y].ocupado >= 0){// verifica se ha algum robo nessa pos
					int id = arena->tabuleiro[x][y].ocupado;
					arena->robos[id]->vida--;
					if (arena->robos[id]->vida <= 0) 
						removeRobo(id);
				}
				break;
			case MOV:
				if (arena->tabuleiro[x][y].ocupado < 0){ //verifica se ha alguem na nova posicao
					printf("Move %d\n", op.val.n);
					arena->tabuleiro[m->pos.x][m->pos.y].ocupado = -1;
					arena->tabuleiro[x][y].ocupado = m->id;
					m->pos.x = x;
					m->pos.y = y;
					printf("new pos (%d,%d)\n", m->pos.x, m->pos.y);
				} else {
					printf("posição ocupada %d\n", arena->tabuleiro[x][y].ocupado);
				}
				break;
			case COL:
				if (arena->tabuleiro[m->pos.x][m->pos.y].cristais > 0){
					printf("Coleta cristal");
					arena->tabuleiro[m->pos.x][m->pos.y].cristais--;
					m->cristal++;
				} else {
					printf("Celula (%d,%d) não tem cristais\n", m->pos.x, m->pos.y);
				}
				break;

			case VER: //verifica se a celula (x,y) esta ocupada
				if (arena->tabuleiro[x][y].ocupado >= 0)
					empilha(&m->pil, (OPERANDO) {NUM, {arena->tabuleiro[x][y].ocupado}});
				printf("verifica (%d,%d)\n", x, y);
				break;
		}
	}
}