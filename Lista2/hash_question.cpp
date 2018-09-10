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

    arquivo* remove(string nome) {
        nodePtr cur;
        cur = this->head;

        while(cur != nullptr) {
            if(cur->val->nome == nome) {
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

    void rehash() {
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

    arquivo* remove(string nome) {
        int hash_code = hash_generate(nome);
        return table[hash_code]->remove(nome);
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

    /*
    Lista *a = new Lista();
    arquivo *f1 = new arquivo("Arquivo 1", 11);
    arquivo *f2 = new arquivo("Arquivo 2", 22);
    arquivo *f3 = new arquivo("Arquivo 3", 33);
    arquivo *f4 = new arquivo("Arquivo 4", 44);

    a->insert_tail(f1);
    a->insert_tail(f2);
    a->insert_tail(f3);
    a->insert_tail(f4);

    a->remove("Arquivo 2");
    a->remove("Arquivo 3");
    a->remove("Arquivo");

    a->print();
    */

    arquivo *f1 = new arquivo("Arquivo 1", 11);
    arquivo *f2 = new arquivo("Arquivo 2", 22);
    arquivo *f3 = new arquivo("Arquivo 3", 33);
    arquivo *f4 = new arquivo("Arquivo 4", 44);

    hash_table *a = new hash_table(10);

    a->insert(f1);
    a->insert(f2);
    a->insert(f3);
    a->remove("Arquivo 2");
    a->print();


    return 0;
};
