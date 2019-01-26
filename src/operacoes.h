#ifndef OPERACOES_H
#define OPERACOES_H

#include <iostream>

#include "fila.h"
#include "node.h"

using namespace std;

bool insere(fila &a, int valor){

    nodePtr p = new node;
    p->info = valor;
    p->next = NULL;

    if(a.header == NULL)
    {
        a.header = p;
        return true;
    }
    else
    {
        nodePtr aux;
        aux = a.header;

        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        aux->next = p;
        return true;
    }

}

bool remove(fila &a){

    if(a.header == NULL)
    {
        return false;
    }

    nodePtr aux;
    aux = a.header->next;

    delete a.header;
    a.header = aux;

    return true;
}

int tamanho(fila &a){
	if(a.header == NULL){
		return 0;
	}

	int i = 0;
	nodePtr aux;
	aux = a.header;

	while(aux != NULL){
		aux = aux->next;
		i++;
	}
	return i;
}

bool compara(fila a, fila b){
    int i = 1;

    nodePtr aux1 = a.header;
    nodePtr aux2 = b.header;

    while(i == 1){
        if(aux1 == NULL && aux2 == NULL){
            return true;
        }
        if(aux1 == NULL && aux2 != NULL){
            return false;
        }
        if(aux2 == NULL && aux1 != NULL){
            return false;
        }
        if(aux1->info != aux2->info){
            return false;
        }
        aux1 = aux1->next;
        aux2 = aux2->next;
    }
}

// para essas funçoes: quando a variavel i mudar de valor (0 ou 1), um dos valores do RGB ira mudar para que a cor "pisque" na interface
int vermelhopiscar(int i){
	if(i == 0){
		return 200;
	}
	if(i == 1){
		return 255;
	}
}
int verdepiscar(int i){
	if(i == 0){
		return 100;
	}
	if(i == 1){
		return 155;
	}
}
int amarelopiscar(int i){
	if(i == 0){
		return 0;
	}
	if(i == 1){
		return 150;
	}
}
int azulpiscar(int i){

	if(i == 0){
		return 100;
	}
	if(i == 1){
		return 155;
	}
}

#endif
