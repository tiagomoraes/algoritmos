#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

//PROCESSO STRUCT
struct processo {
    int magistradoPref, tempo;

    // constructor for struct processo
    processo(int magistradoPref, int tempo) {
        this->magistradoPref = magistradoPref;
        this->tempo = tempo;
    }
};

//NODE STRUCT
struct node {
    processo *val;
    node *prev;
    node *next;

    node(processo *val) {
        this->val = val;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

// defines a node* as nodePtr for easy use
typedef struct node* nodePtr;

// PILHA STRUCT
struct Pilha {
    int size;

    nodePtr head;
    nodePtr tail;
    nodePtr cur;

    // constructor for the class
    Pilha() {
        head = nullptr;
        tail = nullptr;
        cur = nullptr;
        size = 0;
    }

    // inserts new node on the head
    void insert_head(processo *val) {
        nodePtr n;
        n = new node(val);

        // check if list is empty
        if(this->head == nullptr) {
            this->tail = n;
        } else {
            this->head->prev = n;
            n->next = this->head;
        }
        this->head = n;

        this->size++;
    }

    processo* remove_head() {
        if(this->head != nullptr) {
            processo *p = this->head->val;
            if(this->head->next != nullptr) {
                this->head->next->prev = nullptr;
            }
            this->head = this->head->next;
            this->size--;
            return p;
        } else {
            return nullptr;
        }
    }

    void print() {
        nodePtr cur;
        cur = this->head;
        nodePtr aux;
        while(cur != nullptr) {
            cout << "Processo" << endl;
            cout << "M:" << cur->val->magistradoPref << endl;
            cout << "T:" << cur->val->tempo << endl << endl;
            cur = cur->next;
        }
    }

    int length() {
        return this->size;
    }
};

// FILA STRUCT
struct Fila {
    int size;

    nodePtr head;
    nodePtr tail;
    nodePtr cur;

    // constructor for the class
    Fila() {
        head = nullptr;
        tail = nullptr;
        cur = nullptr;
        size = 0;
    }

    // inserts new node on the tail
    void insert_tail(processo *val) {
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

    processo* remove_head() {
        if(this->head != nullptr) {
            processo *p = this->head->val;
            if(this->head->next != nullptr) {
                this->head->next->prev = nullptr;
            }
            this->head = this->head->next;
            this->size--;
            return p;
        } else {
            return nullptr;
        }
    }

    void print() {
        nodePtr cur;
        cur = this->head;
       nodePtr aux;
        while(cur != nullptr) {
            cout << "M:" << cur->val->magistradoPref << endl;
            cout << "T:" << cur->val->tempo << endl;
            cur = cur->next;
        }
    }

    int length() {
        return this->size;
    }
};

//MAGISTRADO STRUCT
struct magistrado {
    Pilha *pilha;
    int horasDia;

    magistrado(int horasDia) {
        this->horasDia = horasDia;
        this->pilha = new Pilha();
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numEmpresas;
    cin >> numEmpresas;

    Fila *arrFilas[numEmpresas];

    int numProcessos;

    for(int i = 0; i < numEmpresas; i++) {
        arrFilas[i] = new Fila();

        cin >> numProcessos;

        for(int j = 0; j < numProcessos; j++) {
            int magistradoPref, tempoNec;
            cin >> magistradoPref;
            cin >> tempoNec;

            processo *p = new processo(magistradoPref, tempoNec);

            arrFilas[i]->insert_tail(p);
        }
    }

    int m;
    cin >> m;

    // array of int containing the magistrados(i) and hours
    magistrado *arrMagistrados[m];
    for(int i = 0; i < m; i++) {
        int horasDia;
        cin >> horasDia;
        arrMagistrados[i] = new magistrado(horasDia);
    }

    int totalProcessos = 0;
    for(int i = 0; i < numEmpresas; i++) {
        totalProcessos += arrFilas[i]->length();
    }


    int cont1 = 0;
    int cont2 = 0;
    // loop for distributing the processos between the magistrados
    for(int i = 0; i < totalProcessos; i++) {
        while(arrFilas[cont1]->length() <= 0) {
            if(cont1 == numEmpresas-1) {
                cont1 = 0;
            } else {
                cont1++;
            }
        }
        processo *p = arrFilas[cont1]->remove_head();
        arrMagistrados[cont2]->pilha->insert_head(p);

        if(cont1 == numEmpresas-1) {
            cont1 = 0;
        } else {
            cont1++;
        }

        if(cont2 == m-1) {
            cont2 = 0;
        } else {
            cont2++;
        }
    }


    for(int i = 0; i < m; i++) {
        arrMagistrados[i]->pilha->print();
    }

    return 0;
}


/*
//PROCESSO STRUCT
struct Processo {
    int magistrado, tempo;

    // constructor for struct processo
    Processo(int magistrado, int tempo) {
        this->magistrado = magistrado;
        this->tempo = tempo;
    }
}

// PILHA STRUCT
struct Pilha {
    struct node {

        processo val;
        node *prev;
        node *next;

        // constructor for struct node
        node(processo *val) : val(val), prev(nullptr), next(nullptr) {}
    };

    // defines a node* as nodePtr for easy use
    typedef struct node* nodePtr;

    int size;

    nodePtr head;
    nodePtr tail;
    nodePtr cur;
    nodePtr aux;

    // constructor for the class
    Pilha() {
        head = nullptr;
        tail = nullptr;
        cur = nullptr;
        size = 0;
    }

    // inserts new node on the head
    void insert_head(processo *val) {
        nodePtr n;
        n = new node(val);

        // check if list is empty
        if(this->head == nullptr) {
            this->tail = n;
        } else {
            this->head->prev = n;
            n->next = this->head;
        }
        this->head = n;

        this->size++;
    }

    bool remove_head() {
        if(this->head != nullptr) {
            this->head->next->prev = nullptr;
            this->head = this->head->next;
            this->size--
            return true;
        } else {
            return false;
        }
    }

    void print() {
        nodePtr cur;
        cur = this->head;

        while(cur != nullptr) {
            cout << "M:" << cur->val->magistrado << endl;
            cout << "T:" << cur->val->tempo << endl;

            cur = cur->next;
        }
    }

    // inserts new node on the tail
    void insert_tail(processo *val) {
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




    bool remove_tail() {
        if(this->tail != nullptr) {
            this->tail->prev->next = nullptr;
            this->tail = this->tail->prev;
            this->size--;
            return true;
        } else {
            return false;
        }
    }

    bool list_removeOne(processo val) {

        nodePtr cur;
        cur = head;

        //goes until the end of the list
        while (cur != nullptr) {
            if(cur->val == val) {

                // check if the elemnt is the first
                if(cur->prev != nullptr) {
                    cur->prev->next = cur->next;
                } else {
                    this->head = cur->next;
                }

                // check if the elemnt is the last
                if(cur->next != nullptr) {
                    cur->next->prev = cur->prev;
                } else {
                    this->tail = cur->prev;
                }

                delete cur;
                this->size--;
                return true;
            }
        }
        return false;
    }

    // remove all elements that have some value and returnes how many removed
    int list_removeAll(processo val) {
        int removed = 0;

        nodePtr cur;
        cur = head;

        //goes until the end of the list
        while (cur != nullptr) {
            if(cur->val == val) {

                // check if the elemnt is the first
                if(cur->prev != nullptr) {
                    cur->prev->next = cur->next;
                } else {
                    this->head = cur->next;
                }

                // check if the elemnt is the last
                if(cur->next != nullptr) {
                    cur->next->prev = cur->prev;
                } else {
                    this->tail = cur->prev;
                }

                delete cur;
                this->size--;
                removed++;
            }
        }
        return removed;
    }
};
*/
