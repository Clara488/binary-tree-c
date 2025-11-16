#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

struct arv {
    tno *raiz;
};

struct no {
    int chave;
    tno *esq;
    tno *dir;
};

tarv *criaArvore() {
    tarv *arv = (tarv*) malloc(sizeof(tarv));
    if (arv)
        arv->raiz = NULL;
    return arv;
}

tno *criaNo(int chave) {
    tno *no = (tno*) malloc(sizeof(tno));
    if (no) {
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
    }
    return no;
}

void insereNo(tarv *arv, tno *no) {
    if (!arv->raiz) {
        arv->raiz = no;
        return;
    }

    tno *aux = arv->raiz;
    tno *pai = NULL;

    while (aux) {
        pai = aux;
        if (no->chave < aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    if (no->chave < pai->chave)
        pai->esq = no;
    else
        pai->dir = no;
}

int carregaArvore(tarv *arv, char nomeArq[]) {
    FILE *arq = fopen(nomeArq, "r");
    if (!arq)
        return -1;

    int chave;
    while (fscanf(arq, "%d", &chave) == 1) {
        tno *no = criaNo(chave);
        if (!no)
            return -1;
        insereNo(arv, no);
    }

    fclose(arq);
    return 1;
}

// Percursos
void percorrePreOrdem(tno *no) {
    if (!no) return;
    printf("%d ", no->chave);
    percorrePreOrdem(no->esq);
    percorrePreOrdem(no->dir);
}

void percorreEmOrdem(tno *no) {
    if (!no) return;
    percorreEmOrdem(no->esq);
    printf("%d ", no->chave);
    percorreEmOrdem(no->dir);
}

void percorrePosOrdem(tno *no) {
    if (!no) return;
    percorrePosOrdem(no->esq);
    percorrePosOrdem(no->dir);
    printf("%d ", no->chave);
}

// Acesso
tno *getRaiz(tarv *arv) {
    return arv->raiz;
}

tno *getValor(tarv *arv, int valor) {
    tno *aux = arv->raiz;
    while (aux && aux->chave != valor) {
        if (valor < aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    return aux;
}

// Propriedades
int alturaArvore(tno *no) {
    if (!no)
        return -1;
    int altEsq = 1 + alturaArvore(no->esq);
    int altDir = 1 + alturaArvore(no->dir);
    return (altEsq > altDir ? altEsq : altDir);
}

int noSucessor(tno *no) {
    if (!no || !no->dir)
        return -1;
    tno *aux = no->dir;
    while (aux->esq)
        aux = aux->esq;
    return aux->chave;
}

int noPredecessor(tno *no) {
    if (!no || !no->esq)
        return -1;
    tno *aux = no->esq;
    while (aux->dir)
        aux = aux->dir;
    return aux->chave;
}

int maiorValor(tno *no) {
    if (!no)
        return -1;
    while (no->dir)
        no = no->dir;
    return no->chave;
}

int menorValor(tno *no) {
    if (!no)
        return -1;
    while (no->esq)
        no = no->esq;
    return no->chave;
}

// Contagens
int nosFolhas(tno *no) {
    if (!no) return 0;
    if (!no->esq && !no->dir) return 1;
    return nosFolhas(no->esq) + nosFolhas(no->dir);
}

int nosInternos(tno *no) {
    if (!no) return 0;
    if (!no->esq && !no->dir) return 0;
    return 1 + nosInternos(no->esq) + nosInternos(no->dir);
}

// Verificações
int verificaBinaria(tno *no) {
    if (!no) return 1;
    if ((no->esq && !no->dir) || (!no->esq && no->dir))
        return 0;
    return verificaBinaria(no->esq) && verificaBinaria(no->dir);
}

int cheiaAux(tno *no, int nivel, int h) {
    if (!no)
        return 1;

    if (!no->esq && !no->dir)
        return (nivel == h);

    if (!no->esq || !no->dir)
        return 0;

    return cheiaAux(no->esq, nivel + 1, h) &&
           cheiaAux(no->dir, nivel + 1, h);
}

int verificaCheia(tno *no) {
    if (!verificaBinaria(no))
        return 0;
    int h = alturaArvore(no);
    return cheiaAux(no, 0, h);
}
