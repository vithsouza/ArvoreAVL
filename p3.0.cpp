//Vithoria Cabreira 2410400
//Lucas de Lima Quaglia 2266466
//Pedro Augusto de Lima Oliveira 2417847

#include <iostream>
using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int val) : key(val), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void updateHeight(Node* node) {
    if (node)
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    cout << "RSD " << y->key << endl;
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    cout << "RSE " << x->key << endl;
    return y;
}

Node* rotateDoubleRight(Node* z) {
    z->left = rotateLeft(z->left);
    return rotateRight(z);
}

Node* rotateDoubleLeft(Node* z) {
    z->right = rotateRight(z->right);
    return rotateLeft(z);
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; 

    updateHeight(node);

    int balance = getBalance(node);

    // Caso 1: Rotação simples à direita
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Caso 2: Rotação simples à esquerda
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Caso 3: Rotação dupla à direita
    if (balance > 1 && key > node->left->key) {
        cout << "RDD " << node->key << endl;
        return rotateDoubleRight(node);
    }

    // Caso 4: Rotação dupla à esquerda
    if (balance < -1 && key < node->right->key) {
        cout << "RDE " << node->key << endl;
        return rotateDoubleLeft(node);
    }

    return node;
}

void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    Node* root = nullptr;
    int value;

    while (cin >> value) {
        if (value == -1) {
            cout << "fim" << endl;
            break;
        } else if (value == 0) {
            if (root) {
                cout << "Bal= " << getBalance(root) << endl;
                deleteTree(root);
                root = nullptr;
            }
        } else {
            root = insert(root, value);
        }
    }

    deleteTree(root);
    return 0;
}
