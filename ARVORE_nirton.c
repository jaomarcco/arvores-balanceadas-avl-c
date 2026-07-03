
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *esquerdo;
    struct No *direito;
    int altura;
} No;

int obterAltura(No *n) {
    if (n == NULL) return 0;
    return n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

No* novoNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1;
    return no;
}

No *rotacaoDireita(No *y) {
    No *x = y->esquerdo;
    No *T2 = x->direito;

    x->direito = y;
    y->esquerdo = T2;

    y->altura = max(obterAltura(y->esquerdo), obterAltura(y->direito)) + 1;
    x->altura = max(obterAltura(x->esquerdo), obterAltura(x->direito)) + 1;

    return x;
}

No *rotacaoEsquerda(No *x) {
    No *y = x->direito;
    No *T2 = y->esquerdo;

    y->esquerdo = x;
    x->direito = T2;

    x->altura = max(obterAltura(x->esquerdo), obterAltura(x->direito)) + 1;
    y->altura = max(obterAltura(y->esquerdo), obterAltura(y->direito)) + 1;

    return y;
}

int obterBalanceamento(No *n) {
    if (n == NULL) return 0;
    return obterAltura(n->esquerdo) - obterAltura(n->direito);
}

No* inserir(No* no, int chave) {
    if (no == NULL) return novoNo(chave);

    if (chave < no->chave)
        no->esquerdo = inserir(no->esquerdo, chave);
    else if (chave > no->chave)
        no->direito = inserir(no->direito, chave);
    else 
        return no;

    no->altura = 1 + max(obterAltura(no->esquerdo), obterAltura(no->direito));

    int fb = obterBalanceamento(no);

    if (fb > 1 && chave < no->esquerdo->chave)
        return rotacaoDireita(no);

    if (fb < -1 && chave > no->direito->chave)
        return rotacaoEsquerda(no);

    if (fb > 1 && chave > no->esquerdo->chave) {
        no->esquerdo = rotacaoEsquerda(no->esquerdo);
        return rotacaoDireita(no);
    }

    if (fb < -1 && chave < no->direito->chave) {
        no->direito = rotacaoDireita(no->direito);
        return rotacaoEsquerda(no);
    }

    return no;
}

void exibirEmOrdem(No *raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esquerdo);
        printf("%d (FB: %d) | ", raiz->chave, obterBalanceamento(raiz));
        exibirEmOrdem(raiz->direito);
    }
}

int main() {
    No *raiz = NULL;

    printf("--- Teste de Execucao da Arvore AVL ---\n");
    printf("Inserindo elementos que forcam desbalanceamento sucessivo: 10, 20, 30...\n\n");
    
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);

    printf("Estrutura da arvore apos balanceamento (Em-Ordem):\n");
    exibirEmOrdem(raiz);
    printf("\n\nNote que a raiz real agora se tornou o 20, mantendo a altura equilibrada!\n");

    return 0;
}
