//--------------------------------------------------------------
// NOME : Gabriel Medeiros Jospin
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

// ######### ESCREVA O NROUSP AQUI


#define NUMUSP 11796020
#define MAX 9999
#define WHITE 0
#define BLACK 1

int nroUSP() {
    return NUMUSP;
}



//-------------------------------------------

// nos das listas de adjacencias
typedef struct adj {
    int v;
    struct adj* prox;
} NO;

// vertices
typedef struct {
    NO* inicio;
} VERTICE;


// funcao principal
NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
void visita(VERTICE* graph, int position, int objective, int limit,
            int* color, NO* *iteration, NO* *temporaryList); //Visita o elemento e seus adjascentes

int addList(NO *Elem, NO **List); //Adiciona um elemento na lista
void addList(int vert, NO **list); //Cria um elemento de velor $vert e adiciona ma lista
void copyToList(NO* *recive, NO* *Demand);//Copia todos os elementos da lista demand pra recive
void removeLast(NO **list); //Remove o ultimo elemento da lista


void visita(VERTICE* graph, int position, int objective, int limit,
            int* color, NO* *iteration, NO* *temporaryList){

    if(limit < 0){
        return;
    }

    addList(position,temporaryList);
    color[position] = BLACK;

    if( position == objective){
        copyToList(iteration,temporaryList);
        removeLast(temporaryList);
        color[position] = WHITE;
        return;
    }

    NO* list = graph[position].inicio;

    while(list){
        int teste = color[list->v];
        if(teste == WHITE)
            visita(graph,list->v,objective,limit-1,color,iteration,temporaryList);
        list = list->prox;
    }

    color[position] = WHITE;
    removeLast(temporaryList);
}

void removeLast(NO **list) {
    if(!list)
        return;

    NO* back = NULL;
    NO* iteration = *list;

    while(iteration->prox){
        back = iteration;
        iteration=iteration->prox;
    }

    free(iteration);
    if(back)
        back->prox = NULL;
}


NO* caminhos_max_d(VERTICE* graph, int length, int x, int y, int limit)
{

    if(limit <= 0 || x <= 0 || y<=0){
        return NULL;
    }

    if(y > length)
        return NULL;


    NO* iteration = NULL;
    NO* temporaryList = NULL;
    int color[length];
    for(int i = 0; i<length; i++)
        color[i] = WHITE;


    visita(graph,x,y,limit,color,&iteration,&temporaryList);
    return iteration;
}

void copyToList(NO* *recive, NO* *Demand){
    NO* iterationD = *Demand;

    while(iterationD){
        addList(iterationD->v,recive);
        iterationD = iterationD->prox;
    }

}


void addList(int vert, NO **list){
    NO* noPosition = (NO*) malloc(sizeof(NO));
    noPosition->v = vert;
    noPosition->prox = NULL;
    addList(noPosition,list);
}


int addList(NO *Elem, NO **list) {
    if(!Elem)
        return 404.;

    if(! *list){
        *list = Elem;
        return 0;
    }

    NO* iteration = *list;
    while(iteration->prox)
        iteration = iteration->prox;

    iteration->prox = Elem;

    return 0;
}
