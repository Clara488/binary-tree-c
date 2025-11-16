#ifndef ARVORE_H
#define ARVORE_H

typedef struct arv tarv;
typedef struct no tno;

// Estrutura da árvore e dos nós
tarv *criaArvore();
tno *criaNo(int chave);

// Operações principais
void insereNo(tarv *arv, tno *no);
int carregaArvore(tarv *arv, char nomeArq[]);

// Percursos
void percorrePreOrdem(tno *no);
void percorreEmOrdem(tno *no);
void percorrePosOrdem(tno *no);

// Acesso
tno *getRaiz(tarv *arv);
tno *getValor(tarv *arv, int valor);

// Propriedades
int alturaArvore(tno *no);
int noSucessor(tno *no);
int noPredecessor(tno *no);
int maiorValor(tno *no);
int menorValor(tno *no);

// Contagens
int nosFolhas(tno *no);
int nosInternos(tno *no);

// Verificações
int verificaBinaria(tno *no);
int verificaCheia(tno *no);

// Funções auxiliares
int internosAux(tno *no);
int cheiaAux(tno *no, int nivel, int h);

#endif
