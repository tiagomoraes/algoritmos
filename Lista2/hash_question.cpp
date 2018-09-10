#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct arquivo {
    string nome;
    int id;

    // contructer for arquivo
    arquivo(string nome, int id) {
        this->nome = nome;
        this->id = id;
    }
};

struct Lista {
    struct node {
        arquivo *val;
        node *prev;
        node *next;

        node(arquivo *val) {
            this->val = val;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };

    typedef struct node* nodePtr;

    int size;

    nodePtr head;
    nodePtr tail;
    nodePtr cur;

    // constructor for the class
    Lista() {
        head = nullptr;
        tail = nullptr;
        cur = nullptr;
        size = 0;
    }

    // inserts new node on the tail
    void insert_tail(arquivo *val) {
        nodePtr n;
        n = new node(val);

        // check if list is empty
        if(this->tail == nullptr) {
            this->head = n;
        } else {
            this->tail->next = n;
            n->prev = this->tail;
        }
        this->tail = n;

        this->size++;
    }

    /*
    arquivo* remove(int id) {
        nodePtr cur;
        cur = this->head;

        while(cur != nullptr) {
            if(cur->val->id == id) {
                if(cur->next != nullptr) {
                    cur->next->prev = cur->prev;
                } else {
                    this->tail = cur->prev;
                }

                if(cur->prev != nullptr) {
                    cur->prev->next = cur->next;
                } else {
                    this->head = cur->next;
                }
                this->size--;
                return cur->val;

            } else {
                if(cur->next != nullptr) {
                    cur = cur->next;
                } else {
                    return nullptr;
                }
            }
        }
    }
    */

    int pos(string nome) {
        nodePtr cur;
        cur = this->head;

        int resp = 1;

        while(cur != nullptr) {
            if(cur->val->nome == nome) {
                return resp;
            } else {
                if(cur->next != nullptr) {
                    cur = cur->next;
                    resp++;
                } else {
                    return -1;
                }
            }
        }
    }

    void print() {
        nodePtr cur;
        cur = this->head;
        nodePtr aux;
        cout << "Printing list" << endl;
        cout << "Size: " << this->size << endl << endl;
        while(cur != nullptr) {
            cout << "arquivo" << endl;
            cout << "nome: " << cur->val->nome << endl;
            cout << "id: " << cur->val->id << endl;
            cur = cur->next;
        }
    }

    int length() {
        return this->size;
    }
};

struct hash_table {

    int filled;
    int size;
    Lista **table;

    hash_table(int size) {
        this->filled = 0;
        this->size = size;
        this->table = new Lista*[this->size];

        for(int i = 0; i < this->size; i++) {
            table[i] = new Lista();
        }
    }

    int hash_generate(string nome) {
        int key = 0;

        for(int i = 0; i < nome.length(); i++) {
            key += int((i+1)*(nome[i]));
        }

        int resp = key % this->size;
        return resp;
    }

    void insert(arquivo *val) {
        int hash_code = hash_generate(val->nome);
        table[hash_code]->insert_tail(val);
    }

    /*
    arquivo* remove(string nome) {
        int hash_code = hash_generate(nome);
        return table[hash_code]->remove(nome);
    }
    */

    int pos(string nome) {
        int hash_code = hash_generate(nome);
        return table[hash_code]->pos(nome);
    }

    void print() {
        for(int i = 0; i < size; i++) {
            cout << "Bucket[" << i << "]:" << endl;
            table[i]->print();
            cout << "----------------------" << endl;
        }
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numArquivos, idIn, quantGavetas, numTransf, idTransf, quantConsult;
    string nomeIn, nomeConsult;

    cin >> numArquivos;

    arquivo *arquivosAntigos[numArquivos];

    for(int i = 0; i < numArquivos; i++) {
        cin >> nomeIn;
        cin >> idIn;
        arquivosAntigos[i] = new arquivo(nomeIn, idIn);
    }

    cin >> quantGavetas;
    hash_table *gavetas = new hash_table(quantGavetas);

    cin >> numTransf;

    for(int i = 0; i < numTransf; i++) {
        cin >> idTransf;
        for(int j = 0; j < numArquivos; j++) {
            if(arquivosAntigos[j]->id == idTransf) {
                gavetas->insert(arquivosAntigos[j]);
            }
        }
    }

    for(int i = 0; i < quantGavetas; i++) {
        cout << i << ": " << gavetas->table[i]->size << endl;
    }

    cin >> quantConsult;
    for(int i = 0; i < quantConsult; i++) {
        cin >> nomeConsult;
        cout << i << ": " << gavetas->pos(nomeConsult) << endl;
    }

    return 0;
};
