#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

// struct cointaining the name and id of the arquivo
struct arquivo {
    string nome;
    int id;

    // contructer for arquivo
    arquivo(string nome, int id) {
        this->nome = nome;
        this->id = id;
    }
};

// default linked_list struct (for the hash_table lists)
struct Lista {
    struct node {
        arquivo *val;
        node *prev;
        node *next;

        node(arquivo *val) {
            this->val = val;
            this->next = nullptr;
        }
    };

    typedef struct node* nodePtr;

    int size;

    nodePtr head;
    nodePtr tail;
    nodePtr cur;

    // constructor for the Lista
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
        }
        this->tail = n;

        this->size++;
    }

    // returns the position of some element based on the name
    int pos(string nome) {
        nodePtr cur;
        cur = this->head;

        int resp = 1; // first position is 1, not 0...

        while(cur != nullptr) {
            // if founds the elemnt
            if(cur->val->nome == nome) {
                return resp;
            } else {
                // if has next element
                if(cur->next != nullptr) {
                    cur = cur->next;
                    resp++;
                } else {
                    // return -1 for not found
                    return -1;
                }
            }
        }
    }

    // just returns the length of the Lista
    int length() {
        return this->size;
    }
};

// hash_table struct (doesn't have the rehashin function, however it is simple to add, just creating a new hash_table)
struct hash_table {

    // int filled; (would use for seeing the 'capacidade de carga')
    int size;
    Lista **table;

    // constructor for the hash_table
    hash_table(int size) {
        // this->filled = 0;
        this->size = size;
        this->table = new Lista*[this->size];

        // sets each table position as a new Lista;
        for(int i = 0; i < this->size; i++) {
            table[i] = new Lista();
        }
    }

    // gets the file name and returns the hash_code
    int hash_generate(string nome) {
        int key = 0;

        for(int i = 0; i < nome.length(); i++) {
            key += int((i+1)*(nome[i]));
        }

        int resp = key % this->size;
        return resp;
    }

    // inserts an arquivo on its tabe position in the end of the Lista
    void insert(arquivo *val) {
        int hash_code = hash_generate(val->nome);
        table[hash_code]->insert_tail(val);
    }

    // returns the position (based on the Lista pos() function)
    int pos(string nome) {
        int hash_code = hash_generate(nome);
        return table[hash_code]->pos(nome);
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numArquivos, idIn, quantGavetas, numTransf, idTransf, quantConsult;
    string nomeIn, nomeConsult;

    cin >> numArquivos;

    arquivo *arquivosAntigos[numArquivos];

    // fills an array with all the initila arquivos
    for(int i = 0; i < numArquivos; i++) {
        cin >> nomeIn;
        cin >> idIn;
        arquivosAntigos[i] = new arquivo(nomeIn, idIn);
    }

    // creates a hash_table qithe the desired size (number of gavetas)
    cin >> quantGavetas;
    hash_table *gavetas = new hash_table(quantGavetas);

    cin >> numTransf;

    // transfers the arquivos for their gavetas based on its names
    // --------- Como etá ordenado, implementar uma busca binária para achar o arquivo correto -----------
    for(int i = 0; i < numTransf; i++) {
        cin >> idTransf;

        int l, r, m;
        l = 0;
        r = numArquivos-1;

        while(l <= r) {
            m = floor((l+r)/2);
            if(idTransf == arquivosAntigos[m]->id) {
                gavetas->insert(arquivosAntigos[m]);
                break;
            } else if(idTransf < arquivosAntigos[m]->id) {
                r = m-1;
            } else {
                l = m+1;
            }
        }
    }

    // prints the amount of arquivos on each gaveta
    for(int i = 0; i < quantGavetas; i++) {
        cout << i << ": " << gavetas->table[i]->size << endl;
    }

    // prints the position of the arquivos based on their nomes
    cin >> quantConsult;
    for(int i = 0; i < quantConsult; i++) {
        cin >> nomeConsult;
        cout << i << ": " << gavetas->pos(nomeConsult) << endl;
    }

    return 0;
};
