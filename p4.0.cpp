//Vithoria Cabreira 2410400
//Lucas de Lima Quaglia 2266466
//Pedro Augusto de Lima Oliveira 2417847

#include <iostream>
using namespace std;

//estrutura para o nó
struct No {
    int chave; //valor do nó
    int altura; //altura do nó
    No* esquerda;
    No* direita;

    No(int valor) : chave(valor), altura(1), esquerda(nullptr), direita(nullptr) {}
};

//Retorna a altura do nó
int obterAltura(No* no) {
    return no ? no->altura : 0;
} //Se for nulo ele vai retornar 0

//Calcula o fator de balanceamento da árvore
int obterBalanceamento(No* no) {
    return no ? obterAltura(no->esquerda) - obterAltura(no->direita) : 0;
}

//Atualiza a altura do nó
void atualizarAltura(No* no) {
    if (no)
        no->altura = 1 + max(obterAltura(no->esquerda), obterAltura(no->direita));
}

//Faz a rotação simples para a direita
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T = x->direita;

    x->direita = y;
    y->esquerda = T;

    atualizarAltura(y);
    atualizarAltura(x);

    cout << "RSD " << y->chave << endl;
    return x;
}

//Faz a rotação simples para a esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T = y->esquerda;

    y->esquerda = x;
    x->direita = T;

    atualizarAltura(x);
    atualizarAltura(y);

    cout << "RSE " << x->chave << endl;
    return y;
}

//Faz a rotação dupla para a direita
No* rotacaoDuplaDireita(No* z) {
    z->esquerda = rotacaoEsquerda(z->esquerda);
    return rotacaoDireita(z);
}

//Faz a rotação dupla para a esquerda
No* rotacaoDuplaEsquerda(No* z) {
    z->direita = rotacaoDireita(z->direita);
    return rotacaoEsquerda(z);
}

//Faz a inserção dos nós na árvore
No* inserir(No* no, int chave) {
    if (!no) return new No(chave);

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave);
    else if (chave > no->chave)
        no->direita = inserir(no->direita, chave);
    else
        return no;

    atualizarAltura(no);

    int balanceamento = obterBalanceamento(no);

    // Caso 1: Rotação simples à direita
    if (balanceamento > 1 && chave < no->esquerda->chave)
        return rotacaoDireita(no);

    // Caso 2: Rotação simples à esquerda
    if (balanceamento < -1 && chave > no->direita->chave)
        return rotacaoEsquerda(no);

    // Caso 3: Rotação dupla à direita
    if (balanceamento > 1 && chave > no->esquerda->chave) {
        cout << "RDD " << no->chave << endl;
        return rotacaoDuplaDireita(no);
    }

    // Caso 4: Rotação dupla à esquerda
    if (balanceamento < -1 && chave < no->direita->chave) {
        cout << "RDE " << no->chave << endl;
        return rotacaoDuplaEsquerda(no);
    }

    return no;
}

//Exclui a árvore
void excluirArvore(No* no) {
    if (!no) return;
    excluirArvore(no->esquerda);
    excluirArvore(no->direita);
    delete no;
}

int main() {
    No* raiz = nullptr;
    int valor;

    while (cin >> valor) {
        if (valor == -1) {
            cout << "fim" << endl;
            break;
        } else if (valor == 0) {
            if (raiz) {
                cout << "Bal= " << obterBalanceamento(raiz) << endl;
                excluirArvore(raiz);
                raiz = nullptr;
            }
        } else {
            raiz = inserir(raiz, valor);
        }
    }

    excluirArvore(raiz);
    return 0;
}
